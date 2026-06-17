#ifndef __CLASS_BLKC_IDANDOBJECTCONTAINER_H_
#define __CLASS_BLKC_IDANDOBJECTCONTAINER_H_

#include <map>

#include "MutexLock.h"
#include "ObserverDestructor.h"

using namespace std;

template<typename OBJ_T>
class BLKC_IdAndObjectContainer
{
	private :
		typedef map<uint32_t, OBJ_T*> ID_OBJECT_TBL_T;
		typedef map<OBJ_T*, uint32_t> OBJECT_ID_TBL_T;
		typedef typename ID_OBJECT_TBL_T::value_type ID_OBJECT_TBL_VT_T;
		typedef typename OBJECT_ID_TBL_T::value_type OBJECT_ID_TBL_VT_T;

	
		MutexLock mPreRegistMutex;
		
		uint32_t mIdNumber;

		uint32_t createNewId();
	protected:
		typedef typename ID_OBJECT_TBL_T::iterator ID_OBJECT_TBL_IT_T;
		typedef typename OBJECT_ID_TBL_T::iterator OBJECT_ID_TBL_IT_T;
		MutexLock mMutex;
		ID_OBJECT_TBL_T mIdObjectTbl;
		OBJECT_ID_TBL_T mObjectIdTbl;

	public :
	
		BLKC_IdAndObjectContainer();
		
		virtual ~BLKC_IdAndObjectContainer();

		uint32_t resistObject(OBJ_T* object);

		void addIdAndObject(uint32_t id, OBJ_T* obj);
		
		OBJ_T* findObject(uint32_t id);
			
		uint32_t findId(OBJ_T* object);

		void unregistObject(uint32_t id);
		
		void deleteObject(uint32_t id);
			
		void deleteAllObject();
		
		uint32_t getSize();

	private :

		uint32_t doResistObject(OBJ_T* object);

		void doAddIdAndObject(uint32_t id, OBJ_T* obj);
		
		OBJ_T* doFindObject(uint32_t id);
		
		uint32_t doFindId(OBJ_T* object);
		
		void doUnregistObject(uint32_t id);

		void doDeleteAllObject();

	protected:

		void doDeleteObject(uint32_t id);


			
};
		


	
template<typename OBJ_T>
BLKC_IdAndObjectContainer<OBJ_T>::BLKC_IdAndObjectContainer()
:mIdNumber(0)
{
		

}

template<typename OBJ_T>
BLKC_IdAndObjectContainer<OBJ_T>::~BLKC_IdAndObjectContainer()
{
			ScopeLock lock( mMutex );
		
}

template<typename OBJ_T>
uint32_t BLKC_IdAndObjectContainer<OBJ_T>::resistObject(OBJ_T* object)
{

			ScopeLock lock( mMutex );
		
			return doResistObject( object );
		
}
		
		

template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::addIdAndObject(uint32_t id, OBJ_T* obj)
{
	if ( BLKD_PRE_OBSERVER_ID == id ) {
		mPreRegistMutex.lockWait();
	}

	ScopeLock lock( mMutex );

	doAddIdAndObject(id, obj);
}
		
		
template<typename OBJ_T>
OBJ_T* BLKC_IdAndObjectContainer<OBJ_T>::findObject(uint32_t id)
{
	ScopeLock lock( mMutex );
	
	return doFindObject( id );
}
		
template<typename OBJ_T>
uint32_t BLKC_IdAndObjectContainer<OBJ_T>::findId(OBJ_T* object)
{
	ScopeLock lock( mMutex );
	
	return doFindId( object );
}

template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::unregistObject(uint32_t id)
{
	ScopeLock lock( mMutex );
	
	doUnregistObject( id );

	if ( BLKD_PRE_OBSERVER_ID == id ) {
		mPreRegistMutex.unlock();
	}
}

template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::deleteObject(uint32_t id)
{
	ScopeLock lock( mMutex );

	doDeleteObject( id );
}
		
template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::deleteAllObject()
{
	ScopeLock lock( mMutex );

	doDeleteAllObject();
}

