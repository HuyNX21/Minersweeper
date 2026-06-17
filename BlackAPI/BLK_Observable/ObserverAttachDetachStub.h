
#ifndef	__OBSERVER_ATTACH_DETACH_STUB_H_
#define	__OBSERVER_ATTACH_DETACH_STUB_H_

#include "BLKC_Common.h"
#include "BLKC_ConnectManager.h"
#include "BLKC_StubMethodTemplate.h"
#include "marsahling.h"
#include "unmarsahling.h"

namespace StubCommon
{

template<typename OBSERVER_T> void getInstanceByObserverId(BLKC_ConnectManager& c_connectMgr, uint32_t session_id, uint32_t observer_id, uint32_t &observer_instance_id, OBSERVER_T*& observer_obj);


template<typename OBJ_T, typename OBSERVER_T, typename ABSTRUCT_OBSERVER_T>
class ObserverAttachDettachFunc
{
	public :
	
		typedef void (OBJ_T::*FUNC_T)(ABSTRUCT_OBSERVER_T*) ;
		typedef bool (OBJ_T::*FUNC_RET_bool_T)(ABSTRUCT_OBSERVER_T*) ;
	
		static void attach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, ObserverAttachDettachFunc::FUNC_T func );
		
		static void attach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, void (*attach_func)(ABSTRUCT_OBSERVER_T*) );

		
		static void detach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, ObserverAttachDettachFunc::FUNC_T func);
		static void detach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, ObserverAttachDettachFunc::FUNC_RET_bool_T func);
		
		static void detach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, void (*detach_func)(ABSTRUCT_OBSERVER_T*));
	
};	// class ObserverAttachDettach

}	// namespace StubCommon

template<typename OBJ_T, typename OBSERVER_T, typename ABSTRUCT_OBSERVER_T>
void StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>
::attach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>::FUNC_T func )
{
	ABSTRUCT_OBSERVER_T* observer_obj;
	observer_obj = NULL;

	BLKC_StubMethodTemplate::BLKD_StubAttach_pre< OBJ_T, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	(obj->*func)( observer_obj );

	BLKC_StubMethodTemplate::BLKD_StubAttach_post< OBJ_T, void*, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, mMarshalDummy, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	return;
}

template<typename OBJ_T, typename OBSERVER_T, typename ABSTRUCT_OBSERVER_T>
void StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>
::attach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, void (*attach_func)(ABSTRUCT_OBSERVER_T*) )
{
	ABSTRUCT_OBSERVER_T* observer_obj;
	observer_obj = NULL;

	BLKC_StubMethodTemplate::BLKD_StubAttach_pre< OBJ_T, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	attach_func( observer_obj );

	BLKC_StubMethodTemplate::BLKD_StubAttach_post< OBJ_T, void*, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, mMarshalDummy, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	return;
}



template<typename OBJ_T, typename OBSERVER_T, typename ABSTRUCT_OBSERVER_T>
void StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>
::detach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>::FUNC_T func )
{
	ABSTRUCT_OBSERVER_T* observer_obj;
	observer_obj = NULL;

	BLKC_StubMethodTemplate::BLKD_StubDetach_pre< OBJ_T, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	(obj->*func)( observer_obj );

	BLKC_StubMethodTemplate::BLKD_StubDetach_post< OBJ_T, void*, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, mMarshalDummy, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	return;
}

template<typename OBJ_T, typename OBSERVER_T, typename ABSTRUCT_OBSERVER_T>
void StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>
::detach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>::FUNC_RET_bool_T func )
{
	ABSTRUCT_OBSERVER_T* observer_obj;

	BLKC_StubMethodTemplate::BLKD_StubDetach_pre< OBJ_T, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	bool ret = (obj->*func)( observer_obj );

	BLKC_StubMethodTemplate::BLKD_StubDetach_post< OBJ_T, bool, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, ret, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	return;
}


template<typename OBJ_T, typename OBSERVER_T, typename ABSTRUCT_OBSERVER_T>
void StubCommon::ObserverAttachDettachFunc<OBJ_T, OBSERVER_T, ABSTRUCT_OBSERVER_T>
::detach(BLKS_COMMONID* id, OBJ_T* obj, void* pt, void (*detach_func)(ABSTRUCT_OBSERVER_T*))
{
	ABSTRUCT_OBSERVER_T* observer_obj;
	observer_obj = NULL;

	BLKC_StubMethodTemplate::BLKD_StubDetach_pre< OBJ_T, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	detach_func( observer_obj );

	BLKC_StubMethodTemplate::BLKD_StubDetach_post< OBJ_T, void*, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			void*, void*, void*, void*, void*, void*, void*, void*, void*, void*,void*, void*, void*, void* >
		( id, obj, pt, mMarshalDummy, observer_obj,
			mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );

	return;
}

template<typename OBSERVER_T> void StubCommon::getInstanceByObserverId(BLKC_ConnectManager& c_connectMgr, uint32_t session_id, uint32_t observer_id, uint32_t &observer_instance_id, OBSERVER_T*& observer_obj)
{
	ObserverDestructor* obs_des = (ObserverDestructor*)c_connectMgr.findObserverObject( observer_id );
	observer_obj = (OBSERVER_T*)obs_des;

	if(observer_obj == NULL){
		observer_obj = new OBSERVER_T( session_id );
		c_connectMgr.addObserverObject( observer_id, observer_obj );
		observer_instance_id = c_connectMgr.getNewInstanceID( observer_obj );
	}else{
		observer_instance_id = c_connectMgr.findInstanceId( observer_obj );
	}
	
	return;
}


#endif	// #ifndef	__OBSERVER_ATTACH_DETACH_STUB_H_

