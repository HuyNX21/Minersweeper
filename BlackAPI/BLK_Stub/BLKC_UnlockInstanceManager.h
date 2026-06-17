#ifndef __CLASS_BLKC_UNLOCKINSTANCEMANAGER_H_
#define __CLASS_BLKC_UNLOCKINSTANCEMANAGER_H_

#include <map>
#include <list>
#include <typeinfo>
#include <cxxabi.h>
#include <stdint.h>
#include "MutexLock.h"

#include "BLKC_Common.h"

using namespace std;

class BLKC_UnlockInstance
{
	public :
		BLKC_UnlockInstance(){}

		virtual ~BLKC_UnlockInstance(){}

		virtual bool checkInsAndSessionID( void* p_ApicInstance, uint32_t SessionID ) = 0;

		virtual bool callUnlock() = 0;

		virtual void onUnlockFlag( uint32_t SessionID ) = 0;

		virtual void outputLog( uint32_t InstanceID ) = 0;
};

class BLKC_UnlockInstanceManager
{
	private :
		list<BLKC_UnlockInstance*> mUnlockInstanceList;
		MutexLock mMutex;

	public :
		BLKC_UnlockInstanceManager();

		~BLKC_UnlockInstanceManager();

		void registInstance( BLKC_UnlockInstance* p_UnlockInstance );

		void deleteInstance( void* p_ApicInstance, uint32_t SessionID );

private:
		void onUnlockFlag( uint32_t SessionID );

		void callUnlock();
public:
		void endSession( uint32_t SessionID );

		void dump_UnlockInsTbl( int mode );
};

template<typename T>
class BLKC_UnlockInstanceT : public BLKC_UnlockInstance
{
	private :
		T* mInstance;
		uint32_t mSessionID;
		bool mUnlockFlag;
	public :
		BLKC_UnlockInstanceT( T* p_ApicInstance, uint32_t SessionID );

		virtual ~BLKC_UnlockInstanceT();

		virtual bool checkInsAndSessionID( void* p_ApicInstance, uint32_t SessionID );

		virtual bool callUnlock();

		virtual void onUnlockFlag( uint32_t SessionID );

		virtual void outputLog( uint32_t InstanceID );
};

template<typename T>
BLKC_UnlockInstanceT<T>::BLKC_UnlockInstanceT( T* p_ApicInstance, uint32_t SessionID ) : mInstance(p_ApicInstance), mSessionID(SessionID), mUnlockFlag(false)
{
}

template<typename T>
BLKC_UnlockInstanceT<T>::~BLKC_UnlockInstanceT()
{
}

template<typename T>
bool BLKC_UnlockInstanceT<T>::checkInsAndSessionID( void* p_ApicInstance, uint32_t SessionID )
{
	bool b_ret = false;
	if( p_ApicInstance == mInstance && SessionID == mSessionID ) {
		b_ret = true;
	}
	
	return b_ret;
}

template<typename T>
bool BLKC_UnlockInstanceT<T>::callUnlock()
{
	if( !mUnlockFlag )	return false;
	
	if( mInstance != NULL ) {
		mInstance->unlock();
	}
	
	return true;
}

template<typename T>
void BLKC_UnlockInstanceT<T>::onUnlockFlag( uint32_t SessionID )
{
	if( SessionID == mSessionID )
	{
		mUnlockFlag = true;
	}
	
}

template<typename T>
void BLKC_UnlockInstanceT<T>::outputLog( uint32_t InstanceID )
{
	int status = 0;
	const type_info& t_info = typeid(*mInstance);
}

#endif // #ifndef __CLASS_BLKC_UNLOCKINSTANCEMANAGER_H_
