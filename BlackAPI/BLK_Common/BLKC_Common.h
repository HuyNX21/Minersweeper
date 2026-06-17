#ifndef BLKC_COMMON_H
#define BLKC_COMMON_H

#include <vector>
#include <stdint.h>
#include <sys/types.h>
#include <string>
#include <inttypes.h>

#include "BLKC_Log.h"
#include "ClassIDMethodIDObservable.h"

typedef uint32_t OBSERVER_ID_T;

#define TYPD_MaxParamString 8

typedef unsigned char   uchar;
typedef unsigned short  ushort;

#define BLKD_DEFAULT_INSTANCE_ID	(0)
#define BLKD_FUNCTION_ID			(0)
#define BLKD_STATIC_METHOD_ID		(0)
#define BLKD_CALLBACK_ID			(0)
#define BLKD_OBSERVABLE_ID			(0)
#define BLKD_MAX_RETRY_NUM			(5)

#define _MARKER  (0xFA)
#define TYPD_CORE0      (0x01)
#define TYPD_CORE1      (0x02)
#define TYPD_CORE2      (0x04)
#define TYPD_CORE3      (0x08)
#define TYPD_COREX      (0x00)

#define _PRIONO_USE_OSWRAPPER( cpuno, prio )  (((cpuno) & 0xff) | (((255 - prio + 1) & 0xffff) << 8 ) | (_MARKER << 24))
#define _PRIONO_USE_PTHREAD( cpuno, prio )    (((cpuno) & 0xff) | (((prio) & 0xffff) << 8) | (_MARKER << 24))

#define TYPD_PRIONO_BLKLIB__SrvSessionTh              _PRIONO_USE_OSWRAPPER( TYPD_COREX, 156 )
#define TYPD_PRIONO_BLKLIB__SrvSessionThAs            _PRIONO_USE_OSWRAPPER( TYPD_COREX, 156 )
#define TYPD_PRIONO_BLKLIB__SrvSessionThTmp           _PRIONO_USE_OSWRAPPER( TYPD_COREX, 156 )
#define TYPD_PRIONO_BLKLIB__SrvConnectTh              _PRIONO_USE_OSWRAPPER( TYPD_COREX, 156 )
#define TYPD_PRIONO_BLKLIB__ConKillProTh              _PRIONO_USE_OSWRAPPER( TYPD_COREX, 156 )

#define TYPD_PRIONO_BLKLIB__ConResetProTh             _PRIONO_USE_OSWRAPPER( TYPD_COREX, 181 )

#define DEF_STACK_SIZE_CONRESETPROTH	    (24*1024)
#define DEF_STACK_SIZE_CONKILLPROTH	        (36*1024)
#define DEF_STACK_SIZE_PROXYRCVCTRLTH	    ((16+4+5)*1024)
#define DEF_STACK_SIZE_STUBRCVCTRLTH	    ((16+4+5)*1024)

// #define BLKF_checkConnectManagerInstance(ins, type_id)  if(ins == NULL) { \
// 	printf("[BLKlib][Err] %s , ClassMethodID(%08"PRIx32"), InstanceID(%08"PRIx32"), SessionID(%08"PRIx32") \n" \
// 		, __PRETTY_FUNCTION__ \
// 		, (((BLKS_COMMONID*)type_id)->ClassMethodID) \
// 		, (((BLKS_COMMONID*)type_id)->InstanceID) \
// 		, (((BLKS_COMMONID*)type_id)->SessionID)); \
// 	return; }

#define BLKF_checkConnectManagerInstance(ins, type_id)  if(ins == NULL) { \
	LOG_ERROR("instance is null ~ ClassMethodID: %d - InstanceID: %d - SessionID: %d" \
		, (((BLKS_COMMONID*)type_id)->ClassMethodID) \
		, (((BLKS_COMMONID*)type_id)->InstanceID) \
		, (((BLKS_COMMONID*)type_id)->SessionID)); \
	return; }

typedef char TYPE_JOBSPEC_CLASS_KIND;
	#define TYPE_JOBSPEC_CLASS_TYPC_JobSpec			0
	#define TYPE_JOBSPEC_CLASS_TYPC_Common			1
	#define TYPE_JOBSPEC_CLASS_TYPC_Scan			2
	#define TYPE_JOBSPEC_CLASS_TYPC_Print			3
	#define TYPE_JOBSPEC_CLASS_TYPC_Send			4
	#define TYPE_JOBSPEC_CLASS_TYPC_Fax				5
	#define TYPE_JOBSPEC_CLASS_TYPC_Interpreter		6
	#define TYPE_JOBSPEC_CLASS_TYPC_IPP				7
	#define TYPE_JOBSPEC_CLASS_TYPC_ImageConvert	8
	#define TYPE_JOBSPEC_CLASS_TYPC_Plugin			9
	#define TYPE_JOBSPEC_CLASS_TYPC_JobHistory		10
	#define TYPE_JOBSPEC_CLASS_TYPC_JobStatus		11


static const uint32_t  BLKD_MSG_PAYLOAD_SIZE = 32 * 1024;
static const uint32_t  BLKD_MSG_PAYLOAD_EXT_SIZE = 512 * 1024;

