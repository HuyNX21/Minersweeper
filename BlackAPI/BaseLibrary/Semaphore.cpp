
#include <string.h>


#include <errno.h>
#include <time.h>
#include "Semaphore.h"

Semaphore::Semaphore()
{
	
	init();
}

Semaphore::Semaphore(unsigned int initial_sem_val)
{
	
	init( initial_sem_val );
}

Semaphore::~Semaphore()
{
	
	destroy();
}

void Semaphore::post()
{
	int error = sem_post( &mSemaphore );
	if(error != 0){
	}
}

void Semaphore::wait()
{
RETRY:
	int error = sem_wait( &mSemaphore );
	if(error != 0){
		if( errno == EINTR ) goto RETRY;
#ifdef FUM_LINUX
		if( errno == 512 ) goto RETRY;
#endif

	}
	
}

bool Semaphore::timedWait(int32_t timeout_sec, int32_t timeout_nsec)
{
	struct timespec time;

	static const int32_t TIME_1SEC = 1000*1000*1000;

	clock_gettime( CLOCK_REALTIME, &time );

	time.tv_sec += timeout_sec;
	time.tv_nsec += timeout_nsec;
	if( time.tv_nsec >= TIME_1SEC){
		time.tv_nsec -= TIME_1SEC;
		time.tv_sec++;
	}
	
	
RETRY:
	int error = sem_timedwait( &mSemaphore, &time );

	if(error != 0){
		if( errno == EINTR ){
			goto RETRY;
		}else if( errno == ETIMEDOUT ){
			return false;
		}
	}
	
	return true;
}

void Semaphore::destroy()
{
	
	int error = sem_destroy( &mSemaphore );
	if(error != 0){

	}

}

void Semaphore::init(unsigned int initial_sem_val)
{
	memset( &mSemaphore, 0, sizeof(sem_t) );
	int error = sem_init( &mSemaphore, 0, initial_sem_val );
	
	if(error != 0){
	}
	
	return;
}

	

