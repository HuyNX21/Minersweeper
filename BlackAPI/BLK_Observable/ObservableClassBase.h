#ifndef	__CLASS_OBSERVABLECLASSBASE_H_
#define	__CLASS_OBSERVABLECLASSBASE_H_

#include <exception>
#include <stdint.h>
#include <typeinfo>

#include "BLKC_Common.h"

class ObservableClassBase
{
	public :
		ObservableClassBase()
		{
			mObserverType = NULL;
		}
	
		virtual ~ObservableClassBase(){}
	
		void exec( BLKS_COMMONID* type_id , void* ObjectPt, void* pt )
		{
			doExec(type_id, ObjectPt, pt);
		}
	
		void setObserverType( const std::type_info* pObserverType )
		{
			mObserverType = pObserverType;
		}
	
		const std::type_info* getObserverType()
		{
			return mObserverType;
		}

	protected :
		virtual void doExec( BLKS_COMMONID* type_id , void* ObjectPt, void* pt ) = 0;

	protected :
		const std::type_info*	mObserverType;
	
	
};

template <typename OBSERVABLE_T, typename APIC_T>
class ObservableFuncContainer 
{

	public :

		typedef void (OBSERVABLE_T::*FUNC_TYPE)( BLKS_COMMONID*, APIC_T*, void* );
		typedef struct{
			uint32_t	class_method_id;
			FUNC_TYPE		func_pt;
		}FUNC_TBL_T;
		typedef APIC_T OBSERVER_T;

	private :
	
		const FUNC_TBL_T* mFunctionTbl;
		uint32_t mFunctionCnt;

	public :

		ObservableFuncContainer()
			: mFunctionTbl( NULL )
			, mFunctionCnt( 0 )
		{
		}

		void exec( OBSERVABLE_T* observable, BLKS_COMMONID* type_id , void* ObjectPt, void* pt )
		{

			FUNC_TYPE func = NULL;

			for(uint32_t i = 0;i < mFunctionCnt;i++){
				if(mFunctionTbl[i].class_method_id == type_id->ClassMethodID){
					func = mFunctionTbl[i].func_pt;
					break;
				}
			}

			if(func == NULL) LOG_ERROR("mFunctionTbl.find() is failed. ClassMethod_id = %#x", type_id->ClassMethodID);

			(observable->*func)(type_id, (APIC_T*)ObjectPt, pt);
		}
		
		void registFunction(const FUNC_TBL_T* tbl, uint32_t tbl_cnt)
		{
			mFunctionTbl = tbl;
			mFunctionCnt = tbl_cnt;
		}
		
	private :
		ObservableFuncContainer( ObservableFuncContainer& arg){}

};

#define FUNC_TBL_LENGTH(tbl) (sizeof(tbl)/sizeof(tbl[0]))

#endif	//#ifndef	__CLASS_OBSERVABLECLASSBASE_H_


