#include "pch.h"
#include "APIC_MineModel.h"
#include "BLKC_StubManager.h"

int main()
{
    APIC_MineModel::newInstance();
    BLKC_StubManager::getInstance();
    sleep(10000);

    return 0;
}
