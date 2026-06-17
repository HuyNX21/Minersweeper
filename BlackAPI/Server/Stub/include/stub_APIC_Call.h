#include "BLKC_Common.h"

class APIC_Call;

class Stub_APIC_Call
{
public:
	Stub_APIC_Call(){}
	~Stub_APIC_Call(){}
	static Stub_APIC_Call* newInstance();
	void dispatch( BLKS_COMMONID* type_id , void* ObjectPt, void* pt );

	void Stub_APIC_Call_newInstance_01( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt );
	void Stub_APIC_Call_funcCallNoReturn_02( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt );
	bool Stub_APIC_Call_funcCallReturnBool_03( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt );
	void Stub_req_funcCallback_04( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt );
	void Stub_attachObserver_05( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_HddInfo, void* pt );
	void Stub_detachObserver_06( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_HddInfo, void* pt );
	void Stub_obs_funcCallObserver_07( BLKS_COMMONID* type_id , APIC_Call* pc_APIC_Call, void* pt );

	static void Stub_ans_funcCallback__99(bool b_result);
};