static const int32_t BLKD_MQFILE_MAX_PATH = (255+12+1);
static const int32_t BLKD_SEMFILE_MAX_PATH = (255+9+1);

typedef uint32_t SEQUENS_ID_T;
typedef uint32_t MESSAGE_SIZE_T;

typedef struct BLKS_MsgHead
{
	uint32_t  msgSize;
	SEQUENS_ID_T  sequenceId;
} BLKS_MSGHEAD;

typedef struct BLKS_MsgFormat{
	BLKS_MSGHEAD  header;
	unsigned char payload[ BLKD_MSG_PAYLOAD_SIZE ];
}BLKS_MSG_FORMAT;

static const unsigned int BLKD_MSGHEAD_SIZE = sizeof(BLKS_MSGHEAD);

typedef struct BLKS_CommonId
{
	uint32_t ClassMethodID;	
	uint32_t InstanceID;	
	uint32_t SessionID;		
} BLKS_COMMONID;

struct LARGE_RET_VAL_DESTINATION_T
{
	void* destination;
	MESSAGE_SIZE_T size;
};

typedef std::vector<struct LARGE_RET_VAL_DESTINATION_T*> LARGE_RET_VAL_ARRY;

struct LARGE_PARAM_DESTINATION_T
{
	void* destination;
	MESSAGE_SIZE_T size;
};

typedef std::vector<struct LARGE_PARAM_DESTINATION_T*> LARGE_PARAM_ARRY;

typedef uint32_t BLKD_SOCKID;
#define BLKD_SOCKID_SYNC	(0)				
#define BLKD_SOCKID_ASYNC	(1)				
#define BLKD_SOCKID_MAX		(2)				
#define BLKD_SOCKID_INVALID	(0xFFFFFFFF)	

typedef struct {
	pid_t sys_pid;		
	pid_t sys_tid;		
	int priority;		
	BLKD_SOCKID sockid;	
} BLKS_SOCKET_CONTROLDATA;

typedef struct 
{
    int x;
    int y;
	int adjacentValue;
}PointCellOpened;

static const SEQUENS_ID_T SEQUENSE_ID_KIND_MASK						= 0xff << 24;
static const SEQUENS_ID_T SEQUENSE_ID_HELTH_CHECK					= 0x00 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_SYNC_REQUEST					= 0x01 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_CALL_BACK						= 0x02 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_OBSERVER_NOTIFY				= 0x03 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_SYNC_REQ_WITH_LARGE_RETVAL	= 0x04 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_SYNC_REQ_LARGE_RETVAL			= 0x05 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_CALL_BACK_LARGE_PARAM			= 0x06 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_OBSERVER_NOTIFY_LARGE_PARAM	= 0x07 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_REQUEST_LARGE_PARAM			= 0x08 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_SYNC_REQ_LARGE_PARAM			= 0x09 << 24;
static const SEQUENS_ID_T SEQUENSE_ID_SYNC_REQ_LARGE_PARAM_RETVAL	= 0x0a << 24;
static const SEQUENS_ID_T SEQUENSE_ID_CALL_BACK_NOWAIT				= 0x0b << 24;
static const SEQUENS_ID_T SEQUENSE_ID_OBSERVER_NOWAIT				= 0x0c << 24;
static const SEQUENS_ID_T SEQUENSE_ID_CALL_BACK_LARGEPRM_NOWAIT		= 0x0d << 24;
static const SEQUENS_ID_T SEQUENSE_ID_OBSERVER_LARGEPRM_NOAWIT		= 0x0e << 24;
static const SEQUENS_ID_T SEQUENSE_ID_SYNC_REQ_JOBSPEC_DEL			= 0x0f << 24;
static const SEQUENS_ID_T SEQUENSE_ID_SYNC_REQ_JOBSPEC_DEL_SRV		= 0x10 << 24;

typedef uint32_t OBSERVER_ID_T;

#define BLKD_EINTR_RETRY_CALL(exp, errexp)				\
do {													\
	exp;												\
} while ((errexp) && (errno == EINTR));

#define BLKD_EINTR_RETRY_CALL3(exp, errexp, errstate)	\
do {													\
	exp;												\
} while ((errexp) && (errno == EINTR));					\
														\
if (errexp) {											\
	errstate;											\
}

inline uint32_t UISEP_OBSERVABLE::getClassID(uint32_t class_method_id)
{
	return class_method_id & CLASS_MASK;
}

inline uint32_t UISEP_OBSERVABLE::getMethodID(uint32_t class_method_id)
{
	return class_method_id & ~CLASS_MASK;
}

inline void toCommonIDStruct(BLKS_COMMONID& str, uint32_t class_method_id, uint32_t instance_id, uint32_t session_id)
{
	str.ClassMethodID = class_method_id;
	str.InstanceID = instance_id;
	str.SessionID = session_id;
	
}

inline void fromCommonIDStruct(BLKS_COMMONID& str, uint32_t& class_method_id, uint32_t& instance_id, uint32_t& session_id)
{
	class_method_id = str.ClassMethodID;
	instance_id = str.InstanceID;
	session_id = str.SessionID;
	
}

#endif // BLKC_COMMON_H