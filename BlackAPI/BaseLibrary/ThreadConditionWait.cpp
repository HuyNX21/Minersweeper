#include "pch.h"
#include "ThreadConditionWait.h"

ThreadConditionWait::ThreadConditionWait(ConditionCheck *Checker)
{
	mCondChecker = NULL;
	mTimeMeasure = NULL;
	mWatchDogCounter = NULL;
	
	int error = pthread_cond_init( &mConditionWait, NULL );

	if(error != 0){
	}

	mCondChecker = Checker;
}

ThreadConditionWait::~ThreadConditionWait()
{
	pthread_cond_destroy(&mConditionWait);
}

void ThreadConditionWait::wait()
{
	pthread_mutex_t* p_mutex = mMutexLock.getMutexPointer();
	
	while(mCondChecker->checkCondition() == false){
		int error = pthread_cond_wait(&mConditionWait, p_mutex);
		if(error != 0){

		}
	}
}

bool ThreadConditionWait::waitTimeOut(int32_t sec, int32_t nano_sec)
{

	pthread_mutex_t mutex = mMutexLock.getMutex();
	bool ret = true;

	struct timespec time_out;
	
	time_out.tv_sec = time(NULL) + sec;
	time_out.tv_nsec = nano_sec;
	
	int error = pthread_cond_timedwait(&mConditionWait, &mutex, (const struct timespec*)&time_out);
	
	switch(error){
		case ETIMEDOUT:
			ret = false;
			break;
		default:
			if(error != 0){

			}
			break;
	}
	return ret;

}

void ThreadConditionWait::wakeup()
{
	int error = pthread_cond_signal( &mConditionWait );
	if(error != 0){

	}
}

void ThreadConditionWait::wakeupBroadcast()
{
	int error = pthread_cond_broadcast( &mConditionWait );
	if(error != 0){

	}
}

bool ThreadConditionWait::destroy()
{
	bool ret = true;
	
	int error = pthread_cond_destroy( &mConditionWait );
	switch(error){
		case 0:
			break;
		case EBUSY:
			ret = false;
			break;
		default:

			break;
	}

	return ret;
}

bool ThreadConditionWait::lockWait()
{
	return mMutexLock.lockWait();
}

bool ThreadConditionWait::unlock()
{
	return mMutexLock.unlock();
}