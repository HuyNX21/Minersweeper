
#include "SYSC_Call.h" // phải đặt trước #include "APIC_Call.h"
#include "APIC_Call.h"

APIC_Call::APIC_Call(){}
APIC_Call::~APIC_Call(){}

APIC_Call* APIC_Call::newInstance()
{
	return	SYSC_Call::newInstance();
}

void APIC_Call::funcCallNoReturn(bool b_param) { }
bool APIC_Call::funcCallReturnBool() { }
void APIC_Call::req_funcCallback(const uchar* puc_ParamString, void(*ans_funcCallback)(bool b_result)) { }
void APIC_Call::attachObserver(APIC_CallObserver* pc_obs) {}
void APIC_Call::detachObserver(APIC_CallObserver* pc_obs) {}

APIC_CallObserver::APIC_CallObserver() {}
APIC_CallObserver::~APIC_CallObserver() {}
void APIC_CallObserver::obs_funcCallObserver( bool b_result ) { }