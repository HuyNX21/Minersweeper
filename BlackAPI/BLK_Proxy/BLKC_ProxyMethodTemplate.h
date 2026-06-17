#ifndef __BLKC_PROXYMETHODTEMPLATE_H__
#define __BLKC_PROXYMETHODTEMPLATE_H__

#include "BLKC_Common.h"
#include "BLKC_ProxyManager.h"
#include "AllocateMemory.h"
#include "BLKC_MarshalWrapper.h"
#include "BLKC_UnmarshalWrapper.h"

class BLKC_MarshalWrapper;
class BLKC_UnmarshalWrapper;

#define BLKD_ALLOCATE_SENDBUFFER(buf) AllocateMemory<uchar> send_mem( sizeof(BLKS_MSG_FORMAT) ); \
												buf = (send_mem.allocate()==NULL)? NULL:send_mem.getTopAddress()+BLKD_MSGHEAD_SIZE;

class BLKC_ProxyMethodTemplate
{
    public:
        static BLKC_MarshalWrapper*     getMarshalWrapper();
	    static BLKC_UnmarshalWrapper*   getUnmarshalWrapper();

        template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
	    static void BLKD_ProxyNewinstance_Singleton(uint32_t ClassMethodID, OBJ_T*& ret, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6);

        template<typename OBJ_T, typename RET_T,
			 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
			 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
			 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T> 
        static void BLKD_ProxyParaType(uint32_t ClassMethodID, OBJ_T* pc_obj, RET_T &ret,
                                        PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
                                        PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
                                        PARA12_T& para12,PARA13_T& para13,PARA14_T& para14,PARA15_T& para15,PARA16_T& para16);

        template<typename OBJ_T,
			 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
			 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
			 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T> 
        static void BLKD_ProxyParaType(uint32_t ClassMethodID, OBJ_T* pc_obj,
                                        PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
                                        PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
                                        PARA12_T& para12,PARA13_T& para13,PARA14_T& para14,PARA15_T& para15,PARA16_T& para16);

        template< typename FUNC_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
        static void BLKD_ProxyCallBack_pre( BLKS_COMMONID* type_id , uint32_t* p_callbackID, FUNC_T* pc_func, void* pt,
                                            PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 );
							
		template< typename RET_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
		static void BLKD_ProxyCallBack_post( BLKS_COMMONID* type_id, uint32_t p_callbackID, void* pt, RET_T& ret,
											PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 );

		template< typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
		static void BLKD_ProxyCallBack_post( BLKS_COMMONID* type_id, uint32_t p_callbackID, void* pt,
											PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 );

		template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
		static void BLKD_ProxyNotify_pre( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4);

		template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T>
		static void BLKD_ProxyNotify_pre( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5);

		template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
		static void BLKD_ProxyNotify_pre( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6);

		template<typename OBJ_T,typename RET_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
		static void BLKD_ProxyNotify_post( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, RET_T &ret, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4);

		template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
		static void BLKD_ProxyNotify_post( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4);

		template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
		static void BLKD_ProxyNotify_post( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6);

		template<typename OBJ_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T> 
		static void BLKD_ProxyAttach(uint32_t ClassMethodID, OBJ_T* pc_obj, OBSERVER_T& apic_observer,
										PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
										PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
										PARA12_T& para12,PARA13_T& para13,PARA14_T& para14);

		template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T> 
		static void BLKD_ProxyAttach(uint32_t ClassMethodID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
										PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
										PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
										PARA12_T& para12,PARA13_T& para13,PARA14_T& para14);

		template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T> 
		static void BLKD_ProxyAttach( uint32_t ClassMethodID, uint32_t& InstanceID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );

		template<typename OBJ_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T> 
		static void BLKD_ProxyDetach(uint32_t ClassMethodID, OBJ_T* pc_obj, OBSERVER_T& apic_observer,
										PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
										PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
										PARA12_T& para12,PARA13_T& para13,PARA14_T& para14);

