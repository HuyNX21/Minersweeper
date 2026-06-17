#ifndef __BLKC_STUBMETHODTEMPLATE_H__
#define __BLKC_STUBMETHODTEMPLATE_H__

#include "AllocateMemory.h"
#include "ClassIDMethodID.h"

#include "BLKC_Common.h"
#include "BLKC_MarshalWrapper.h"
#include "BLKC_UnmarshalWrapper.h"
#include "BLKC_StubManager.h"
#include "BLKC_ConnectManager.h"

#define BLKD_ALLOCATE_SENDBUFFER(buf) AllocateMemory<uchar> send_mem( sizeof(BLKS_MSG_FORMAT) ); \
												buf = (send_mem.allocate()==NULL)? NULL:send_mem.getTopAddress()+BLKD_MSGHEAD_SIZE;

#define RENEW_FUNC_INFO()
#define CALL_MARSHALDISP_FUNC()

class BLKC_StubMethodTemplate
{
    private:
        static BLKC_MarshalWrapper* mMarshalWrapper;
        static BLKC_UnmarshalWrapper* mUnmarshalWrapper;
        
        static BLKC_MarshalWrapper* getMarshalWrapper();
        static BLKC_UnmarshalWrapper* getUnmarshalWrapper();

    public:

        template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
	    static void BLKD_StubNewinstance_pre( BLKS_COMMONID* type_id , OBJ_T*& pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 );

        template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
	    static void BLKD_StubNewinstance_post( BLKS_COMMONID* type_id , OBJ_T*& pc_obj , void*& pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6);

        template<typename OBJ_T,
                 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
                 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
                 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T >
        static void BLKD_StubParaType_pre( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt,
                                            PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
                                            PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
                                            PARA12_T& para12, PARA13_T& para13, PARA14_T& para14, PARA15_T& para15, PARA16_T& para16 );

        template<typename OBJ_T, typename RET_T, 
                typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
                typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
                typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T >
        static void BLKD_StubParaType_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, RET_T ret,
                                            PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
                                            PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
                                            PARA12_T& para12, PARA13_T& para13, PARA14_T& para14, PARA15_T& para15, PARA16_T& para16 );

        template<typename OBJ_T,
                typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
                typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
                typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T >
        static void BLKD_StubParaType_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt,
                                            PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
                                            PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
                                            PARA12_T& para12, PARA13_T& para13, PARA14_T& para14, PARA15_T& para15, PARA16_T& para16 );

		template<typename RET_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
		static void BLKD_StubCallBack( uint32_t upperCBID,RET_T& ret, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 );

		template<typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
		static void BLKD_StubCallBack( uint32_t upperCBID, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 );

		template<typename OBJ_T, typename RET_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
		static void BLKD_StubNotify( uint32_t ClassMethodID, OBJ_T* pc_obj , RET_T& ret, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4);

		template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
		static void BLKD_StubNotify( uint32_t ClassMethodID, OBJ_T* pc_obj , PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4);

		template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
		static void BLKD_StubNotify( uint32_t ClassMethodID, OBJ_T* pc_obj , PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6);

		template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T>
		static void BLKD_StubObserverAttach_processObserverID( const BLKS_COMMONID* type_id, OBJ_T* pc_obj, ABSTRUCT_OBSERVER_T*& apic_observer, OBSERVER_ID_T& observer_id, uint32_t& observer_instance_id );

		template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T >
		static void BLKD_StubAttach_pre( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );

		template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T >
		static void BLKD_StubAttach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );

		template<typename OBJ_T, typename RET_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T >
		static void BLKD_StubAttach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, RET_T ret, ABSTRUCT_OBSERVER_T*& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );

		template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T >
		static void BLKD_StubDetach_pre( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );

		template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T >
		static void BLKD_StubDetach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );

		template<typename OBJ_T, typename RET_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T >
		static void BLKD_StubDetach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, RET_T ret, ABSTRUCT_OBSERVER_T*& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );
};

