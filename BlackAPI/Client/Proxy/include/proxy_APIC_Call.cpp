
#include "proxy_APIC_Call.h"
#include "proxy_SYSC_Call.h"

Proxy_APIC_Call::Proxy_APIC_Call(){}
Proxy_APIC_Call::~Proxy_APIC_Call(){}

Proxy_APIC_Call* Proxy_APIC_Call::newInstance()
{
	return	Proxy_SYSC_Call::newInstance();
}

void Proxy_APIC_Call::funcCallNoReturn(bool b_param) { }
bool Proxy_APIC_Call::funcCallReturnBool() { }
void Proxy_APIC_Call::req_funcCallback(const uchar* puc_ParamString, void(*ans_funcCallback)(bool b_result)) { }
void Proxy_APIC_Call::attachObserver(Proxy_APIC_CallObserver* pc_obs) {}
void Proxy_APIC_Call::detachObserver(Proxy_APIC_CallObserver* pc_obs) {}

Proxy_APIC_CallObserver::Proxy_APIC_CallObserver() {}
Proxy_APIC_CallObserver::~Proxy_APIC_CallObserver() {}
void Proxy_APIC_CallObserver::obs_funcCallObserver( bool b_result ) { }