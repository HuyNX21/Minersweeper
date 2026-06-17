//********************************************************************************************
/**
 * @file		Thread.h
 * @brief		Thread?¿½N?¿½?¿½?¿½X?¿½éŒ¾
 *
 * @author		Ri Kanji
 * @date		2010/11/29
 */
//********************************************************************************************

#ifndef __CLASS_THREAD_H_
#define __CLASS_THREAD_H_

#include <string>
#include <map>
#include <stdint.h>
#include <pthread.h>
#include "EnumBase.h"
#include "ThreadSafeMap.h"
#include "ThreadSafeSingleton.h"
#include "Runnable.h"

class Runnable;

#define DEF_STUB_THREAD_PRIO_SRVS_TH	(TYPD_PRIONO_BLKLIB__SrvSessionTh)
#define DEF_STUB_THREAD_PRIO_SRVS_THAS	(TYPD_PRIONO_BLKLIB__SrvSessionThAs)
#define DEF_STUB_THREAD_PRIO_SRVS_THTMP	(TYPD_PRIONO_BLKLIB__SrvSessionThTmp)
#define DEF_STUB_THREAD_PRIO_SRVC		(TYPD_PRIONO_BLKLIB__SrvConnectTh)
#define DEF_STUB_THREAD_PRIO_CONK		(TYPD_PRIONO_BLKLIB__ConKillProTh)

#define DEF_STACK_SIZE_PROXYASYNCTH 	(84*1024)		
#define DEF_STACK_SIZE_PROXYRCVTH		(36*1024)		
#define DEF_STACK_SIZE_SRVCONNECTTH		(32*1024)		
#define DEF_STACK_SIZE_STUBAPICPROTH	(156*1024)		
#define DEF_STACK_SIZE_SRVSESSIONTH		((36*1024)*2)	
#define DEF_STACK_SIZE_STUBRCVCTRLTH	((16+4+5)*1024)

// #define DEF_STUB_RECV_CTRL_THREAD_PRIO				(TYPD_PRIONO_BLKLIB__SrvRxCtrlTh)
// #define DEF_PROXY_RECV_CTRL_THREAD_PRIO_RX			(TYPD_PRIONO_BLKLIB__ProxyRxCtrlTh)
// #define DEF_PROXY_RECV_CTRL_THREAD_PRIO_RCV			(TYPD_PRIONO_BLKLIB__ProxyRcvTh)
// #define DEF_PROXY_RECV_CTRL_THREAD_PRIO_ASYNCRCV		(TYPD_PRIONO_BLKLIB__ProxyAsyncRcvTh)

#define DEF_PROXY_RECV_CTRL_THREAD_PRIO_RCV        10
#define DEF_PROXY_RECV_CTRL_THREAD_PRIO_ASYNCRCV   20
#define DEF_PROXY_RECV_CTRL_THREAD_PRIO_RX   15
#define DEF_STUB_RECV_CTRL_THREAD_PRIO       10
#define DEF_STUB_THREAD_PRIO_SRVS_TH 10
#define DEF_STUB_THREAD_PRIO_SRVS_THAS 20

#define TYPD_PRIONO_BLKLIB__ProxyTmpRcvTh 10

class Thread
{

	public:
		typedef pthread_t THREAD_ID_T;
		typedef pthread_attr_t		THREAD_ATTR_T;
		
		/// ?¿½X?¿½?¿½?¿½b?¿½h?¿½?¿½Ô’ï¿½`
		class State : public EnumBase
		{
			public :
				static const State NEW;		
				static const State RUNNABLE;	
				static const State TERMINATED;	
			
				State(std::string name);

				virtual ~State();
				
			private:
				
		};

		Thread(Runnable *runnable, std::string threadName, int prio = -1);
		
		virtual ~Thread();
		
		std::string getName();
		
		int32_t getPID();
		
		THREAD_ID_T getThreadId();
		
		Thread::State getState();
		
		bool equal(Thread* thread);
		
		void join();
		
		void setEnableJoin(bool joinable);

        void run();
		
		static Thread* currentThread();

		static void nanosleepThread(unsigned int seconds, int32_t nanoSeconds);

		static void printThreadList();

		static void sleepThread(unsigned int seconds);

        static int getThreadCntMax();
		
		void setStackSize(size_t size);

	private :

		typedef ThreadSafeMap<pthread_t, Thread*> TYPE_THREAD_LIST;
		typedef std::map<pthread_t, Thread*> TYPE_THREAD_LIST_CONTAINER;

		pthread_t mThread;
		
		pthread_attr_t mThreadAttribute;
		
		std::string mThreadName;
		
		int32_t mThreadPID;

        int priority;

		size_t mThreadStackSize;

		bool mThreadJoinable;

		Runnable *mRunnable;
		
		const Thread::State *mThreadState;
		
		
		class ThreadList : public TYPE_THREAD_LIST
		{
			
		};

		
		class ThreadListFactory : public ThreadSafeSingleton<ThreadList>
		{
			
		};

		static void* ThreadEntry(void *);
		
};

#endif	