template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
void BLKC_StubMethodTemplate::BLKD_StubNewinstance_pre( BLKS_COMMONID* type_id , OBJ_T*& pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 )
{
    uchar* data_pt = (uchar*)pt;

    short size = 0;

	CALL_MARSHALDISP_FUNC()

	data_pt = getUnmarshalWrapper()->unmarshalParams(data_pt, &size, type_id, para1, para2, para3, para4, para5, para6 );
}

template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
void BLKC_StubMethodTemplate::BLKD_StubNewinstance_post( BLKS_COMMONID* type_id , OBJ_T*& pc_obj , void*& pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6)
{
	BLKC_ConnectManager* c_connectMgr = BLKC_StubManager::getInstance()->getConnectManager(type_id->SessionID);

	BLKF_checkConnectManagerInstance(c_connectMgr, type_id);
	
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)
	
    uchar* data_pt = (uchar*)sendbuf;

    short size = 0;

    type_id->InstanceID = c_connectMgr->getNewInstanceID(pc_obj);

    data_pt = getMarshalWrapper()->marshalParams(data_pt, &size, type_id, para1, para2, para3, para4, para5, para6);

    int i_ret = c_connectMgr->sendRply( sendbuf , size );

	LOG_INFO("send reply to proxy %d byte C_ID: %d - S_ID: %d - I_ID: %d", i_ret, type_id->ClassMethodID, type_id->SessionID, type_id->InstanceID);
}

template<typename OBJ_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T >
void BLKC_StubMethodTemplate::BLKD_StubParaType_pre( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt,
															  PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
															  PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
															  PARA12_T& para12, PARA13_T& para13, PARA14_T& para14, PARA15_T& para15, PARA16_T& para16 )
{
	uchar *data_pt = (uchar*)pt;

	short ss_datasize = 0;
	
	CALL_MARSHALDISP_FUNC()

	data_pt = getUnmarshalWrapper()->unmarshalParams(data_pt, &ss_datasize, type_id,
					para1, para2, para3, para4, para5, para6, 
					para7, para8, para9, para10, para11, 
					para12, para13, para14, para15, para16 );
}

template<typename OBJ_T, typename RET_T, 
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T >
void BLKC_StubMethodTemplate::BLKD_StubParaType_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, RET_T ret,
															 PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
															 PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
															 PARA12_T& para12, PARA13_T& para13, PARA14_T& para14, PARA15_T& para15, PARA16_T& para16 )
{
	BLKC_ConnectManager* c_connectMgr = BLKC_StubManager::getInstance()->getConnectManager(type_id->SessionID);

	BLKF_checkConnectManagerInstance(c_connectMgr, type_id);

	uchar *sendbuf = NULL;

	BLKD_ALLOCATE_SENDBUFFER(sendbuf)
	
	uchar* data_pt = (uchar*)sendbuf;
	short ss_datasize = 0;

	data_pt = getMarshalWrapper()->marshalParams(data_pt, &ss_datasize, type_id,
												 para1, para2, para3, para4, para5, para6, 
												 para7, para8, para9, para10, para11, 
												 para12, para13, para14, para15, para16);

	data_pt = (uchar*)getMarshalWrapper()->marshal( data_pt , ret , &ss_datasize );

	int i_ret = c_connectMgr->sendRply( sendbuf , ss_datasize );

	LOG_INFO("send reply to proxy %d byte C_ID: %d - S_ID: %d - I_ID: %d", i_ret, type_id->ClassMethodID, type_id->SessionID, type_id->InstanceID);
}

template<typename OBJ_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T >
void BLKC_StubMethodTemplate::BLKD_StubParaType_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt,
															 PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
															 PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
															 PARA12_T& para12, PARA13_T& para13, PARA14_T& para14, PARA15_T& para15, PARA16_T& para16 )
{
	BLKC_ConnectManager* c_connectMgr = BLKC_StubManager::getInstance()->getConnectManager(type_id->SessionID);

    BLKF_checkConnectManagerInstance(c_connectMgr, type_id);

	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)
	
	uchar* data_pt = (uchar*)sendbuf;
	short ss_datasize = 0;

	data_pt = getMarshalWrapper()->marshalParams(data_pt, &ss_datasize, type_id,
												 para1, para2, para3, para4, para5, para6, 
												 para7, para8, para9, para10, para11, 
												 para12, para13, para14, para15, para16);

	int i_ret = c_connectMgr->sendRply( sendbuf , ss_datasize );

	LOG_INFO("send reply to proxy %d byte C_ID: %d - S_ID: %d - I_ID: %d", i_ret, type_id->ClassMethodID, type_id->SessionID, type_id->InstanceID);
}

