#ifndef __CLASS_MUTEX_LOCK_H_
#define __CLASS_MUTEX_LOCK_H_

#include <string>

#include <pthread.h>

#include "EnumBase.h"

class MutexLock
{
	public:
	
		MutexLock();

		enum MUTEX_TYPE {
				MUTEX_FAST_NP = 0,
				MUTEX_RECURSIVE_NP
		};

		MutexLock(MUTEX_TYPE type);

		void init(MUTEX_TYPE type);

		virtual ~MutexLock();

		void init();
		
		bool lockWait();
	
		bool lockNoWait();

		bool unlock();
	
		void destroy();
	
		const pthread_mutex_t getMutex();

		pthread_mutex_t* getMutexPointer();
	
	private:
		pthread_mutex_t mMutex;
		
		pthread_mutexattr_t mMutexAttribute;
		
};

class ScopeLock
{
	public :
		ScopeLock(MutexLock& mutex);
		
		virtual ~ScopeLock();
		
	private :
		ScopeLock();
		ScopeLock(const ScopeLock&);

		void* operator new(size_t) throw ();
		void  operator delete(void*);
		void* operator &() const;
		void  operator =(const ScopeLock&);
	
		MutexLock &mLock;
};

#endif // #ifndef __CLASS_MUTEX_LOCK_

