#include "pch.h"

#include "ObservableExecutor.h"
#include "ClassIDMethodIDObservable.h"
#include "BLKC_ProxyManager.h"

#include "Observable_APIC_CallObserver.h"
#include "Observable_APIC_MineModelObserver.h"

using namespace std;
using namespace UISEP_OBSERVABLE;

ObservableExecutor::ObservableExecutor()
{
	buildObservableClassTbl();
}

ObservableExecutor::~ObservableExecutor()
{
	EXECUTOR_TBL::iterator it = mObservableClassTbl.begin();
	EXECUTOR_TBL::iterator it_end = mObservableClassTbl.end();

	for(;it != it_end;it++){
		delete (*it).second;
	}
}

void ObservableExecutor::buildObservableClassTbl()
{
    try{
        mObservableClassTbl[ CLASS_APIC_CallObserver ] 				= new Observable_APIC_CallObserver;
		mObservableClassTbl[ CLASS_APIC_MineModelObserver ] 		= new Observable_APIC_MineModelObserver;
    }catch(exception& ex){
		LOG_ERROR("thrown exception., ex = %s", ex.what());
	}
}

void ObservableExecutor::exec( BLKC_ProxyManager& proxy_manager, BLKS_COMMONID* type_id, void *pt, void *object_pt, BLKC_ReceiveThreadContext* context )
{
	uint32_t class_id = getClassID( type_id->ClassMethodID );

	
	EXECUTOR_TBL::iterator it = mObservableClassTbl.find( class_id );
	EXECUTOR_TBL::iterator it_end = mObservableClassTbl.end();

    if((it == it_end)) LOG_ERROR("Proxy received invalid observable-id., ClassMethodID = %#x", type_id->ClassMethodID);

	if ( object_pt == NULL ) {
		const std::type_info* pObserverType = ((*it).second)->getObserverType();
		while ( proxy_manager.waitSyncObject( pObserverType ) ) {
			object_pt = proxy_manager.getObject( type_id->InstanceID );
			if ( object_pt != NULL ) {
				break;
			}
		}

		if ( object_pt == NULL ) {
			object_pt = proxy_manager.getObject( type_id->InstanceID );
		}
	}

    if(object_pt == NULL) LOG_ERROR("object_pt is NULL. ClassMethodID = %#x, InstanceID = %#d", type_id->ClassMethodID, type_id->InstanceID);

	((*it).second)->exec(type_id, object_pt, pt);


}

void ObservableExecutor::notifyProxyRcvThFatalCallBack( ushort us_TaskDetailCode, uint64_t ull_NewDetailCode )
{
	// LAPC_BFW_System::newInstance()->registDetailCode( us_TaskDetailCode, ull_NewDetailCode );
}