		template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T> 
		static void BLKD_ProxyDetach(uint32_t ClassMethodID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
										PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
										PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
										PARA12_T& para12,PARA13_T& para13,PARA14_T& para14);

		template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
				typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
				typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
				typename PARA12_T, typename PARA13_T, typename PARA14_T> 
		static void BLKD_ProxyDetach( uint32_t ClassMethodID, uint32_t& InstanceID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
										PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
										PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
										PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 );

    private:
        static BLKC_MarshalWrapper* mMarshalWrapper;
        static BLKC_UnmarshalWrapper* mUnmarshalWrapper;
};

template<typename OBJ_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
void BLKC_ProxyMethodTemplate::BLKD_ProxyNewinstance_Singleton(uint32_t ClassMethodID, OBJ_T*& ret,PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6)
{
    BLKS_COMMONID* type_id = new BLKS_COMMONID{0};
    uint32_t InstanceID = BLKD_STATIC_METHOD_ID;
    uint32_t SessionID = 0;
    short size = 0;
    uchar *pt;

    static OBJ_T* p_ret = NULL;
	if( p_ret != NULL ) {
		ret = p_ret;
		return;
	}

    BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();

    uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

    pt = (uchar*)sendbuf;

    LOG_DEBUG("Before send get new instance C_ID: %d - S_ID: %d - I_ID: %d", ClassMethodID, SessionID, InstanceID);

    type_id->ClassMethodID  = ClassMethodID;
    type_id->InstanceID     = InstanceID;
    type_id->SessionID      = SessionID;
    pt = getMarshalWrapper()->marshalParams(pt, &size, type_id, para1, para2, para3, para4, para5, para6);
    
    c_proxyMgr->Send_ProxyMgr( sendbuf , size );

    pt = (uchar*)sendbuf;

    pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, type_id, para1, para2, para3, para4, para5, para6 );
    ClassMethodID   = type_id->ClassMethodID;
    InstanceID      = type_id->InstanceID;
    SessionID       = type_id->SessionID;

    LOG_DEBUG("After send get new instance C_ID: %d - S_ID: %d - I_ID: %d", ClassMethodID, SessionID, InstanceID);

    ret = (OBJ_T*)c_proxyMgr->getObject(InstanceID);

	if (ret == NULL && InstanceID != 0)
	{
		ret = new OBJ_T;
		c_proxyMgr->setInstanceId( InstanceID, ret );
		ret->InstanceID = InstanceID;
	}

	p_ret = ret;
}

template<typename OBJ_T, typename RET_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyParaType(uint32_t ClassMethodID, OBJ_T* pc_obj, RET_T &ret,
													PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
													PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
													PARA12_T& para12,PARA13_T& para13,PARA14_T& para14,PARA15_T& para15,PARA16_T& para16)
{
	BLKS_COMMONID* type_id = new BLKS_COMMONID{0};
    uint32_t SessionID = 0;
    uchar *sendbuf = NULL;
    uchar *pt;
    short size = 0;

    BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
    
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)
    pt = (uchar*)sendbuf;

    if ((ClassMethodID == 0x009c0001) && (sendbuf == NULL)) {
		LOG_ERROR("Failed to allocate(getChannelStatus)\n");
		return;
	}

    uint32_t uDataIndex = c_proxyMgr->reserveSyncObject();

    LOG_INFO("marshal and send message to stub C_ID: %d - S_ID: %d - I_ID: %d", ClassMethodID, SessionID, pc_obj->InstanceID);

	type_id->ClassMethodID  = ClassMethodID;
    type_id->InstanceID     = pc_obj->InstanceID;
    type_id->SessionID      = SessionID;
    pt = getMarshalWrapper()->marshalParams(pt, &size, type_id, para1, para2, para3, para4, para5, para6, 
											para7, para8, para9, para10, para11, 
											para12, para13, para14, para15, para16);

    c_proxyMgr->readySyncObject( uDataIndex );

    c_proxyMgr->Send_ProxyMgr( sendbuf ,  size );

    pt = (uchar*)sendbuf;

    pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, type_id, para1, para2, para3, para4, para5, para6, 
												para7, para8, para9, para10, para11, 
												para12, para13, para14, para15, para16);

    pt = (uchar*)getUnmarshalWrapper()->unmarshal( pt, ret, &size );

    LOG_INFO("receive reply from stub C_ID: %d - S_ID: %d - I_ID: %d", type_id->ClassMethodID, type_id->SessionID, type_id->InstanceID);

	c_proxyMgr->signalSyncObject( uDataIndex );
}

