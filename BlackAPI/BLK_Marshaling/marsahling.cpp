#include "BLKC_Common.h"
#include "marsahling.h"

void* marshal_setCommonID(  uchar* buf, BLKS_COMMONID* type_id, short* ss_datasize )
{
	DEBUG_PRINT
	buf = (uchar *)marshal_ClassMethodID(buf , &(type_id->ClassMethodID), ss_datasize );
	buf = (uchar *)marshal_InstanceID(buf , &(type_id->InstanceID), ss_datasize );
	buf = (uchar *)marshal_SessionID( buf , &(type_id->SessionID), ss_datasize );
	return buf;
}

void* marshal_char( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(char);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_signed_char( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(signed char);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_signed_char2( uchar* buf, void* data, int32_t* datasize, int32_t num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(signed char);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) += s_typesize * num;

	pt += s_typesize * num;

	return pt;
}

void* marshal_unsigned_char( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(unsigned char);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_wchar_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(wchar_t);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);			

	pt += s_typesize * num;

	return pt;
}

void* marshal_bool( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(bool);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_int( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(int);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_signed_int( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(signed int);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_unsigned_int( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	
	short s_typesize= sizeof(unsigned int);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_short( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(short);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_signed_short( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(signed short);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_unsigned_short( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(unsigned short);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_int64_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	short s_typesize= sizeof(int64_t);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);

	pt += s_typesize * num;

	return pt;
}

void* marshal_int32_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(int32_t);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_signed_int32_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(int32_t);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_unsigned_int32_t( uchar* buf, void* data, short* datasize, short num )
{
	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(uint32_t);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_unsigned_long_long( uchar* buf, void* data, short* datasize, short num )
{
	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(uint64_t);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_float( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(float);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_double( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(double);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_long_double( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(long double);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_time_t( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;
	
	short s_typesize= sizeof(time_t);
	
	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

	(*datasize) = (short)((*datasize) + s_typesize * num);		

	pt += s_typesize * num;

	return pt;
}

void* marshal_enum( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	return pt;
}

void* marshal_union( uchar* buf, void* data, short* datasize, short num )
{
	DEBUG_PRINT

	uchar* pt = buf;

	memcpy( pt, ( uchar* )data,  num  );

	(*datasize) = (short)((*datasize) +  num);		

	pt += num;

	return pt;
}

// void* marshal_Bool( uchar* buf, void* data, short* datasize, short num )
// {

// 	DEBUG_PRINT

// 	uchar* pt = buf;

	
// 	short s_typesize= sizeof(Bool);
	
// 	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

// 	(*datasize) = (short)((*datasize) + s_typesize * num);		

// 	pt += s_typesize * num;

// 	return pt;
// }

// void* marshal_BOOL( uchar* buf, void* data, short* datasize, short num )
// {

// 	DEBUG_PRINT

// 	uchar* pt = buf;

	
// 	short s_typesize= sizeof(BOOL);
	
// 	memcpy( pt, ( uchar* )data, ( s_typesize * num ) );

// 	(*datasize) = (short)((*datasize) + s_typesize * num); 

// 	pt += s_typesize * num;

// 	return pt;
// }

void* marshal_TYPE_Marshal_Setting( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	signed char* work = ( signed char* )data;

	pt = ( uchar* )marshal_signed_char( pt,work,datasize,num );

	return pt;
}

void* marshal_ClassMethodID( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	uintptr_t* work = ( uintptr_t* )data;

	pt = ( uchar* )marshal_unsigned_int32_t( pt,work,datasize,num );

	return pt;
}

void* marshal_InstanceID( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	uintptr_t* work = ( uintptr_t* )data;

	pt = ( uchar* )marshal_unsigned_int32_t( pt,work,datasize,num );

	return pt;
}

void* marshal_SessionID( uchar* buf, void* data, short* datasize, short num )
{

	DEBUG_PRINT

	uchar* pt = buf;

	uintptr_t* work = ( uintptr_t* )data;

	pt = ( uchar* )marshal_unsigned_int32_t( pt,work,datasize,num );

	return pt;
}