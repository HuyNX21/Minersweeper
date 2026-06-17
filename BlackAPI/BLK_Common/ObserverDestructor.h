#ifndef __OBSERVERDESTRUCTOR_H__
#define __OBSERVERDESTRUCTOR_H__
#include <set>
#include <stdio.h>
#include <stdint.h>
#include "MutexLock.h"

// 機種マージ後不具合No.141 2011.12.8 start.
// オブザーバ用仮登録ID.
// Stub側で正式IDが発行される前のProxy側での事前登録用ID(登録完了前に通知が来てもよいようにする為).
static const uint32_t BLKD_PRE_OBSERVER_ID = -1;			// 仮登録ID.
static const uint32_t BLKD_NOTPRE_OBSERVER_ID = -2;		// 再送信要求用ID.
static const uint32_t BLKD_PRE_OBSERVER_ID_NOWAIT = -3;	// Stub側応答待ちなし時の仮登録ID.
// 機種マージ後不具合No.141 2011.12.8 end.

// attach, detachメソッドがstaticではないクラス用.
template<typename OBSERVER_T, typename DETACH_FUNC_T, typename OBSERVABLE_T >
class AttachedObserverList
{

	typedef std::set<OBSERVER_T*> LIST_T;
	typedef typename LIST_T::iterator LIST_IT_T;

	DETACH_FUNC_T m_funcPt;
	LIST_T m_subjects;
	OBSERVABLE_T* m_observable;

	void detachAll()
	{
		//printf("[DBG] %s called, this = %lx\n", __PRETTY_FUNCTION__, this);
		// subjectがある間繰り返し start
		LIST_IT_T it = m_subjects.begin();
		LIST_IT_T it_end = m_subjects.end();
// 2019/06/19 APF OP_BTS-7841対応 Start.
//		for( ;it != it_end;it++ )
		while(it != it_end)
// 2019/06/19 APF OP_BTS-7841対応 End.
		{
			// 取得したsubjectから自分をdetach
// 2019/06/19 APF OP_BTS-7841対応 Start.
//			detachOwn(it);
			detachOwn(it++);
// 2019/06/19 APF OP_BTS-7841対応 End.
		}
		// subjectがある間繰り返し end
	}

	void detachOwn(LIST_IT_T it)
	{
		//printf("[DBG] %s called, this = %lx\n", __PRETTY_FUNCTION__, this);
		OBSERVER_T* pc_subject = (OBSERVER_T*)(*it);
		if( pc_subject == NULL )
		{
#ifdef DEF_BLACKAPI_DEBUGLOG
			printf("          pc_subject is NULL !!!\n");
#endif // DEF_BLACKAPI_DEBUGLOG.
			m_subjects.erase(it);
			return;
		}
		// pc_subjectから自分をdetach
		// detachメソッドが存在しない場合 m_funcPt はNULLが代入される
		if( m_funcPt != NULL )
		{
#ifdef DEF_BLACKAPI_DEBUGLOG
			printf("         m_funcPt = %x\n", m_funcPt);
			printf("         (pc_subject->*m_funcPt)(m_observable) --- pc_subject = %x, m_observable = %x\n", pc_subject, m_observable);
#endif // DEF_BLACKAPI_DEBUGLOG.
			(pc_subject->*m_funcPt)(m_observable);
		}
		m_subjects.erase(it);
	}

public:

	AttachedObserverList(DETACH_FUNC_T func_pt, OBSERVABLE_T*pc_observable)
	:m_funcPt( func_pt ),m_observable( pc_observable )
	{
	}

	~AttachedObserverList()
	{
		//printf("[DBG] %s called, this = %lx\n", __PRETTY_FUNCTION__, this);
		detachAll();
	}

	void setSubject(OBSERVER_T* pc_subject)
	{
		//printf("[DBG] %s called, pc_subject = %lx, this = %lx\n", __PRETTY_FUNCTION__, pc_subject, this );
		// std::set に要素登録
		m_subjects.insert(pc_subject);
	}
	
	void deleteSubject(OBSERVER_T* pc_subject)
	{
		// subjectがある間繰り返し start
		LIST_IT_T it = m_subjects.begin();
		LIST_IT_T it_end = m_subjects.end();
// 2012/04/17 平岩 MinervaZeus静的解析警告対応 CID:271471 [START].
		while(it != it_end)
		{
			// 取得したsubjectから自分をdetach
			if( *it == pc_subject )
			{
				m_subjects.erase(it++);
			}else{
				++it;
			}
		}
		// subjectがある間繰り返し end
// 2012/04/17 平岩 MinervaZeus静的解析警告対応 CID:271471 [END].
	}
};

// attach, detachメソッドがstaticとなっているクラス用.
template<typename OBSERVER_T, typename DETACH_FUNC_T, typename OBSERVABLE_T >
class AttachedObserverList_static
{

	typedef std::set<OBSERVER_T*> LIST_T;
	typedef typename LIST_T::iterator LIST_IT_T;

	DETACH_FUNC_T m_funcPt;
	LIST_T m_subjects;
	OBSERVABLE_T* m_observable;
	bool isAttached;

	void detachAll()
	{
		if( isAttached )
		{
			isAttached = false;
			detachOwn(m_subjects.begin());
		}
	}

	void detachOwn(LIST_IT_T it)
	{
		// pc_subjectから自分をdetach
		// detachメソッドが存在しない場合 m_funcPt はNULLが代入される
		if( m_funcPt != NULL )
		{
#ifdef DEF_BLACKAPI_DEBUGLOG
			printf("         m_funcPt = %x\n", m_funcPt);
			printf("         m_funcPt(m_observable) --- , m_observable = %x\n", m_observable);
#endif // DEF_BLACKAPI_DEBUGLOG.
			m_funcPt(m_observable);
		}
	}

public:

	AttachedObserverList_static(DETACH_FUNC_T func_pt, OBSERVABLE_T*pc_observable)
	:m_funcPt( func_pt ),m_observable( pc_observable ), isAttached(false)
	{
	}

	~AttachedObserverList_static()
	{
		//printf("[DBG] %s called, this = %lx\n", __PRETTY_FUNCTION__, this);
		detachAll();
	}

	void setSubject(OBSERVER_T* pc_subject)
	{
		// attachされたことを記憶.
		isAttached = true;
	}
	
	void deleteSubject(OBSERVER_T* pc_subject)
	{
		isAttached = false;
	}
};

class ObserverDestructor
{
private:
	uint32_t m_connectId;
public:
	// 機種マージ後不具合No.141 2011.12.8 start.
//	ObserverDestructor() : mRegistFlg( false ), m_connectId(0) {};		// warning除去対応.
//	ObserverDestructor( uint32_t connectId ) : mRegistFlg( false ), m_connectId(connectId) {};		// warning除去対応.
	ObserverDestructor() : m_connectId(0), mRegistFlg( false ) {};		// warning除去対応.
	ObserverDestructor( uint32_t connectId ) : m_connectId(connectId), mRegistFlg( false ) {};		// warning除去対応.

	virtual ~ObserverDestructor(){};
	bool getRegistFlg()
	{
		return mRegistFlg;
	};
	void setRegistFlg( bool b_Regist )
	{
		mRegistFlg = b_Regist;
	};
	uint32_t getConnectId()
	{
		return m_connectId;
	};
	void setConnectId( uint32_t connectId )
	{
		m_connectId = connectId;
	};
protected:
	bool mRegistFlg;
	// 機種マージ後不具合No.141 2011.12.8 end.
};

#endif // __OBSERVERDESTRUCTOR_H__
