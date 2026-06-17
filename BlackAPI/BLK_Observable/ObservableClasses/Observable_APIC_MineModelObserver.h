#ifndef _OBSERVABLE_APIC_MINEMODELOBSERVER_H_
#define _OBSERVABLE_APIC_MINEMODELOBSERVER_H_

#include "ObservableClassBase.h"
#include "proxy_APIC_MineModel.h"

class Observable_APIC_MineModelObserver : public ObservableClassBase
{
    public :
		typedef ObservableFuncContainer< Observable_APIC_MineModelObserver, Proxy_APIC_MineModelObserver > FUNC_CONTAINER;
		Observable_APIC_MineModelObserver();
	protected :
		void doExec( BLKS_COMMONID* type_id , void* ObjectPt, void* pt );
	private :
		FUNC_CONTAINER mFuncPtContainer;
	private :
		void obs_gameStateChanged( BLKS_COMMONID* type_id, Proxy_APIC_MineModelObserver* ObjectPt, void* pt );
		void obs_minesRevealed( BLKS_COMMONID* type_id, Proxy_APIC_MineModelObserver* ObjectPt, void* pt );
		void obs_gameOver( BLKS_COMMONID* type_id, Proxy_APIC_MineModelObserver* ObjectPt, void* pt );
};

#endif // _OBSERVABLE_APIC_MINEMODELOBSERVER_H_