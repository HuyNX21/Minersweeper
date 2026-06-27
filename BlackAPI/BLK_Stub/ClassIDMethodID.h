#ifndef _ClASSIDMETHODID_h_
#define _ClASSIDMETHODID_h_

#include<stdint.h>

static const uint32_t UISEP_METHOD_ID_newInstance = 0x0000ffff;

static const uint32_t UISEP_CLASS_MASK = 0xffff << 16;
static const uint32_t UISEP_METHOD_MASK = 0x0000ffff;

#define ClassMethodID_toClassID( arg )			( (uint32_t)( arg & UISEP_CLASS_MASK ) )
#define ClassMethodID_toMethodID( arg )			( (uint32_t)( arg & UISEP_METHOD_MASK ) )
#define ClassMethodID_toNewInstanceID( arg )	( (uint32_t)( arg | UISEP_METHOD_ID_newInstance ) )
#define ClassMethodID_isNewInstanceID( arg )	( (bool)(ClassMethodID_to_MethodID( arg ) == UISEP_METHOD_ID_newInstance ) )
#define UISEP_CALLBACK_METHOD 0

static const uint32_t UISEP__APIC_Call__BASE__                                  = 0x0000 << 16;
static const uint32_t UISEP__APIC_Call__newInstance__1                          = ( UISEP__APIC_Call__BASE__ | UISEP_METHOD_ID_newInstance );       // APIC_Call::newInstance.
static const uint32_t UISEP__APIC_Call__funcCallNoReturn__2                     = ( UISEP__APIC_Call__BASE__ | 0x0002 );                            // APIC_Call::funcCallNoReturn.
static const uint32_t UISEP__APIC_Call__funcCallReturnBool__3                   = ( UISEP__APIC_Call__BASE__ | 0x0003 );                            // APIC_Call::funcCallReturnBool.
static const uint32_t UISEP__APIC_Call__req_funcCallback__4                     = ( UISEP__APIC_Call__BASE__ | 0x0004 );                            // APIC_Call::req_funcCallback.
static const uint32_t UISEP__APIC_Call__attachObserver__5                       = ( UISEP__APIC_Call__BASE__ | 0x0005 );                            // APIC_Call::attachObserver.
static const uint32_t UISEP__APIC_Call__detachObserver__6                       = ( UISEP__APIC_Call__BASE__ | 0x0006 );                            // APIC_Call::detachObserver.
static const uint32_t UISEP__APIC_Call__obs_funcCallObserver__7                 = ( UISEP__APIC_Call__BASE__ | 0x0007 );                            // APIC_Call::obs_funcCallObserver.

static const uint32_t UISEP__APIC_CallObserver__BASE__                          = 0x0001 << 16;
static const uint32_t UISEP__APIC_CallObserver__obs_funcCallObserver__1         = ( UISEP__APIC_CallObserver__BASE__ | 0x0001 );                    // APIC_CallObserver::obs_funcCallObserver.

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

static const uint32_t UISEP__APIC_MineModel__BASE__                             = 0x0002 << 16;
static const uint32_t UISEP__APIC_MineModel__newInstance__1                     = ( UISEP__APIC_MineModel__BASE__ | UISEP_METHOD_ID_newInstance );  // APIC_MineModel::newInstance.
static const uint32_t UISEP__APIC_MineModel__setup__2                           = ( UISEP__APIC_MineModel__BASE__ | 0x0002 );                       // APIC_MineModel::setup.
static const uint32_t UISEP__APIC_MineModel__req_openCell__3                    = ( UISEP__APIC_MineModel__BASE__ | 0x0003 );                       // APIC_MineModel::req_openCell.
static const uint32_t UISEP__APIC_MineModel__attachObserver__4                  = ( UISEP__APIC_MineModel__BASE__ | 0x0004 );                       // APIC_MineModel::attachObserver.
static const uint32_t UISEP__APIC_MineModel__detachObserver__5                  = ( UISEP__APIC_MineModel__BASE__ | 0x0005 );                       // APIC_MineModel::detachObserver.
static const uint32_t UISEP__APIC_MineModel__obs_gameStateChanged__6            = ( UISEP__APIC_MineModel__BASE__ | 0x0006 );                       // APIC_MineModel::obs_gameStateChanged.
static const uint32_t UISEP__APIC_MineModel__req_toggleFlag__7                  = ( UISEP__APIC_MineModel__BASE__ | 0x0007 );                       // APIC_MineModel::req_toggleFlag.
static const uint32_t UISEP__APIC_MineModel__getState__8                        = ( UISEP__APIC_MineModel__BASE__ | 0x0008 );                       // APIC_MineModel::getState.
static const uint32_t UISEP__APIC_MineModel__setState__9                        = ( UISEP__APIC_MineModel__BASE__ | 0x0009 );                       // APIC_MineModel::setState.
static const uint32_t UISEP__APIC_MineModel__obs_minesRevealed__10              = ( UISEP__APIC_MineModel__BASE__ | 0x000A );                       // APIC_MineModel::obs_minesRevealed.
static const uint32_t UISEP__APIC_MineModel__obs_gameOver__11                   = ( UISEP__APIC_MineModel__BASE__ | 0x000B );                       // APIC_MineModel::obs_gameOver.
static const uint32_t UISEP__APIC_MineModel__getEntries__12                     = ( UISEP__APIC_MineModel__BASE__ | 0x000C );                       // APIC_MineModel::getEntries.
static const uint32_t UISEP__APIC_MineModel__getCurrentSizeField__13            = ( UISEP__APIC_MineModel__BASE__ | 0x000D );                       // APIC_MineModel::getCurrentSizeField.
static const uint32_t UISEP__APIC_MineModel__getCurrentMinesField__14           = ( UISEP__APIC_MineModel__BASE__ | 0x000E );                       // APIC_MineModel::getCurrentMinesField.
static const uint32_t UISEP__APIC_MineModel__setBestTime__15                    = ( UISEP__APIC_MineModel__BASE__ | 0x000F );                       // APIC_MineModel::setBestTime.

static const uint32_t UISEP__APIC_MineModelObserver__BASE__                     = 0x0003 << 16;
static const uint32_t UISEP__APIC_MineModelObserver__obs_gameStateChanged__1    = ( UISEP__APIC_MineModelObserver__BASE__ | 0x0001 );               // APIC_MineModelObserver::obs_gameStateChanged.
static const uint32_t UISEP__APIC_MineModelObserver__obs_minesRevealed__2       = ( UISEP__APIC_MineModelObserver__BASE__ | 0x0002 );               // APIC_MineModelObserver::obs_minesRevealed.
static const uint32_t UISEP__APIC_MineModelObserver__obs_gameOver__3            = ( UISEP__APIC_MineModelObserver__BASE__ | 0x0003 );               // APIC_MineModelObserver::obs_gameOver.

#endif  