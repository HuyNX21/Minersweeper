
#ifndef  __CLASS_SEMAPHORE_H_
#define __CLASS_SEMAPHORE_H_

#define CLOCK_REALTIME	0x0

#include <semaphore.h>

class Semaphore
{
	public :
	
		Semaphore();
		
		Semaphore(unsigned int initial_sem_val);
		
		virtual ~Semaphore();
		
		void post();
	
		void wait();
		bool timedWait(int32_t timeout_sec, int32_t timeout_nsec);
		
		void destroy();
	
	private :
		
		void init(unsigned int initial_sem_val=0);

		sem_t mSemaphore;
	
};

#endif	// #ifdef  __CLASS_SEMAPHORE_H_


