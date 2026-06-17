#ifndef	__CLASS_APIC_STUB_CallObserver_H_
#define	__CLASS_APIC_STUB_CallObserver_H_

#include "BLKC_Common.h"
#include "APIC_Call.h"
#include "ObserverDestructor.h"

class Stub_APIC_CallObserver :  public APIC_CallObserver, public ObserverDestructor
{
	public:
		Stub_APIC_CallObserver( uint32_t session_id );
		~Stub_APIC_CallObserver();
		void setSubject( APIC_Call* );
		void deleteSubject( APIC_Call* );
		void dataChanged();
		void obs_funcCallObserver( bool b_result );

		uint32_t SessionID;

	private:
		Stub_APIC_CallObserver();

		AttachedObserverList<APIC_Call,void (APIC_Call::*)(APIC_CallObserver*),APIC_CallObserver> *m_AttachedObserverList;
};

#endif	// #ifndef __CLASS_APIC_STUB_CallObserver_H_