template<typename RET_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
void BLKC_StubMethodTemplate::BLKD_StubCallBack( uint32_t upperCBID,RET_T& ret, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 )
{
	uint32_t ClassMethodID = UISEP_CALLBACK_METHOD;
	uint32_t InstanceID = BLKD_CALLBACK_ID;
	uint32_t SessionID = 0;

	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	short size = 0;

	uint32_t wcbid;
	uchar *pt;

	CallBackContainer& callback_container = BLKC_ConnectManager::getCallBackContainer();
	bool result = callback_container.begin( upperCBID, wcbid, SessionID);
	while(result == true){
		pt = (uchar*)sendbuf;
		pt = getMarshalWrapper()->marshalParams(pt, &size, ClassMethodID, InstanceID, SessionID, wcbid, para1, para2, para3, para4, para5, para6);

		BLKC_ConnectManager::sendCallBack( SessionID, sendbuf, size );

		LOG_INFO("send callback reply to proxy C_ID: %d - S_ID: %d - I_ID: %d", ClassMethodID, SessionID, InstanceID);

		pt = (uchar*)sendbuf;
		pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, ClassMethodID, InstanceID, SessionID, wcbid, para1, para2, para3, para4, para5, para6);

		pt = (uchar*)getUnmarshalWrapper()->unmarshal(pt, ret, &size);

		result = callback_container.next(wcbid, SessionID);
	}
}


template<typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
void BLKC_StubMethodTemplate::BLKD_StubCallBack( uint32_t upperCBID, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 )
{
	uint32_t ClassMethodID = UISEP_CALLBACK_METHOD;
	uint32_t InstanceID = BLKD_CALLBACK_ID;
	uint32_t SessionID = 0;

	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	short size = 0;
	uint32_t wcbid;
	uchar *pt;

	CallBackContainer& callback_container = BLKC_ConnectManager::getCallBackContainer();
	bool result = callback_container.begin( upperCBID , wcbid, SessionID);
	while(result == true){
		pt = (uchar*)sendbuf;
		pt = getMarshalWrapper()->marshalParams(pt, &size, ClassMethodID, InstanceID, SessionID, wcbid, para1, para2, para3, para4, para5, para6);

		LOG_INFO("send callback reply to proxy CallBackId: %d", wcbid);
		BLKC_ConnectManager::sendCallBack( SessionID, sendbuf, size );
		LOG_INFO("recv callback reply from proxy CallBackId: %d", wcbid);

		pt = (uchar*)sendbuf;
		pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, ClassMethodID, InstanceID, SessionID, wcbid, para1, para2, para3, para4, para5, para6);

		result = callback_container.next( wcbid, SessionID);
	}
}

template<typename OBJ_T, typename RET_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
void BLKC_StubMethodTemplate::BLKD_StubNotify( uint32_t ClassMethodID, OBJ_T* pc_obj , RET_T& ret, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4)
{	
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	uchar* pt = NULL;
	short size = 0;
	bool b_retry = false;
	do {
		pt = sendbuf;
		size = 0;
		BLKS_COMMONID type_id;
		BLKS_COMMONID* ptype_id = &type_id;	
		BLKS_COMMONID*& _type_id = ptype_id;

		type_id.ClassMethodID = ClassMethodID;
		type_id.InstanceID = BLKC_ConnectManager::findInstanceId( pc_obj->SessionID, pc_obj);
		type_id.SessionID = pc_obj->SessionID;

		if ( pc_obj->getRegistFlg() == false ) {
			type_id.InstanceID = BLKD_PRE_OBSERVER_ID;
		}

		pt = getMarshalWrapper()->marshalParams(pt, &size, _type_id, para1, para2, para3, para4);

		BLKC_ConnectManager::sendObserverNotify( type_id.SessionID, sendbuf, size);

		pt = sendbuf;
	
		pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, ptype_id->ClassMethodID, ptype_id->InstanceID, ptype_id->SessionID, para1, para2, para3, para4);

		if ( ptype_id->InstanceID == BLKD_NOTPRE_OBSERVER_ID ) {
			b_retry = true;
		}
		else {
			b_retry = false;
		}
	} while( b_retry );

	pt = (uchar*)getUnmarshalWrapper()->unmarshal(pt, ret, &size);
}

