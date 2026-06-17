#ifndef __CLASS_PROXY_APIC_CALL_H_
#define __CLASS_PROXY_APIC_CALL_H_

#include "BLKC_Common.h"

class Proxy_APIC_CallObserver
{
    public:
        Proxy_APIC_CallObserver();
        ~Proxy_APIC_CallObserver();
        virtual void obs_funcCallObserver( bool b_result );
};

class Proxy_APIC_Call
{
    public:
        uint32_t InstanceID;
    protected: 
        uint32_t SessionID;
    public:
        Proxy_APIC_Call();
        ~Proxy_APIC_Call();
        static Proxy_APIC_Call* newInstance();
        virtual void funcCallNoReturn(bool b_param) = 0;
        virtual bool funcCallReturnBool() = 0;
        virtual void req_funcCallback( const uchar* puc_ParamString, void (*ans_funcCallback)(bool b_result) ) = 0;
        virtual void attachObserver(Proxy_APIC_CallObserver* pc_obs) = 0;
        virtual void detachObserver(Proxy_APIC_CallObserver* pc_obs) = 0;
        virtual void obs_funcCallObserver( bool b_result ) = 0;
};

#endif