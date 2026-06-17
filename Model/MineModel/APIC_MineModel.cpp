#include "MDLC_MineModel.h"
#include "APIC_MineModel.h"

APIC_MineModel::APIC_MineModel()
{

}

APIC_MineModel::~APIC_MineModel()
{

}

APIC_MineModel* APIC_MineModel::newInstance()
{
    return MDLC_MineModel::newInstance();
}