template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
void BLKC_StubMethodTemplate::BLKD_StubNotify( uint32_t ClassMethodID, OBJ_T* pc_obj , PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4)
{
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	if ( NULL != sendbuf ) {
		uchar* pt = NULL;
		short size = 0;
		bool b_retry = false;
		do {
			pt = sendbuf;
			size = 0;
			BLKS_COMMONID type_id;
			BLKS_COMMONID* ptype_id = &type_id;	
			BLKS_COMMONID*& _type_id = ptype_id;

			type_id.ClassMethodID = ClassMethodID;
			type_id.InstanceID = BLKC_ConnectManager::findInstanceId( pc_obj->SessionID, pc_obj);
			type_id.SessionID = pc_obj->SessionID;

			if ( pc_obj->getRegistFlg() == false ) {
				type_id.InstanceID = BLKD_PRE_OBSERVER_ID;
			}

			pt = getMarshalWrapper()->marshalParams(pt, &size, _type_id, para1, para2, para3, para4);

			BLKC_ConnectManager::sendObserverNotify( type_id.SessionID, sendbuf, size);
			pt = sendbuf;

			pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, ptype_id->ClassMethodID, ptype_id->InstanceID, ptype_id->SessionID, para1, para2, para3, para4);

			if ( ptype_id->InstanceID == BLKD_NOTPRE_OBSERVER_ID ) {
				b_retry = true;
			}
			else {
				b_retry = false;
			}
		} while( b_retry );
	} else {
		LOG_ERROR("allocate() is NULL.");
		exit( EXIT_FAILURE );
	}

}

template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
void BLKC_StubMethodTemplate::BLKD_StubNotify( uint32_t ClassMethodID, OBJ_T* pc_obj , PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6)
{
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	uchar* pt = NULL;
	short size = 0;
	bool b_retry = false;
	do {
		pt = sendbuf;
		size = 0;
		BLKS_COMMONID type_id;
		BLKS_COMMONID* ptype_id = &type_id;	
		BLKS_COMMONID*& _type_id = ptype_id;

		type_id.ClassMethodID = ClassMethodID;
		type_id.InstanceID = BLKC_ConnectManager::findInstanceId( pc_obj->SessionID, pc_obj);
		type_id.SessionID = pc_obj->SessionID;

		if ( pc_obj->getRegistFlg() == false ) {
			type_id.InstanceID = BLKD_PRE_OBSERVER_ID;
		}

		pt = getMarshalWrapper()->marshalParams(pt, &size, _type_id, para1, para2, para3, para4, para5, para6);

		BLKC_ConnectManager::sendObserverNotify( type_id.SessionID, sendbuf, size);

		pt = sendbuf;
	
		pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, ptype_id->ClassMethodID, ptype_id->InstanceID, ptype_id->SessionID, para1, para2, para3, para4, para5, para6);

		if ( ptype_id->InstanceID == BLKD_NOTPRE_OBSERVER_ID ) {
			b_retry = true;
		}
		else {
			b_retry = false;
		}
	} while( b_retry );
}