template<typename OBJ_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T, typename PARA15_T, typename PARA16_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyParaType(uint32_t ClassMethodID, OBJ_T* pc_obj,
													PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
													PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
													PARA12_T& para12,PARA13_T& para13,PARA14_T& para14,PARA15_T& para15,PARA16_T& para16)
{
	BLKS_COMMONID* type_id = new BLKS_COMMONID{0};
	uint32_t SessionID = 0;
    uchar *sendbuf = NULL;
    uchar *pt;
    short size = 0;

    BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
    
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)
    pt = (uchar*)sendbuf;

	uint32_t uDataIndex = c_proxyMgr->reserveSyncObject();

    LOG_INFO("marshal and send message to stub C_ID: %d - S_ID: %d - I_ID: %d", ClassMethodID, SessionID, pc_obj->InstanceID);

	type_id->ClassMethodID  = ClassMethodID;
    type_id->InstanceID     = pc_obj->InstanceID;
    type_id->SessionID      = SessionID;
	pt = getMarshalWrapper()->marshalParams(pt, &size, type_id,
											para1, para2, para3, para4, para5, para6, 
											para7, para8, para9, para10, para11, 
											para12, para13, para14, para15, para16);
	
	c_proxyMgr->readySyncObject( uDataIndex );

	c_proxyMgr->Send_ProxyMgr( sendbuf ,  size );

	pt = (uchar*)sendbuf;

	pt = getUnmarshalWrapper()->unmarshalParams(pt, &size, type_id,
												para1, para2, para3, para4, para5, para6, 
												para7, para8, para9, para10, para11, 
												para12, para13, para14, para15, para16);

    LOG_INFO("receive reply from stub C_ID: %d - S_ID: %d - I_ID: %d", type_id->ClassMethodID, type_id->SessionID, type_id->InstanceID);

	c_proxyMgr->signalSyncObject( uDataIndex );

}

// callback - front
template< typename FUNC_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
void BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_pre( BLKS_COMMONID* type_id, uint32_t* p_callbackID, FUNC_T* pc_func, void* pt,
												 PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 )
{
	uchar* data_pt = (uchar*)pt;
	short ss_datasize = 0;
	uint32_t ulCallBackId = 0;

	data_pt = getUnmarshalWrapper()->unmarshalParams( data_pt, &ss_datasize, type_id, ulCallBackId, para1, para2, para3, para4, para5, para6 );

	*pc_func = (FUNC_T)BLKC_ProxyManager::getInstance()->getCallBackFP( ulCallBackId );
	*p_callbackID = ulCallBackId;

	LOG_INFO("send callback reply pre CallBackId: %d", ulCallBackId);
}

// callback - post
template< typename RET_T, typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
void BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_post( BLKS_COMMONID* type_id, uint32_t ul_callbackID, void* pt, RET_T& ret, 
												PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 )
{
	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance(); 
	
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	short ss_datasize = 0;
	uchar* data_pt = (uchar*)pt;

	data_pt = (uchar*)sendbuf;
	data_pt = getMarshalWrapper()->marshalParams( data_pt, &ss_datasize, type_id, ul_callbackID, para1, para2, para3, para4, para5, para6 );
	data_pt = (uchar*)getMarshalWrapper()->marshal( data_pt, ret, &ss_datasize );

	c_proxyMgr->deleteCallBackFP(ul_callbackID);

	LOG_INFO("send callback reply post CallBackId: %d", ul_callbackID);
	
	c_proxyMgr->SendRply_ProxyMgr( sendbuf, ss_datasize );
}

template< typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T >
void BLKC_ProxyMethodTemplate::BLKD_ProxyCallBack_post( BLKS_COMMONID* type_id, uint32_t ul_callbackID, void* pt,
												 PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6 )
{
	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance(); 
	
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	short ss_datasize = 0;
	uchar* data_pt = (uchar*)pt;

	data_pt = (uchar*)sendbuf;
	data_pt = getMarshalWrapper()->marshalParams( data_pt, &ss_datasize, type_id, ul_callbackID, para1, para2, para3, para4, para5, para6 );

	c_proxyMgr->deleteCallBackFP(ul_callbackID);

	LOG_INFO("send callback reply post CallBackId: %d", ul_callbackID);

	c_proxyMgr->SendRply_ProxyMgr( sendbuf , ss_datasize );
}

template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
void BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_pre( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4)
{
	uchar* data_pt = (uchar*)pt;
	short ss_datasize = 0;

	data_pt = getUnmarshalWrapper()->unmarshalParams<BLKS_COMMONID*,PARA1_T, PARA2_T, PARA3_T, PARA4_T>(data_pt, &ss_datasize, type_id, para1, para2, para3, para4 );
}

template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T>
void BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_pre( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5)
{
	uchar* data_pt = (uchar*)pt;
	short ss_datasize = 0;

	data_pt = getUnmarshalWrapper()->unmarshalParams<BLKS_COMMONID*,PARA1_T, PARA2_T, PARA3_T, PARA4_T, PARA5_T>(data_pt, &ss_datasize, type_id, para1, para2, para3, para4, para5);
}

template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
void BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_pre( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6)
{
	uchar* data_pt = (uchar*)pt;
	short ss_datasize = 0;

	data_pt = getUnmarshalWrapper()->unmarshalParams<BLKS_COMMONID*,PARA1_T, PARA2_T, PARA3_T, PARA4_T, PARA5_T, PARA6_T>(data_pt, &ss_datasize, type_id, para1, para2, para3, para4, para5, para6 );
}

template<typename OBJ_T,typename RET_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
void BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_post( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, RET_T& ret, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4)
{
	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
	
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	uchar* data_pt = (uchar*)pt;
	short ss_datasize = 0;

	data_pt = (uchar*)sendbuf;

	data_pt = getMarshalWrapper()->marshalParams<BLKS_COMMONID*,PARA1_T, PARA2_T, PARA3_T, PARA4_T>(data_pt, &ss_datasize, type_id, para1, para2, para3, para4);

	data_pt = (uchar*)getMarshalWrapper()->marshal( data_pt, ret, &ss_datasize );

	c_proxyMgr->SendRply_ProxyMgr( sendbuf , ss_datasize );
}

template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T>
void BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_post( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4)
{
	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance(); 
	
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	uchar* data_pt = (uchar*)pt;
	short ss_datasize = 0;

	data_pt = (uchar*)sendbuf;

	data_pt = getMarshalWrapper()->marshalParams<BLKS_COMMONID*, PARA1_T, PARA2_T, PARA3_T, PARA4_T >(data_pt, &ss_datasize, type_id, para1, para2, para3, para4);

	c_proxyMgr->SendRply_ProxyMgr( sendbuf , ss_datasize );
}

