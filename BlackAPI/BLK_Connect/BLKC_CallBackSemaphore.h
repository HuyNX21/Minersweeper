#ifndef _CLASS_BLKC_CALLBACKSEMAPHORE_H_
#define _CLASS_BLKC_CALLBACKSEMAPHORE_H_

#include <stdint.h>

class Semaphore;

template<typename THIS_KEY_T, typename THIS_VALUE_T> 
class ThreadSafeMap;

template< typename T >
class ThreadSafeSingleton;


class BLKC_CallBackSemaphore
{
	
	friend class ThreadSafeSingleton<BLKC_CallBackSemaphore>;
	
	public :
	
		static void lock(uint32_t callback_id);
	
		static void unlock(uint32_t callback_id);
	
	private :
	
		static BLKC_CallBackSemaphore* mThisInstace;
	
		BLKC_CallBackSemaphore();
		BLKC_CallBackSemaphore( const BLKC_CallBackSemaphore& );
	
		~BLKC_CallBackSemaphore();
	
		typedef ThreadSafeMap<uint32_t, Semaphore*> SEMPHORE_LIST_T;
	
		SEMPHORE_LIST_T* mSemaphoreList;
	
		void doLock(uint32_t callback_id);

		void doUnlock(uint32_t callback_id);
	
};




#endif // #ifdef _CLASS_BLKC_CALLBACKSEMAPHORE_H_