template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T >
void BLKC_StubMethodTemplate::BLKD_StubObserverAttach_processObserverID( const BLKS_COMMONID* type_id, OBJ_T* pc_obj, ABSTRUCT_OBSERVER_T*& apic_observer, OBSERVER_ID_T& observer_id, uint32_t& observer_instance_id )
{
	BLKC_ConnectManager* c_connectMgr = BLKC_StubManager::getInstance()->getConnectManager(type_id->SessionID);

	BLKF_checkConnectManagerInstance(c_connectMgr, type_id);

	OBSERVER_T* observer_imp_obj;
	
	ObserverDestructor* obs_des = (ObserverDestructor*)c_connectMgr->findObserverObject( observer_id );
	if(obs_des == NULL){
		LOG_INFO("Observer, new observer");
		observer_imp_obj = new OBSERVER_T(type_id->SessionID);
		apic_observer = (ABSTRUCT_OBSERVER_T*)observer_imp_obj;
		obs_des = (ObserverDestructor*)observer_imp_obj;
		observer_id = c_connectMgr->resistObserverObject( obs_des );
		observer_instance_id = c_connectMgr->getNewInstanceID( apic_observer );
	}else{
		observer_imp_obj = (OBSERVER_T*)obs_des;
		apic_observer = (ABSTRUCT_OBSERVER_T*)observer_imp_obj;
		observer_instance_id = c_connectMgr->findInstanceId(apic_observer);
		LOG_INFO("Observer, exist observer");
	}
	                
	observer_imp_obj->setSubject( pc_obj );
}

template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T >
void BLKC_StubMethodTemplate::BLKD_StubAttach_pre( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										 PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										 PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										 PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 )
{
	CALL_MARSHALDISP_FUNC()
	
	uchar *data_pt = (uchar*)pt;
	short ss_datasize = 0;

	OBSERVER_ID_T	observer_id = 0;
	uint32_t	observer_instance_id = 0;
	bool isNULLObserver = false;

	data_pt = getUnmarshalWrapper()->unmarshalParams( data_pt, &ss_datasize, type_id, observer_id,
	                                                  para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                                  para9, para10, para11, para12, para13, para14, isNULLObserver );
	if( isNULLObserver ) {
		apic_observer = NULL;
		return;
	}

	BLKD_StubObserverAttach_processObserverID<OBJ_T, ABSTRUCT_OBSERVER_T, OBSERVER_T>(type_id, pc_obj, apic_observer, observer_id, observer_instance_id );
}

template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T >
void BLKC_StubMethodTemplate::BLKD_StubAttach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										  PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										  PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										  PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 )
{
	BLKD_StubAttach_post< OBJ_T, void*, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			PARA1_T, PARA2_T, PARA3_T, PARA4_T, PARA5_T, PARA6_T, PARA7_T, PARA8_T, PARA9_T, PARA10_T, PARA11_T, PARA12_T, PARA13_T, PARA14_T >
		( type_id, pc_obj, pt, mMarshalDummy, apic_observer,
			para1, para2, para3, para4, para5, para6, para7, para8, para9, para10, para11, para12, para13, para14 );
}

template<typename OBJ_T, typename RET_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T >
void BLKC_StubMethodTemplate::BLKD_StubAttach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, RET_T ret, ABSTRUCT_OBSERVER_T*& apic_observer,
										  PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										  PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										  PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 )
{
	BLKC_ConnectManager* c_connectMgr = BLKC_StubManager::getInstance()->getConnectManager(type_id->SessionID);		// マルチスレッド対応 新規追加.

	BLKF_checkConnectManagerInstance(c_connectMgr, type_id);

	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	uchar* data_pt = (uchar*)sendbuf;
	short ss_datasize = 0;

	ObserverDestructor* obs_des;
	OBSERVER_T* observer_imp_obj;
	OBSERVER_ID_T observer_id = 0;
	uint32_t observer_instance_id = 0;

	if( apic_observer != NULL){
		observer_imp_obj = (OBSERVER_T*)apic_observer;
		obs_des = (ObserverDestructor*)observer_imp_obj;
		observer_id = c_connectMgr->findObserverId( obs_des );
		observer_instance_id = BLKC_ConnectManager::findInstanceId( type_id->SessionID, apic_observer );
	}

	data_pt = getMarshalWrapper()->marshalParams( data_pt, &ss_datasize, type_id, observer_id, observer_instance_id,
	                                              para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                              para9, para10, para11, para12, para13, para14 );

	data_pt = (uchar*)getMarshalWrapper()->marshal( data_pt , ret , &ss_datasize );

	c_connectMgr->sendRply( sendbuf , ss_datasize );

	if( apic_observer != NULL )
	{
		((OBSERVER_T*)apic_observer)->setRegistFlg( true );
	}

}