template<typename OBJ_T,typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T>
void BLKC_ProxyMethodTemplate::BLKD_ProxyNotify_post( BLKS_COMMONID* type_id , OBJ_T* pc_obj, void* pt, PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6)
{
	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance(); 
	
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	uchar* data_pt = (uchar*)pt;
	short ss_datasize = 0;

	data_pt = (uchar*)sendbuf;

	data_pt = getMarshalWrapper()->marshalParams<BLKS_COMMONID*, PARA1_T, PARA2_T, PARA3_T, PARA4_T, PARA5_T, PARA6_T >(data_pt, &ss_datasize, type_id, para1, para2, para3, para4, para5, para6);

	c_proxyMgr->SendRply_ProxyMgr( sendbuf , ss_datasize );
}

template<typename OBJ_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyAttach(uint32_t ClassMethodID, OBJ_T* pc_obj, OBSERVER_T& apic_observer,
								PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
								PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
								PARA12_T& para12,PARA13_T& para13,PARA14_T& para14)
{
	BLKD_ProxyAttach( ClassMethodID, pc_obj->InstanceID, pc_obj, mMarshalDummy, apic_observer,
					para1,  para2, para3, para4, para5,
					para6,  para7, para8, para9, para10,
					para11,  para12, para13, para14 );
}

template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyAttach(uint32_t ClassMethodID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
								PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
								PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
								PARA12_T& para12,PARA13_T& para13,PARA14_T& para14)
{
	BLKD_ProxyAttach( ClassMethodID, pc_obj->InstanceID, pc_obj, ret, apic_observer,
					para1,  para2, para3, para4, para5,
					para6,  para7, para8, para9, para10,
					para11,  para12, para13, para14 );
}

template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyAttach( uint32_t ClassMethodID, uint32_t& InstanceID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
								PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
								PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
								PARA12_T& para12, PARA13_T& para13, PARA14_T& para14 )
{
	bool isNULLObserver = false;
	if( apic_observer == NULL )
	{
		isNULLObserver = true;
	}

	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)

	short size = 0;
	uint32_t SessionID = 0;
	uchar* pt = (uchar*)sendbuf;

	uint32_t uDataIndex = c_proxyMgr->reserveSyncObject();

	OBSERVER_ID_T observer_id = 0;
	if( !isNULLObserver )
	{
		observer_id  = (OBSERVER_ID_T)c_proxyMgr->findObserverId( apic_observer );

		c_proxyMgr->setInstanceId( BLKD_PRE_OBSERVER_ID, apic_observer );

		if( observer_id == 0 )
		{
			c_proxyMgr->addSyncObject( &typeid( apic_observer ) );
		}
	}

	pt = getMarshalWrapper()->marshalParams( pt, &size, ClassMethodID, InstanceID, SessionID, observer_id, 
	                                         para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                         para9, para10, para11, para12, para13, para14, isNULLObserver );
	
	c_proxyMgr->readySyncObject( uDataIndex );
	c_proxyMgr->Send_ProxyMgr( sendbuf,  size );
	pt = (uchar*)sendbuf;
	
	uint32_t instance_id = 0;
	pt = getUnmarshalWrapper()->unmarshalParams( pt, &size, ClassMethodID, InstanceID, SessionID, observer_id, instance_id ,
		                                         para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                             para9, para10, para11, para12, para13, para14 );

	if( !isNULLObserver )
	{
		c_proxyMgr->addObserverObject(observer_id, apic_observer);

		c_proxyMgr->deleteInstanceId( BLKD_PRE_OBSERVER_ID );

		c_proxyMgr->setInstanceId( instance_id, apic_observer );
	}

	pt = (uchar*)getUnmarshalWrapper()->unmarshal( pt, ret, &size );

	c_proxyMgr->signalSyncObject( uDataIndex );
}

template<typename OBJ_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyDetach(uint32_t ClassMethodID, OBJ_T* pc_obj, OBSERVER_T& apic_observer,
								PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
								PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
								PARA12_T& para12,PARA13_T& para13,PARA14_T& para14)
{
	BLKD_ProxyDetach( ClassMethodID, pc_obj->InstanceID, pc_obj, mMarshalDummy, apic_observer,
					para1,  para2, para3, para4, para5,
					para6,  para7, para8, para9, para10,
					para11,  para12, para13, para14 );
}

