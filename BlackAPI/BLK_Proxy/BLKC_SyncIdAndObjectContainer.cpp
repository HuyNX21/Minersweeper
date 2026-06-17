#include "pch.h"
#include "BLKC_SyncIdAndObjectContainer.h"

BLKC_SyncIdAndObjectContainer::Data::Data()
: mThread( 0 )
, mTypeCount( 0 )
{
	memset( mTypeList, 0, sizeof( mTypeList ) );
	pthread_cond_init( &mCond, NULL );
}

BLKC_SyncIdAndObjectContainer::Data::~Data()
{
	int nErrNo = pthread_cond_destroy( &mCond );
	if ( nErrNo != 0 ) {
		if ( nErrNo == EBUSY ) {
			pthread_cond_broadcast( &mCond );
			nErrNo = pthread_cond_destroy( &mCond );
		}
	}
	if ( nErrNo != 0 ) {
		char scTaskName[16] = {};
		syscall(SYS_prctl, PR_GET_NAME, (unsigned long)scTaskName, (unsigned long)0, (unsigned long)0, (unsigned long)0);
		char scWhat[256];
		strerror_r( nErrNo, scWhat, sizeof( scWhat ) );
	}
}

BLKC_SyncIdAndObjectContainer::BLKC_SyncIdAndObjectContainer()
: mReserveBits( 0 )
, mReadyBits( 0 )
{
}

BLKC_SyncIdAndObjectContainer::~BLKC_SyncIdAndObjectContainer()
{
}

uint32_t BLKC_SyncIdAndObjectContainer::reserveSyncObject()
{
	mReserveMutex.lockWait();
	uint32_t uBits = ( ~mReserveBits ) & ( mReserveBits + 1 );

	mReserveBits |= uBits;
	mReserveMutex.unlock();
	
	if ( !uBits ) {
		char scTaskName[16] = {};
		syscall(SYS_prctl, PR_GET_NAME, (unsigned long)scTaskName, (unsigned long)0, (unsigned long)0, (unsigned long)0);
		return BLKD_SYNCIDANDOBJECT_DATA_MAX;
	}

	uint32_t uDataIndex = 0;
	while ( uBits >>= 1 ) {
		++uDataIndex;
	}
	mDataList[uDataIndex].mThread = pthread_self();
	return uDataIndex;
}

void BLKC_SyncIdAndObjectContainer::addSyncObject( const std::type_info* pType )
{
	uint32_t uBits = mReserveBits;
	uint32_t uDataIndex = 0;
	pthread_t pThread = pthread_self();
	Data* pData = NULL;
	do {
		if ( uBits & 0x00000001 ) {
			Data* itData = &mDataList[uDataIndex];
			if ( pThread == itData->mThread ) {
				pData = itData;
				break;
			}
		}
		++uDataIndex;
	} while ( uBits >>= 1 );
	
	if ( pData == NULL ) {
		return;
	}
	
	uint32_t uTypeIndex = 0;
	while ( uTypeIndex < pData->mTypeCount ) {
		if ( pType == pData->mTypeList[uTypeIndex] ) {
			return;
		}
		++uTypeIndex;
	}
	
	if ( pData->mTypeCount >= BLKD_SYNCIDANDOBJECT_TYPE_MAX ) {
		char scTaskName[16] = {};
		syscall(SYS_prctl, PR_GET_NAME, (unsigned long)scTaskName, (unsigned long)0, (unsigned long)0, (unsigned long)0);
		return;
	}
	
	pData->mTypeList[pData->mTypeCount++] = pType;
}

void BLKC_SyncIdAndObjectContainer::readySyncObject( uint32_t uDataIndex )
{
	if ( uDataIndex >= BLKD_SYNCIDANDOBJECT_DATA_MAX ) {
		return;
	}
	Data* pData = &mDataList[uDataIndex];
	if ( pData->mTypeCount > 0 ) {
		uint32_t uBits = ( 1 << uDataIndex );
		mReadyMutex.lockWait();
		mReadyBits |= uBits;
		mReadyMutex.unlock();
	}
}

bool BLKC_SyncIdAndObjectContainer::waitSyncObject( const std::type_info* pType )
{
	uint32_t uDataIndex = 0;
	uint32_t uBits = mReadyBits;
	pthread_t pThread = pthread_self();
	do {
		if ( uBits & 0x00000001 ) {
			Data* pData = &mDataList[uDataIndex];
			pData->mMutex.lockWait();
			if ( pThread != pData->mThread ) {
				uint32_t uTypeIndex = 0;
				while ( uTypeIndex < pData->mTypeCount ) {
					if ( pType == pData->mTypeList[uTypeIndex] ) {
						struct timespec stAbsTime;
#ifdef FUM_LINUX
						clock_gettime( CLOCK_REALTIME, &stAbsTime );
#else
						clock_gettime( CLOCK_MONOTONIC, &stAbsTime );
#endif
						stAbsTime.tv_sec += ( 5 * 60 );
						do {
#ifdef FUM_LINUX
							int nErrNo = pthread_cond_timedwait( &pData->mCond, pData->mMutex.getMutexPointer(), &stAbsTime );
#else
							int nErrNo = pthread_cond_clockwait( &pData->mCond, pData->mMutex.getMutexPointer(), CLOCK_MONOTONIC, &stAbsTime );
#endif
							if ( nErrNo == EINTR ) {
								continue;
							} else if ( nErrNo != 0 ) {
								char scTaskName[16] = {};
								syscall(SYS_prctl, PR_GET_NAME, (unsigned long)scTaskName, (unsigned long)0, (unsigned long)0, (unsigned long)0);
								char scWhat[256];
								strerror_r( nErrNo, scWhat, sizeof( scWhat ) );
								void *pv_StackFrame[128] = {};
								int nStackFrame = backtrace(pv_StackFrame, sizeof(pv_StackFrame)/sizeof(pv_StackFrame[0]));
								backtrace_symbols_fd(pv_StackFrame, nStackFrame, STDOUT_FILENO);
							}
						} while( 0 );
						pData->mMutex.unlock();
						return true;
					}
					++uTypeIndex;
				}
			}
			pData->mMutex.unlock();
		}
		++uDataIndex;
	} while ( uBits >>= 1 );
	
	return false;
}

void BLKC_SyncIdAndObjectContainer::signalSyncObject( uint32_t uDataIndex )
{
	if ( uDataIndex >= BLKD_SYNCIDANDOBJECT_DATA_MAX ) {
		return;
	}
	
	Data* pData = &mDataList[uDataIndex];
	
	uint32_t uBits = ( 1 << uDataIndex );
	bool bReady = ( ( mReadyBits & uBits ) == uBits );
	if ( bReady ) {
		pData->mMutex.lockWait();
		pthread_cond_broadcast( &pData->mCond );
	}

	pData->mThread = 0;
	pData->mTypeCount = 0;
	
	if ( bReady ) {
		mReadyMutex.lockWait();
		mReadyBits &= ~uBits;
		mReadyMutex.unlock();
	}
	
	mReserveMutex.lockWait();
	mReserveBits &= ~uBits;
	mReserveMutex.unlock();

	if ( bReady ) {
		pData->mMutex.unlock();
	}
}
