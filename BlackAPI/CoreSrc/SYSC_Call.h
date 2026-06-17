#ifndef __CLASS_SYSC_CALL_H_
#define __CLASS_SYSC_CALL_H_

#include "APIC_Call.h"
#include "BLKC_Common.h"
#include "LIBC_List.h"

class SYSC_Call : public APIC_Call
{
    public:
        SYSC_Call();
        ~SYSC_Call();
        static SYSC_Call* newInstance();
        virtual void funcCallNoReturn(bool b_param);
        virtual bool funcCallReturnBool();
        virtual void req_funcCallback(const uchar* puc_ParamString, void(*ans_funcCallback)(bool b_result));
        virtual void attachObserver(APIC_CallObserver* pc_obs);
        virtual void detachObserver(APIC_CallObserver* pc_obs);
        virtual void obs_funcCallObserver( bool b_result );
    
    private:
        static LIBC_List<APIC_CallObserver>  	m_pc_CallList;
};

#endif