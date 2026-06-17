#if !defined(__MARSAHLINGH_H__)
#define	__MARSAHLINGH_H__

#include <iomanip>
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>

#include "BLKC_Common.h"

typedef char TYPE_Marshal_Setting;				
	#define TYPE_Marshal_Setting_NotSet 	0x00
	#define TYPE_Marshal_Setting_Set 		0x01


#ifdef DEF_PRIVATE
#define	private		public
#define	protected	public
#endif //#ifdef DEF_PRIVATE

// #define BLK_MARSHALING_DEBUG 1
#if defined(BLK_MARSHALING_DEBUG)
#define DEBUG_PRINT std::cout << __FILE__<<":"<<__LINE__<<"    "<<__PRETTY_FUNCTION__ << std::endl;
#else
#define DEBUG_PRINT
#endif

#define CB_FUNCPTR_SIZE				(12)

typedef uint32_t MESSAGE_SIZE_T;

#ifndef uchar
typedef unsigned char	uchar;
#endif
#ifndef UCHAR
typedef unsigned char	UCHAR;
#endif

void* marshal_setCommonID(  uchar* buf, BLKS_COMMONID* type_id, short* ss_datasize );

void* marshal_char( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_signed_char( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_signed_char2( uchar* buf, void* data, int32_t* datasize, int32_t num = 1 );

void* marshal_unsigned_char( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_wchar_t( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_bool( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_int( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_signed_int( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_unsigned_int( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_short( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_signed_short( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_unsigned_short( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_int64_t( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_int32_t( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_signed_int32_t( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_unsigned_int32_t( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_unsigned_long_long( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_float( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_double( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_long_double( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_time_t( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_enum( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_union( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_Bool( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_BOOL( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_TYPE_Marshal_Setting( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_ClassMethodID( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_InstanceID( uchar* buf, void* data, short* datasize, short num = 1 );

void* marshal_SessionID( uchar* buf, void* data, short* datasize, short num = 1 );

#endif