template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T,typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyDetach(uint32_t ClassMethodID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
								PARA1_T& para1,PARA2_T& para2,PARA3_T& para3,PARA4_T& para4,PARA5_T& para5,PARA6_T& para6,
								PARA7_T& para7,PARA8_T& para8,PARA9_T& para9,PARA10_T& para10,PARA11_T& para11,
								PARA12_T& para12,PARA13_T& para13,PARA14_T& para14)
{
	BLKD_ProxyDetach( ClassMethodID, pc_obj->InstanceID, pc_obj, ret, apic_observer,
					para1,  para2, para3, para4, para5,
					para6,  para7, para8, para9, para10,
					para11,  para12, para13, para14 );
}

template<typename OBJ_T, typename RET_T, typename OBSERVER_T,
		 typename PARA1_T, typename PARA2_T, typename PARA3_T, typename PARA4_T, typename PARA5_T, typename PARA6_T,
		 typename PARA7_T, typename PARA8_T, typename PARA9_T, typename PARA10_T, typename PARA11_T,
		 typename PARA12_T, typename PARA13_T, typename PARA14_T> 
void BLKC_ProxyMethodTemplate::BLKD_ProxyDetach(uint32_t ClassMethodID, uint32_t& InstanceID, OBJ_T* pc_obj, RET_T &ret, OBSERVER_T& apic_observer,
								PARA1_T& para1, PARA2_T& para2, PARA3_T& para3, PARA4_T& para4, PARA5_T& para5, PARA6_T& para6,
								PARA7_T& para7, PARA8_T& para8, PARA9_T& para9, PARA10_T& para10, PARA11_T& para11,
								PARA12_T& para12, PARA13_T& para13, PARA14_T& para14)
{
	bool isNULLObserver = false;
	if( apic_observer == NULL )
	{
		isNULLObserver = true;
	}

	BLKC_ProxyManager* c_proxyMgr = BLKC_ProxyManager::getInstance();
	uchar *sendbuf = NULL;
	BLKD_ALLOCATE_SENDBUFFER(sendbuf)
	short size = 0;
	uint32_t SessionID = 0;

	uchar* pt = (uchar*)sendbuf;

	OBSERVER_ID_T observer_id  = 0;

	if( !isNULLObserver )
	{
		observer_id  = (OBSERVER_ID_T)c_proxyMgr->findObserverId( apic_observer );

		if( observer_id == 0 )
		{
			c_proxyMgr->addSyncObject( &typeid( apic_observer ) );
		}
	}

	uint32_t uDataIndex = c_proxyMgr->reserveSyncObject();
	pt = getMarshalWrapper()->marshalParams( pt, &size, ClassMethodID, InstanceID, SessionID, observer_id, 
	                                         para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                         para9, para10, para11, para12, para13, para14, isNULLObserver );
	
	c_proxyMgr->readySyncObject( uDataIndex );
	c_proxyMgr->Send_ProxyMgr( sendbuf,  size );
	pt = (uchar*)sendbuf;
	
	uint32_t instance_id = 0;
	pt = getUnmarshalWrapper()->unmarshalParams( pt, &size, ClassMethodID, InstanceID, SessionID, observer_id, instance_id ,
		                                         para1, para2,  para3,  para4,  para5,  para6,  para7, para8, 
	                                             para9, para10, para11, para12, para13, para14 );

	if( !isNULLObserver )
	{
		c_proxyMgr->deleteInstanceId( instance_id );
		c_proxyMgr->deleteObserverObject( (OBSERVER_ID_T)observer_id );
	}

	pt = (uchar*)getUnmarshalWrapper()->unmarshal( pt, ret, &size );
	c_proxyMgr->signalSyncObject( uDataIndex );
}

#endif