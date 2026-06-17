#ifndef __BLKC_SYNCIDANDOBJECTCONTAINER_H__
#define __BLKC_SYNCIDANDOBJECTCONTAINER_H__

#include <pthread.h>
#include <vector>
#include <typeinfo>
#include "MutexLock.h"

#define BLKD_SYNCIDANDOBJECT_DATA_MAX	(32)
#define BLKD_SYNCIDANDOBJECT_TYPE_MAX	(32)

class BLKC_SyncIdAndObjectContainer
{
	public:
		struct Data
		{
			Data();
			~Data();
			
			MutexLock					mMutex;										
			pthread_t					mThread;									
			uint32_t					mTypeCount;									
			const std::type_info*		mTypeList[BLKD_SYNCIDANDOBJECT_TYPE_MAX];	
			pthread_cond_t				mCond;										
		};

	public:
		BLKC_SyncIdAndObjectContainer();
		~BLKC_SyncIdAndObjectContainer();
		uint32_t reserveSyncObject();
		void addSyncObject( const std::type_info* pType );
		void readySyncObject( uint32_t uDataIndex );
		bool waitSyncObject( const std::type_info* pType );
		void signalSyncObject( uint32_t uDataIndex );

	private:
		MutexLock						mReserveMutex;
		uint32_t						mReserveBits;
		
		MutexLock						mReadyMutex;
		uint32_t						mReadyBits;
		
		Data							mDataList[BLKD_SYNCIDANDOBJECT_DATA_MAX];
};

#endif // #ifndef __BLKC_SYNCIDANDOBJECTCONTAINER_H__
