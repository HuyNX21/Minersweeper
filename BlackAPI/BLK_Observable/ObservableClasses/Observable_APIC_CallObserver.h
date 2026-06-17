#ifndef __OBSERVABLE_APIC_CallObserver_H_
#define __OBSERVABLE_APIC_CallObserver_H_

#include "ObservableClassBase.h"
#include "proxy_APIC_Call.h"

using namespace std;

class Observable_APIC_CallObserver : public ObservableClassBase
{
	public :
		typedef ObservableFuncContainer< Observable_APIC_CallObserver, Proxy_APIC_CallObserver > FUNC_CONTAINER;
		Observable_APIC_CallObserver();
	protected :
		void doExec( BLKS_COMMONID* type_id , void* ObjectPt, void* pt );
	private :
		FUNC_CONTAINER mFuncPtContainer;
	private :
		void obs_funcCallObserver( BLKS_COMMONID* type_id, Proxy_APIC_CallObserver* ObjectPt, void* pt );
};
#endif	// #ifndef __OBSERVABLE_APIC_CallObserver_H_