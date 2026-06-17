#include "pch.h"
#include "SYSC_Call.h"
#include <chrono>
#include <thread>

LIBC_List<APIC_CallObserver>  	SYSC_Call::m_pc_CallList;

SYSC_Call::SYSC_Call() {}
SYSC_Call::~SYSC_Call() {}

SYSC_Call* SYSC_Call::newInstance()
{
    static SYSC_Call c_Call;
    return &c_Call;
}

void SYSC_Call::funcCallNoReturn(bool b_param) 
{
    printf("called funcCallNoReturn - param %d !!! \n", b_param);
}
bool SYSC_Call::funcCallReturnBool()
{
    bool b_ret = true;

    printf("called funcCallReturnBool !!! \n");

    return b_ret;
}

void SYSC_Call::req_funcCallback(const uchar* puc_ParamString, void(*ans_funcCallback)(bool b_result))
{
    bool b_result = true;
    printf("called req_funcCallback - param %s !!! \n", puc_ParamString);

    if( ans_funcCallback != NULL ){

        void(*p)(bool) = reinterpret_cast< void(*)( bool ) >(ans_funcCallback);

        std::thread callbackThread([p, b_result]() {

            for (int i = 5; i > 0; --i) {
                printf("Countdown run callback: %d\n", i);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            printf("Countdown finished.\n");

            (*p)(b_result);
        });

        callbackThread.detach();
    }
}

void SYSC_Call::attachObserver(APIC_CallObserver* pc_obs)
{
    if(NULL == pc_obs){
		LOG_ERROR("Assert Failed!");
	}

    m_pc_CallList.Lock();
	m_pc_CallList.add( pc_obs );
	m_pc_CallList.UnLock();
}

void SYSC_Call::detachObserver(APIC_CallObserver* pc_obs)
{
    if(NULL == pc_obs){
		LOG_ERROR("Assert Failed!");
	}

    m_pc_CallList.Lock();
	m_pc_CallList.del( pc_obs );
	m_pc_CallList.UnLock();
}

void SYSC_Call::obs_funcCallObserver( bool b_result )
{
    m_pc_CallList.Lock();
	APIC_CallObserver* pc_CallAnsObserver = m_pc_CallList.findFirst();
	while(NULL != pc_CallAnsObserver){
		pc_CallAnsObserver->obs_funcCallObserver( b_result );
		pc_CallAnsObserver = m_pc_CallList.findNext();
	}
	m_pc_CallList.UnLock();
}