template<typename OBJ_T>
uint32_t BLKC_IdAndObjectContainer<OBJ_T>::doResistObject(OBJ_T* object)
{
	uint32_t ret_id = doFindId(object);

	if(ret_id == 0){
		ret_id = createNewId();
		mIdObjectTbl.insert( ID_OBJECT_TBL_VT_T( ret_id, object ) );
		mObjectIdTbl.insert( OBJECT_ID_TBL_VT_T( object, ret_id ) );
		LOG_INFO("regist object id: %d", ret_id);
	}

	return ret_id;
}
		
template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::doAddIdAndObject(uint32_t id, OBJ_T* obj)
{
	ID_OBJECT_TBL_IT_T it = mIdObjectTbl.find( id );
	ID_OBJECT_TBL_IT_T it_end = mIdObjectTbl.end();

//	OBJ_T* object = NULL;
	if(it == it_end){
		mIdObjectTbl.insert( make_pair(id,  obj) );
		mObjectIdTbl.insert( make_pair(obj, id ) );
		LOG_INFO("add object id: %d", id);
	}
	
	return;
}

template<typename OBJ_T>
OBJ_T* BLKC_IdAndObjectContainer<OBJ_T>::doFindObject(uint32_t id)
{
	if(mIdObjectTbl.empty() == true){
		return NULL;
	}

	ID_OBJECT_TBL_IT_T it = mIdObjectTbl.find( id );
	ID_OBJECT_TBL_IT_T it_end = mIdObjectTbl.end();

	OBJ_T* object = NULL;
	if(it != it_end){
		object = (*it).second;
		LOG_INFO("finded object id: %d", id);
	}
	
	return object;
}
		
template<typename OBJ_T>
uint32_t BLKC_IdAndObjectContainer<OBJ_T>::doFindId(OBJ_T* object)
{
	if(mObjectIdTbl.empty() == true){
		return 0;
	}

	OBJECT_ID_TBL_IT_T it = mObjectIdTbl.find( object );
	OBJECT_ID_TBL_IT_T it_end = mObjectIdTbl.end();

	uint32_t id = 0;
	if(it != it_end){
		id = (*it).second;
	}
	
	return id;
}

		
template<typename OBJ_T>
uint32_t BLKC_IdAndObjectContainer<OBJ_T>::createNewId()
{
	ID_OBJECT_TBL_IT_T it_end = mIdObjectTbl.end();

	do{
		do{
			++mIdNumber;
		}while(mIdObjectTbl.find( mIdNumber ) != it_end);

	}while( (mIdNumber == 0) || (mIdNumber == BLKD_PRE_OBSERVER_ID) || (mIdNumber == BLKD_NOTPRE_OBSERVER_ID) || (mIdNumber == BLKD_PRE_OBSERVER_ID_NOWAIT) );
		
	return mIdNumber;
}

template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::doUnregistObject(uint32_t id)
{
	OBJ_T*	object = doFindObject( id );
	if(object != NULL){
		mIdObjectTbl.erase( id );
		mObjectIdTbl.erase( object );
	}	
}
		
template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::doDeleteObject(uint32_t id)
{
	OBJ_T*	object = doFindObject( id );
	if(object != NULL){
		delete object;
		mIdObjectTbl.erase( id );
		mObjectIdTbl.erase( object );
	}
}

template<typename OBJ_T>
void BLKC_IdAndObjectContainer<OBJ_T>::doDeleteAllObject()
{
	ID_OBJECT_TBL_IT_T it = mIdObjectTbl.begin();
	ID_OBJECT_TBL_IT_T it_end = mIdObjectTbl.end();

	for(; it != it_end ; it++){
		delete (*it).second;
	}

	mIdObjectTbl.clear();
	mObjectIdTbl.clear();
}

template<typename OBJ_T>
uint32_t BLKC_IdAndObjectContainer<OBJ_T>::getSize()
{
	return mIdObjectTbl.size();
}


#endif // #ifndef __CLASS_BLKC_IDANDOBJECTCONTAINER_H_
