#ifndef __CLASS_BLKC_DELETEINSTANCEMANAGER_H_
#define __CLASS_BLKC_DELETEINSTANCEMANAGER_H_

#include <map>
#include <list>
#include <typeinfo>
#include <cxxabi.h>

#include "BLKC_Common.h"

using namespace std;

class BLKC_DeleteInstance
{
	public :
		BLKC_DeleteInstance(){}

		virtual ~BLKC_DeleteInstance(){}

		virtual void destoryInstance() = 0;

		virtual void outputLog( uint32_t InstanceID ) = 0;
};

class BLKC_DeleteInstanceManager
{
	private :
		map<uint32_t, BLKC_DeleteInstance*> mIdAndInstanceTbl;
		list<uint32_t> mInstanceOrder;

	public :
		BLKC_DeleteInstanceManager();

		~BLKC_DeleteInstanceManager();

		void registInstanceMap( uint32_t InstanceID, BLKC_DeleteInstance* p_Instance );

		void deleteInstanceMap( uint32_t InstanceID );

		void destoryAllInstance();

		BLKC_DeleteInstance* findInstance( uint32_t InstanceID );

		void dump_deleteInsTbl( int mode );
};

template<typename T>
class BLKC_DeleteInstanceT : public BLKC_DeleteInstance
{
	private :
		T* mInstance;
	public :
		BLKC_DeleteInstanceT( T* p_Instance );

		virtual ~BLKC_DeleteInstanceT();

		virtual void destoryInstance();

		virtual void outputLog( uint32_t InstanceID );
};

template<typename T>
BLKC_DeleteInstanceT<T>::BLKC_DeleteInstanceT( T* p_Instance ) : mInstance(p_Instance)
{
}

template<typename T>
BLKC_DeleteInstanceT<T>::~BLKC_DeleteInstanceT()
{
}

template<typename T>
void BLKC_DeleteInstanceT<T>::destoryInstance()
{
	if( mInstance != NULL ) {
		delete mInstance;
		mInstance = NULL;
	}
}

template<typename T>
void BLKC_DeleteInstanceT<T>::outputLog( uint32_t InstanceID )
{
	int status = 0;
	const type_info& t_info = typeid(*mInstance);	
}

// template<typename T>
// class BLKC_DeleteInstanceAddressSearch : public BLKC_DeleteInstance
// {
// 	private :
// 		TYPC_AddressSearch<T>* mInstance;
// 	public :
// 		BLKC_DeleteInstanceAddressSearch( TYPC_AddressSearch<T>* p_Instance );
// 		virtual ~BLKC_DeleteInstanceAddressSearch();

// 		virtual void destoryInstance();

// 		virtual void outputLog( uint32_t InstanceID );
// };

// template<typename T>
// BLKC_DeleteInstanceAddressSearch<T>::BLKC_DeleteInstanceAddressSearch( TYPC_AddressSearch<T>* p_Instance ) : mInstance(p_Instance)
// {
// }

// template<typename T>
// BLKC_DeleteInstanceAddressSearch<T>::~BLKC_DeleteInstanceAddressSearch()
// {
// }

// template<typename T>
// void BLKC_DeleteInstanceAddressSearch<T>::destoryInstance()
// {
// 	if( mInstance != NULL ) {
// 		delete mInstance;
// 		mInstance = NULL;
// 	}
// }

// template<typename T>
// void BLKC_DeleteInstanceAddressSearch<T>::outputLog( uint32_t InstanceID )
// {
// 	int status = 0;
// 	const type_info& t_info = typeid(*mInstance);
// 	printf("(%u)(sys:BlackAPI) ID(%u) Class(%p:%s)\n", SYSF_tickGet(),
// 		InstanceID, mInstance, abi::__cxa_demangle(t_info.name(), 0, 0, &status) );
// }

#endif // #ifndef __CLASS_BLKC_DELETEINSTANCEMANAGER_H_
