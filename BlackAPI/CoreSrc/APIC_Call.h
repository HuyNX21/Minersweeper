#ifndef __CLASS_APIC_CALL_H_
#define __CLASS_APIC_CALL_H_

#include "BLKC_Common.h"

class APIC_CallObserver
{
public:
	APIC_CallObserver();
	~APIC_CallObserver();

	virtual void obs_funcCallObserver( bool b_result );
};

class APIC_Call
{
    public:
        APIC_Call();
        ~APIC_Call();
        static APIC_Call* newInstance();
        virtual void funcCallNoReturn(bool b_param) = 0;
        virtual bool funcCallReturnBool() = 0;
        virtual void req_funcCallback( const uchar* puc_ParamString, void (*ans_funcCallback)(bool b_result) ) = 0;
        virtual void attachObserver(APIC_CallObserver* pc_obs) = 0;
        virtual void detachObserver(APIC_CallObserver* pc_obs) = 0;
        virtual void obs_funcCallObserver( bool b_result ) = 0;
};

#endif