template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T >
void BLKC_StubMethodTemplate::BLKD_StubDetach_pre( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										 PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										 PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										 PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 )
{
	CALL_MARSHALDISP_FUNC()
	
	BLKC_ConnectManager* c_connectMgr = BLKC_StubManager::getInstance()->getConnectManager(type_id->SessionID);

	BLKF_checkConnectManagerInstance(c_connectMgr, type_id);

	uchar *data_pt = (uchar*)pt;
	short ss_datasize = 0;
	OBSERVER_T*		observer_imp_obj;
	OBSERVER_ID_T	observer_id = 0;
	bool isNULLObserver = false;

	data_pt = getUnmarshalWrapper()->unmarshalParams( data_pt, &ss_datasize, type_id, observer_id,
	                                                  para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                                  para9, para10, para11, para12, para13, para14, isNULLObserver );
	if ( isNULLObserver ) {
		apic_observer = NULL;
	}
	else {
		ObserverDestructor* obs_des = (ObserverDestructor*)c_connectMgr->findObserverObject( observer_id );
		observer_imp_obj = (OBSERVER_T*)obs_des;
		apic_observer = (ABSTRUCT_OBSERVER_T*)observer_imp_obj;
	}
}

template<typename OBJ_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T >
void BLKC_StubMethodTemplate::BLKD_StubDetach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, ABSTRUCT_OBSERVER_T*& apic_observer,
										  PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										  PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										  PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 )
{
	BLKD_StubDetach_post< OBJ_T, void*, ABSTRUCT_OBSERVER_T, OBSERVER_T,
			PARA1_T, PARA2_T, PARA3_T, PARA4_T, PARA5_T, PARA6_T, PARA7_T, PARA8_T, PARA9_T, PARA10_T, PARA11_T, PARA12_T, PARA13_T, PARA14_T >
		( type_id, pc_obj, pt, mMarshalDummy, apic_observer,
			para1, para2, para3, para4, para5, para6, para7, para8, para9, para10, para11, para12, para13, para14 );
}


template<typename OBJ_T, typename RET_T, typename ABSTRUCT_OBSERVER_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T >
void BLKC_StubMethodTemplate::BLKD_StubDetach_post( BLKS_COMMONID* type_id, OBJ_T* pc_obj, void* pt, RET_T ret, ABSTRUCT_OBSERVER_T*& apic_observer,
										  PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										  PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										  PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 )
{
	BLKC_ConnectManager* c_connectMgr = BLKC_StubManager::getInstance()->getConnectManager(type_id->SessionID);

	BLKF_checkConnectManagerInstance(c_connectMgr, type_id);

	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	uchar* data_pt = (uchar*)sendbuf;
	short ss_datasize = 0;

	OBSERVER_T* observer_obj;
	OBSERVER_ID_T observer_id = 0;
	ObserverDestructor* obs_des;
	uint32_t observer_instance_id = 0;

	if( apic_observer != NULL){
		observer_obj = (OBSERVER_T*)apic_observer;
		obs_des = (ObserverDestructor*)observer_obj;
		observer_id = c_connectMgr->findObserverId( obs_des );
		observer_instance_id = c_connectMgr->findInstanceId( apic_observer );
		observer_obj = (OBSERVER_T*)apic_observer;
		observer_obj->deleteSubject(pc_obj);
		c_connectMgr->deleteObserverObject( observer_id );
		c_connectMgr->deleteInstanceId( observer_instance_id );
	}

	data_pt = getMarshalWrapper()->marshalParams( data_pt, &ss_datasize, type_id, observer_id, observer_instance_id,
	                                              para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                              para9, para10, para11, para12, para13, para14 );

	data_pt = (uchar*)getMarshalWrapper()->marshal( data_pt , ret , &ss_datasize );

	c_connectMgr->sendRply( sendbuf , ss_datasize );
}

#endif