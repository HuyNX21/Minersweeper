
#ifndef __CLASS_PROXY_SYSC_CALL_H_
#define __CLASS_PROXY_SYSC_CALL_H_

#include "proxy_APIC_Call.h"
#include "BLKC_Common.h"

class Proxy_SYSC_Call : public Proxy_APIC_Call
{
    public:
        Proxy_SYSC_Call();
        ~Proxy_SYSC_Call();
        static Proxy_SYSC_Call* newInstance();
        virtual void funcCallNoReturn(bool b_param);
        virtual bool funcCallReturnBool();
        virtual void req_funcCallback(const uchar* puc_ParamString, void(*ans_funcCallback)(bool b_result));
        virtual void attachObserver(Proxy_APIC_CallObserver* pc_obs);
        virtual void detachObserver(Proxy_APIC_CallObserver* pc_obs);
        virtual void obs_funcCallObserver( bool b_result );
};

#endif