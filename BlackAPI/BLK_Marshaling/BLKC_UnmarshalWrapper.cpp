#include "pch.h"
#include <iostream>
#include <string.h>
#include <time.h>

#include "BLKC_UnmarshalWrapper.h"
#include "unmarsahling.h"
#include "GameState.h"

int mUnmarshalDummyValiable = 0;
void* mUnmarshalDummy = &mUnmarshalDummyValiable;

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, signed char& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_char( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,signed char*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_char( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,unsigned char& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_char( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,unsigned char*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_char( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,wchar_t& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_wchar_t( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,wchar_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_wchar_t( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,bool& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_bool( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,bool*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_bool( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,char& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_char( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,char*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_char( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,int32_t& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_int( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,int32_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_int( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,uint32_t& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_int( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,uint32_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_int( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,signed short& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_short( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,signed short*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_short( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,const signed short& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_short( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,const signed short*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_signed_short( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,unsigned short& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_short( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,unsigned short*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_short( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,int64_t& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_int64_t( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,int64_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_int64_t( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,uint64_t& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_long_long( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,uint64_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_long_long( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,const uint32_t& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_int32_t( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,const uint32_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_unsigned_int32_t( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,float& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_float( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,float*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_float( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,double& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_double( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,double*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_double( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,long double& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_long_double( buf,  (void*)&data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,long double*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshal_long_double( buf,  (void*)data,  datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf,void*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return buf;
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, BLKS_COMMONID*& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	uchar* data_pt = buf;
	data_pt = (uchar*)unmarshal_getCommonID( data_pt, data, datasize );
	
	return data_pt;
}

// BLKC_SizeArray
void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, BLKC_SizeArray<char>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, BLKC_SizeArray<uchar>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, BLKC_SizeArray<uint32_t>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, BLKC_SizeArray<ushort>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, BLKC_SizeArray<short>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, BLKC_SizeArray<int32_t>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	return unmarshalSizeArray(buf, SizeArray, datasize, num );
}

// ============================================================================================================
// =================================== unmarshal new defined data type here ===================================
// ============================================================================================================
void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, std::vector<PointCellOpened>& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	uchar* pt = buf;

	short count = 0;
	pt = (uchar*)unmarshal_signed_short(pt, (void*)&count, datasize, 1);

	data.clear();
	data.reserve(count);

	for (int i = 0; i < count; ++i) {
		PointCellOpened p;
		pt = (uchar*)unmarshal_int(pt, (void*)&p.x, datasize, 1);
		pt = (uchar*)unmarshal_int(pt, (void*)&p.y, datasize, 1);
		pt = (uchar*)unmarshal_int(pt, (void*)&p.adjacentValue, datasize, 1);
		data.push_back(p);
	}

	return pt;
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, ::GameState& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	uchar* pt = buf;

	int32_t v = 0;
	pt = (uchar*)unmarshal_signed_int(pt, (void*)&v, datasize, num);
	data = static_cast<GameState>(v);

	return pt;
}

void* BLKC_UnmarshalWrapper::unmarshal( uchar* buf, std::vector<std::pair<int,int>>& data, short* datasize, short num )
{
	DEBUG_PRINT_UNMARSHALING_WRAPPER
	uchar* pt = buf;

	short count = 0;
	pt = (uchar*)unmarshal_signed_short(pt, (void*)&count, datasize, 1);

	data.clear();
	data.reserve(count);

	for (int i = 0; i < count; ++i) {
		std::pair<int,int> p;
		pt = (uchar*)unmarshal_int(pt, (void*)&p.first, datasize, 1);
		pt = (uchar*)unmarshal_int(pt, (void*)&p.second, datasize, 1);
		data.push_back(p);
	}

	return pt;
}

// ============================================================================================================
// =================================================== END ====================================================
// ============================================================================================================