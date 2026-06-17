#ifndef	__CLASS_THREAD_SAFE_SINGLETON_H_
#define	__CLASS_THREAD_SAFE_SINGLETON_H_

#include <pthread.h>

template< typename T >
class ThreadSafeSingleton
{
	public:
	
		static T* getInstance();
		
	private:
	
		ThreadSafeSingleton();

		~ThreadSafeSingleton();
	
		static T* mInstance;
		static pthread_once_t mOnceValue;
	
		static void init();
};


template< typename T >
pthread_once_t ThreadSafeSingleton<T>::mOnceValue = PTHREAD_ONCE_INIT;

template< typename T >
T* ThreadSafeSingleton<T>::mInstance = NULL;

template< typename T >
ThreadSafeSingleton<T>::ThreadSafeSingleton()
{
	
}
	
template< typename T >
ThreadSafeSingleton<T>::~ThreadSafeSingleton()
{
	
}

template< typename T >
T* ThreadSafeSingleton<T>::getInstance()
{
	if(mInstance == NULL){
		pthread_once(&mOnceValue, init);
	}
	
	return mInstance;
	
}

template< typename T >
void ThreadSafeSingleton<T>::init()
{
	mInstance = new T;
}

#endif	// __CLASS_THREAD_SAFE_SINGLETON_H_

