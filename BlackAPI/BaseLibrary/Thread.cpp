#include <sstream>
#include <iostream>
#include <exception>

#include <string.h>
#include <sys/syscall.h>
#include <linux/prctl.h>

#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "Thread.h"

const Thread::State NEW        = Thread::State("NEW");
const Thread::State RUNNABLE   = Thread::State("RUNNABLE");
const Thread::State TERMINATED = Thread::State("TERMINATED");

Thread::Thread(Runnable *runnable, std::string threadName, int prio)
:mThreadState(&NEW)
{
	mThread = 0;
	mThreadPID = 0;
	mRunnable = runnable;
	mThreadName = threadName;
	mThreadJoinable = false;
	mThreadStackSize = 1024*1024;
    priority = prio;
}

Thread::~Thread()
{
	pthread_attr_destroy(&mThreadAttribute);
}

void Thread::run()
{
	{
		int error = pthread_attr_init(&mThreadAttribute);
		if(error != 0){
		}
	}

	{
		int stackSize;
		int error = 0;
		
		stackSize = static_cast<int>((double)mThreadStackSize * 1.2);
		if(stackSize < 0x5000)
		{
			stackSize = 0x5000;
		}

		error = pthread_attr_setstacksize(&mThreadAttribute, stackSize);
		if(error != 0){
		}
	}

	{
		int error;
		int detachstate;
		if(mThreadJoinable == true){
			detachstate = PTHREAD_CREATE_JOINABLE;
		}else{
			detachstate = PTHREAD_CREATE_DETACHED;
		}
		error = pthread_attr_setdetachstate(&mThreadAttribute, detachstate);
		if(error != 0){
		}
	}

	{
		int error;
		error = pthread_attr_setscope( &mThreadAttribute , PTHREAD_SCOPE_SYSTEM );
		if(error != 0){
		}
	}
	
	{
		int error = pthread_create(&mThread, &mThreadAttribute, ThreadEntry, (void*)this);
		if(error != 0){
		}
	}
	
	pthread_attr_destroy(&mThreadAttribute);
}

void Thread::join()
{
	if(mThreadJoinable == false){
		return;
	}

	int error =  pthread_join(mThread, NULL);
	if(error != 0){
		Thread::sleepThread(1);
	}

}

std::string Thread::getName()
{
	return mThreadName;
}

int32_t Thread::getPID()
{
	return mThreadPID;
	
}

Thread::THREAD_ID_T Thread::getThreadId()
{
	
	return mThread;
}


bool Thread::equal(Thread* thread)
{
	int result = pthread_equal(this->mThread, thread->mThread);
	if(result != 0){
		return true;
	}else{
		return false;
	}
	
}


void Thread::setEnableJoin(bool joinable)
{

}


Thread* Thread::currentThread()
{
	THREAD_ID_T this_threadId = pthread_self();
	Thread* ret = NULL;
	
	ThreadList* thread_list = ThreadSafeSingleton<ThreadList>::getInstance();
	
	ScopeLock( thread_list->mutex() );
	
	TYPE_THREAD_LIST_CONTAINER& thread_list_ref = thread_list->reference();

	TYPE_THREAD_LIST_CONTAINER::iterator it = thread_list_ref.find(this_threadId);
	TYPE_THREAD_LIST_CONTAINER::iterator it_end = thread_list_ref.end();

	if(it != it_end){
		ret = (*it).second;
	}
	
	return ret;
}

void Thread::sleepThread(unsigned int seconds)
{
	sleep(seconds);
}

void Thread::nanosleepThread(unsigned int seconds, int32_t nanoSeconds)
{
	struct timespec arg;
	
	arg.tv_sec =  seconds;
	arg.tv_nsec = nanoSeconds;
	
	nanosleep(&arg, NULL);
}

void Thread::printThreadList()
{	
	std::ostringstream output_str;
	
	ThreadList* thread_list = Thread::ThreadListFactory::getInstance();

	ScopeLock( thread_list->mutex() );
		
	TYPE_THREAD_LIST_CONTAINER& thread_list_ref = thread_list->reference();

	Thread *thread;
	uint32_t i = 0;
	TYPE_THREAD_LIST_CONTAINER::iterator it = thread_list_ref.begin();
	TYPE_THREAD_LIST_CONTAINER::iterator it_end = thread_list_ref.end();
	for(;it != it_end;it++){
		i++;
		thread = (*it).second;
	}
	
}

int Thread::getThreadCntMax()
{
	return 1024;
}

#include <signal.h>
#define SIGNAL_STACK_SIZE (1024*128)

void* Thread::ThreadEntry(void *arg)
{
	Thread *thread = (Thread*)arg;
	
	ThreadList* thread_list = Thread::ThreadListFactory::getInstance();
	
	thread->mThreadState = &RUNNABLE;

	try{
		if(thread->mRunnable != NULL){
			thread->mThreadPID = getpid();

			thread_list->insert( thread->mThread, thread );

			thread->mRunnable->run();
			
			thread_list->erase(thread->mThread);

			thread->mThreadState = &TERMINATED;

			if(thread->mThreadJoinable == false){
				delete thread->mRunnable;
				delete thread;
			}
		}
	}catch(std::exception& ex){
	}
	pthread_exit(NULL);
}

Thread::State::State(std::string name) : EnumBase(name)
{

}

Thread::State::~State()
{

}

void Thread::setStackSize(size_t size)
{
			mThreadStackSize = size;
}

