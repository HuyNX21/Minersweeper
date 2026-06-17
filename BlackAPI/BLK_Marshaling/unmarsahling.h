#if !defined(__UNMARSAHLINGH_H__)
#define	__UNMARSAHLINGH_H__

#include <iomanip>
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>

#include "BLKC_Common.h"

// #define BLK_UNMARSHALING_DEBUG 1
#if defined(BLK_UNMARSHALING_DEBUG)
#define DEBUG_PRINT std::cout << __FILE__<<":"<<__LINE__<<"    "<<__PRETTY_FUNCTION__ << std::endl;
#define DEBUG_PRINT1 std::cout << __FILE__<<":"<<__LINE__<<"    "<<"TYPE_UnMarshal_Setting_NotSet"<< std::endl;
#define DEBUG_PRINT2 std::cout << __FILE__<<":"<<__LINE__<<"    "<<"malloc Failed."<< std::endl;
#else
#define DEBUG_PRINT
#define DEBUG_PRINT1
#define DEBUG_PRINT2
#endif

#define CB_FUNCPTR_SIZE				(12)
typedef uint32_t MESSAGE_SIZE_T;

typedef char TYPE_UnMarshal_Setting;			
	#define TYPE_UnMarshal_Setting_NotSet 	0x00
	#define TYPE_UnMarshal_Setting_Set 		0x01

#ifndef uchar
typedef unsigned char	uchar;
#endif
#ifndef UCHAR
typedef unsigned char	UCHAR;
#endif


void* unmarshal_getCommonID(  uchar* buf, BLKS_COMMONID* type_id, short* ss_datasize );

void* unmarshal_char( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_signed_char( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_signed_char2( uchar* buf, void* data, int32_t* datasize = 0, int32_t num = 1 );

void* unmarshal_unsigned_char( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_unsigned_int32_t( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_wchar_t( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_bool( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_int( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_signed_int( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_unsigned_int( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_short( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_signed_short( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_unsigned_short( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_int64_t( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_int32_t( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_signed_int32_t( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_unsigned_long_long( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_float( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_double( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_long_double( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_time_t( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_enum( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_union( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_Bool( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_BOOL( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_TYPE_UnMarshal_Setting( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_ClassMethodID( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_InstanceID( uchar* buf, void* data, short* datasize = 0, short num = 1 );

void* unmarshal_SessionID( uchar* buf, void* data, short* datasize = 0, short num = 1 );


#endif