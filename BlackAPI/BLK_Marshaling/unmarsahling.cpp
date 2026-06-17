#include "unmarsahling.h"

void* unmarshal_getCommonID(  uchar* buf, BLKS_COMMONID* type_id, short* ss_datasize )
{
	DEBUG_PRINT
	buf = (uchar *)unmarshal_ClassMethodID(buf , &(type_id->ClassMethodID), ss_datasize );
	buf = (uchar *)unmarshal_InstanceID(buf , &(type_id->InstanceID), ss_datasize );
	buf = (uchar *)unmarshal_SessionID( buf , &(type_id->SessionID), ss_datasize );
	return buf;
}

void* unmarshal_char( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(char);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_signed_char( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	
	short s_typesize= sizeof(signed char);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_signed_char2( uchar* buf, void* data, int32_t* datasize, int32_t num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(signed char);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_unsigned_char( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	
	short s_typesize= sizeof(unsigned char);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_unsigned_int32_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	
	short s_typesize= sizeof(uint32_t);

	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;
	
	return pt;
}

void* unmarshal_wchar_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	
	short s_typesize= sizeof(wchar_t);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_bool( uchar* buf, void* data, short* datasize, short num )
{
	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(bool);
	
	memcpy( ( uchar* )data, pt, ( s_typesize *num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_int( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(int);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_signed_int( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

    short s_typesize= sizeof(signed int);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_unsigned_int( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(unsigned int);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_short( uchar* buf, void* data, short* datasize, short num )
{
	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(short);
	
	memcpy( ( uchar* )data, pt, ( s_typesize *num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_signed_short( uchar* buf, void* data, short* datasize, short num )
{
	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(signed short);
	
	memcpy( ( uchar* )data, pt, ( s_typesize *num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_unsigned_short( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(unsigned short);
	
	memcpy( ( uchar* )data, pt, ( s_typesize *num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_int64_t( uchar* buf, void* data, short* datasize, short num )//mod
{
	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(int64_t);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}


void* unmarshal_int32_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(int32_t);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_signed_int32_t( uchar* buf, void* data, short* datasize, short num )//mod
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(signed int32_t);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_unsigned_long_long( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(uint64_t);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

    pt += s_typesize * num;

	return pt;
}

void* unmarshal_float( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	
	short s_typesize= sizeof(float);
	
	memcpy( ( uchar* )data, pt, ( s_typesize *num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_double( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(double);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_long_double( uchar* buf, void* data, short* datasize, short num )
{
    	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(long double);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_time_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(time_t);
	
	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

	pt += s_typesize * num;

	return pt;
}

void* unmarshal_enum( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	return pt;
}

void* unmarshal_union( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	memcpy( ( uchar* )data, pt, num );

	pt += num;

	return pt;
}

// void* unmarshal_Bool( uchar* buf, void* data, short* datasize, short num )
// {

// 	DEBUG_PRINT

// 	uchar* pt = buf;

	
// 	short s_typesize= sizeof(Bool);

// 	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

// 	pt += s_typesize * num;

// 	return pt;
// }

// void* unmarshal_BOOL( uchar* buf, void* data, short* datasize, short num )
// {
// 	DEBUG_PRINT

// 	uchar* pt = buf;
	
// 	short s_typesize= sizeof(BOOL);
	
// 	memcpy( ( uchar* )data, pt, ( s_typesize * num ) );

// 	pt += s_typesize * num;

// 	return pt;
// }

void* unmarshal_TYPE_UnMarshal_Setting( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	signed char* work = ( signed char* )data;


	pt = ( uchar* )unmarshal_signed_char( pt,work,datasize,num );

	return pt;
}

void* unmarshal_ClassMethodID( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	uint32_t* work = ( uint32_t* )data;

	pt = ( uchar* )unmarshal_unsigned_int32_t( pt,work,datasize,num );

	return pt;
}

void* unmarshal_InstanceID( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

    uint32_t* work = ( uint32_t* )data;

	pt = ( uchar* )unmarshal_unsigned_int32_t( pt,work,datasize,num );

	return pt;
}

void* unmarshal_SessionID( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

    uint32_t* work = ( uint32_t* )data;

	pt = ( uchar* )unmarshal_unsigned_int32_t( pt,work,datasize,num );

	return pt;
}