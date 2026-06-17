
#ifndef	__OBSERVER_ATTACH_DETACH_PROXY_H_
#define	__OBSERVER_ATTACH_DETACH_PROXY_H_

#include "BLKC_Common.h"
#include "BLKC_ProxyMethodTemplate.h" 

class ProxyCommon
{
public:
	template<typename OBJ_T>
	static void attachObserver(BLKS_COMMONID* id, OBJ_T* obj);

	template<typename OBJ_T>
	static void detachObserver(BLKS_COMMONID* id, OBJ_T* obj);

	template<typename OBJ_T>
	static void detachObserver(BLKS_COMMONID* id, bool& ret, OBJ_T* obj);
};

template<typename OBJ_T>
void ProxyCommon::attachObserver(BLKS_COMMONID* id, OBJ_T* obj)
{
	BLKC_ProxyMethodTemplate::BLKD_ProxyAttach( id->ClassMethodID, id->InstanceID, mMarshalDummy, mMarshalDummy, obj,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

template<typename OBJ_T>
void ProxyCommon::detachObserver(BLKS_COMMONID* id, OBJ_T* obj)
{
	BLKC_ProxyMethodTemplate::BLKD_ProxyDetach( id->ClassMethodID, id->InstanceID, mMarshalDummy, mMarshalDummy, obj,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

template<typename OBJ_T>
void ProxyCommon::detachObserver(BLKS_COMMONID* id, bool& ret, OBJ_T* obj)
{
	BLKC_ProxyMethodTemplate::BLKD_ProxyDetach( id->ClassMethodID, id->InstanceID, mMarshalDummy, ret, obj,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy,
					mMarshalDummy, mMarshalDummy, mMarshalDummy, mMarshalDummy );
}

#endif	// #ifndef	__OBSERVER_ATTACH_DETACH_PROXY_H_

