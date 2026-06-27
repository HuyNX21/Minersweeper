#include "pch.h"
#include "APIC_MineModel.h"
#include "BLKC_StubManager.h"
#include "SignalHandle.h"

int main()
{
    char cmd[64];
	struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = seg_handler;
    sigaction(SIGSEGV, &sa, NULL);
    
    APIC_MineModel::newInstance();
    BLKC_StubManager::getInstance();
    sleep(10000);

    return 0;
}
