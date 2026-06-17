#ifndef __BLKC_PROXYCALLBACKTYPEDEF_H_
#define __BLKC_PROXYCALLBACKTYPEDEF_H_

#include <cstdint>

static const uint32_t  BLKD_PROXY_CBID__APIC_Call__req_funcCallback__4                      = 0x00010000;           // APIC_Call::req_funcCallback().
static const uint32_t  BLKD_PROXY_CBID__APIC_MineModel__req_openCell__3                     = 0x00020000;           // APIC_MineModel::req_openCell().
static const uint32_t  BLKD_PROXY_CBID__APIC_MineModel__req_toggleFlag__7                   = 0x00030000;           // APIC_MineModel::req_toggleFlag().

static const uint32_t  BLKD_PROXY_CBID_FRAG                                                 = 0xffff0000;           // For determining the callback function ID

#endif