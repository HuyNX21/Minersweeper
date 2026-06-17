#ifndef	_CLASS_CALLBACKCONTAINER_H_
#define	_CLASS_CALLBACKCONTAINER_H_

#include <map>

#include "BLKC_Common.h"

// コンテナの構造
// CALL_BACK_CONTAINER 
//  |---- Key: BLKD_PROXY_CBID_ANS_XXXの値（コールバック関数毎にユニーク）
//  |---- Value: CALL_BACK_VAL_CONTAINER
//                |---- Key: コールバックID (BLKD_PROXY_CBID_ANS_XXX + カウンタ値) proxyからもらう
//                |---- Value: セッションID コールバック登録したConnectManagerを特定する値
//
class CallBackContainer
{
	private:
		MutexLock mMutex;
		typedef std::multimap<uint32_t, uint32_t> CALL_BACK_VAL_CONTAINER;			
		typedef std::map<uint32_t, CALL_BACK_VAL_CONTAINER*> CALL_BACK_CONTAINER;	

		CALL_BACK_CONTAINER mContainer;
		CALL_BACK_VAL_CONTAINER::iterator mCurrentIterator;
		CALL_BACK_VAL_CONTAINER* mCurrentValContainer;

		bool getElement(CALL_BACK_VAL_CONTAINER::iterator it,
		                uint32_t& call_back_id,
		                uint32_t& session_id);
		                
		bool getContainer(uint32_t cbid_prefix, CALL_BACK_VAL_CONTAINER*& ret_container);
		                
		static const uint32_t CALL_BACK_ID_PREFIX_MASK;		
	
	public :
		CallBackContainer();
		virtual ~CallBackContainer();
		CallBackContainer* getInstance();
	
		bool regist(uint32_t call_back_id, uint32_t session_id);
		void lock();
		void unlock();
		bool begin(uint32_t cbid_prefix, uint32_t& call_back_id, uint32_t& session_id);
		bool next(uint32_t& call_back_id, uint32_t& session_id);
		void eraseSession(uint32_t session_id);
	    void unregist(uint32_t cbid_prefix);
};

class CallBackContainerScopeLock
{
	private :
		CallBackContainer& mContainer;
	
	public :
		CallBackContainerScopeLock(CallBackContainer& container);
		virtual ~CallBackContainerScopeLock();
	
};

#define	CALLBACKCONTAINER_SCOPE_LOCK(container)		{ CallBackContainerScopeLock lock(container)
#define	CALLBACKCONTAINER_SCOPE_UNLOCK(container)	}

#endif	//#ifndef	_CLASS_CALLBACKCONTAINER_H_

