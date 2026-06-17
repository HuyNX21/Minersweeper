#ifndef	__CLASSID_METHODID_OBSERVABLE_H_
#define	__CLASSID_METHODID_OBSERVABLE_H_

#include "ClassIDMethodID.h"

namespace UISEP_OBSERVABLE{

static const uint32_t CLASS_MASK                              = 0xffff << 16;
static const uint32_t CLASS_APIC_CallObserver                 = UISEP__APIC_CallObserver__BASE__;
static const uint32_t CLASS_APIC_MineModelObserver            = UISEP__APIC_MineModelObserver__BASE__;

}

namespace UISEP_OBSERVABLE{
uint32_t getClassID(uint32_t class_method_id);
uint32_t getMethodID(uint32_t class_method_id);
}

#endif