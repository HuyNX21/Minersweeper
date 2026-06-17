#ifndef __CLASS_THREAD_CONDITION_WAIT_H_
#define __CLASS_THREAD_CONDITION_WAIT_H_

#include "MutexLock.h"
#include "ConditionCheck.h"

#include "BLKC_Common.h"

class ConditionCheck;
class TimeMeasure;
class WatchDogCounter;

class ThreadConditionWait
{
    public:
        ThreadConditionWait(ConditionCheck *Checker);
        virtual ~ThreadConditionWait();
		void wait();
		bool waitTimeOut(int32_t sec, int32_t nano_sec);
		void wakeup();
		void wakeupBroadcast();
		bool destroy();
		bool lockWait();
		bool unlock();
    
    private:
		MutexLock mMutexLock;
		pthread_cond_t mConditionWait;
		ConditionCheck* mCondChecker;
		TimeMeasure* mTimeMeasure;
		WatchDogCounter* mWatchDogCounter;

};

#endif