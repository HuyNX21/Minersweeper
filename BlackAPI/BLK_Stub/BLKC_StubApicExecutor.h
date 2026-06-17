#ifndef	__CLASS_BLKC_STUBAPICEXECUTOR_H_
#define	__CLASS_BLKC_STUBAPICEXECUTOR_H_

#include "BLKC_Common.h"
#include <map>

class BLKC_ReceiveThreadContext;

class BLKC_StubApicExecutor
{
	public :
		BLKC_StubApicExecutor();
		void execApicCall(BLKS_COMMONID* type_id, void *pt, BLKC_ReceiveThreadContext* context );
	
	private :
		~BLKC_StubApicExecutor();
		template<typename STUB_CLASS_T>
		static void dispatchClass( BLKS_COMMONID* type_id , void* instance, void* pt );

		struct DispatchFuncTbl{
			uint32_t mClassMethodID;
			void (*mFunction)( BLKS_COMMONID* , void* , void* );
		};

		static const struct DispatchFuncTbl mDispatchFunctiontbl[];

		typedef std::map< uint32_t, void (*)( BLKS_COMMONID* , void* , void* ) > STUB_FUNC_TBL;
		
		STUB_FUNC_TBL mStubApicFuncTable;

};

template<typename STUB_CLASS_T>
void BLKC_StubApicExecutor::dispatchClass( BLKS_COMMONID* type_id , void* instance, void* pt )
{
	STUB_CLASS_T::newInstance()->dispatch( type_id , instance, pt );
}

#endif	// #ifndef	__CLASS_BLKC_STUBAPICEXECUTOR_H_

