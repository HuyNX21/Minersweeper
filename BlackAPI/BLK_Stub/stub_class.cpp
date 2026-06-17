
#include "stub_method.h"
#include "BLKC_ConnectManager.h"
#include "ThreadSafeSingleton.h"
#include "BLKC_StubApicExecutor.h"

using namespace std;


void BLKC_ConnectManager::Stub_APIC_Call( BLKS_COMMONID* type_id, void *pt, BLKC_ReceiveThreadContext* context )
{
	
	static BLKC_StubApicExecutor* executor = NULL;
	
	if(executor == NULL){
		executor = ThreadSafeSingleton<BLKC_StubApicExecutor>::getInstance();
	}
	
	executor->execApicCall(type_id, pt, context);
}