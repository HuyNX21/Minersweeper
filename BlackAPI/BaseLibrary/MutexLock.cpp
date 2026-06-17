
#include <string.h>

#include <errno.h>

#include "MutexLock.h"


MutexLock::MutexLock()
{
	init();
}

MutexLock::MutexLock(MUTEX_TYPE type)
{
	init(type);
}

MutexLock::~MutexLock()
{
	destroy();
}

void MutexLock::init()
{
	int error;
	error = pthread_mutexattr_init( &mMutexAttribute );
	if(error != 0){

	}
	
	error = pthread_mutexattr_settype( &mMutexAttribute , PTHREAD_MUTEX_FAST_NP );
	if(error != 0){
	}

	error = pthread_mutex_init( &mMutex, &mMutexAttribute);
	if(error != 0){
	}

	unlock();
}

void MutexLock::init(MUTEX_TYPE type)
{
	int i_error;

	int mutex_type = PTHREAD_MUTEX_FAST_NP;
	if(type == MUTEX_RECURSIVE_NP) {
		mutex_type = PTHREAD_MUTEX_RECURSIVE_NP ;
	}
	
	i_error = pthread_mutexattr_init( &mMutexAttribute );
	if(i_error != 0){
		char sc_buf[64];
		memset(sc_buf, 0, sizeof(sc_buf));
		strerror_r(i_error, sc_buf, sizeof(sc_buf)/sizeof(sc_buf[0]));

	}
	
	
	i_error = pthread_mutexattr_settype( &mMutexAttribute , mutex_type );
	if(i_error != 0){
		char sc_buf[64];
		memset(sc_buf, 0, sizeof(sc_buf));
		strerror_r(i_error, sc_buf, sizeof(sc_buf)/sizeof(sc_buf[0]));

	}

	i_error = pthread_mutex_init( &mMutex, &mMutexAttribute);
	if(i_error != 0){
		char sc_buf[64];
		memset(sc_buf, 0, sizeof(sc_buf));
		strerror_r(i_error, sc_buf, sizeof(sc_buf)/sizeof(sc_buf[0]));

	}
}


void MutexLock::destroy()
{
	
	int error = pthread_mutex_destroy( &mMutex );
	if(error == EBUSY){
		unlock();
		pthread_mutex_destroy( &mMutex );
		pthread_mutexattr_destroy( &mMutexAttribute );
	}
}

const pthread_mutex_t MutexLock::getMutex()
{
	return (const pthread_mutex_t)mMutex;
}

pthread_mutex_t* MutexLock::getMutexPointer()
{
	return &mMutex;
}

bool MutexLock::lockWait()
{

	int error = pthread_mutex_lock( &mMutex );
	bool ret = false;
	
	switch(error){
		case 0:
			ret = true;
			break;
		case EDEADLK:
			ret = false;
			break;
		default:
			break;
	}
	return ret;
}
	
bool MutexLock::lockNoWait()
{
	bool ret = false;

	int error = pthread_mutex_trylock( &mMutex );

	switch(error){
		case 0:
			ret = true;
			break;
		case EBUSY:
			ret = false;
			break;
		default:
			break;
	}

	return ret;
}

bool MutexLock::unlock()
{
	bool ret = false;

	int error = pthread_mutex_unlock( &mMutex );

	switch(error){
		case 0:
			ret = true;
			break;
		case EPERM:
			ret = false;
			break;
		default:
			break;
	}
	
	return ret;
}

ScopeLock::ScopeLock(MutexLock& mutex)
:mLock(mutex)
{
	mLock.lockWait();
	
}
		
ScopeLock::~ScopeLock()
{
	mLock.unlock();
	
	
}

void* ScopeLock::operator new(size_t) throw ()
{
	
	return NULL;
}

void  ScopeLock::operator delete(void*)
{
	
	
}

void* ScopeLock::operator &() const
{
	return NULL;
	
}

void  ScopeLock::operator =(const ScopeLock&)
{
	
}


