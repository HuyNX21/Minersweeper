
#include "pch.h"
#include "BLKC_MarshalWrapper.h"
#include "marsahling.h"
#include "GameState.h"
#include "BestTimeEntry.h"

int mMarshalDummyValiable = 0;
void* mMarshalDummy = &mMarshalDummyValiable;

void* BLKC_MarshalWrapper::marshal( uchar* buf, signed char& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_char( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, signed char*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_char( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, unsigned char& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_char( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, unsigned char*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_char( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, wchar_t& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_wchar_t( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, wchar_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_wchar_t( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, bool& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_bool( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, bool*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_bool( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, char& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_char( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, char*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_char( buf, (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, int32_t& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_int( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, int32_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_int( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, uint32_t& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_int( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, uint32_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_int32_t( buf, (void*)data, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, signed short& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_short( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, signed short*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_short( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, const signed short& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_short( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, const signed short*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_signed_short( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, unsigned short& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_short( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, unsigned short*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_short( buf, (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, int64_t& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_int64_t( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, int64_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_int64_t( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, uint64_t& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_long_long( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, uint64_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_long_long( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, const uint32_t& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_int32_t( buf, (void*)&data, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, const uint32_t*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_unsigned_int32_t( buf, (void*)data, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, float& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_float( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, float*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_float( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, double& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_double( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, double*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_double( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, long double& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_long_double( buf,  (void*)&data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, long double*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshal_long_double( buf,  (void*)data,  datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, void*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return buf;
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, BLKS_COMMONID*& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	uchar* data_pt = buf;
	data_pt = (uchar*)marshal_setCommonID( data_pt, data, datasize );
	
	return data_pt;
}

// BLKC_SizeArray
void* BLKC_MarshalWrapper::marshal( uchar* buf, BLKC_SizeArray<char>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, BLKC_SizeArray<uchar>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, BLKC_SizeArray<uint32_t>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, BLKC_SizeArray<ushort>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshalSizeArray(buf, SizeArray, datasize, num );
}
void* BLKC_MarshalWrapper::marshal( uchar* buf, BLKC_SizeArray<short>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, BLKC_SizeArray<int32_t>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	return marshalSizeArray(buf, SizeArray, datasize, num );
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, GameState& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	int32_t v = static_cast<int32_t>(data);
	return marshal_signed_int( buf, (void*)&v, datasize, num );
}

// ============================================================================================================
// =================================== marshal new defined data type here ====================================
// ============================================================================================================
void* BLKC_MarshalWrapper::marshal( uchar* buf, std::vector<PointCellOpened>& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	uchar* pt = buf;

	short count = (short)data.size();
	pt = (uchar*)marshal_signed_short(pt, (void*)&count, datasize, 1);

	for (const auto& e : data) {
		pt = (uchar*)marshal_int(pt, (void*)&e.x, datasize, 1);
		pt = (uchar*)marshal_int(pt, (void*)&e.y, datasize, 1);
		pt = (uchar*)marshal_int(pt, (void*)&e.adjacentValue, datasize, 1);
	}

	return pt;
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, std::vector<std::pair<int,int>>& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	uchar* pt = buf;

	short count = (short)data.size();
	pt = (uchar*)marshal_signed_short(pt, (void*)&count, datasize, 1);

	for (const auto& e : data) {
		pt = (uchar*)marshal_int(pt, (void*)&e.first, datasize, 1);
		pt = (uchar*)marshal_int(pt, (void*)&e.second, datasize, 1);
	}

	return pt;
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, std::vector<BestTimeEntry>& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	uchar* pt = buf;

	short count = (short)data.size();
	pt = (uchar*)marshal_signed_short(pt, (void*)&count, datasize, 1);

	for (const auto& e : data) {
		pt = (uchar*)marshal_int(pt, (void*)&e.size, datasize, 1);
		pt = (uchar*)marshal_int(pt, (void*)&e.mines, datasize, 1);
		pt = (uchar*)marshal_int(pt, (void*)&e.seconds, datasize, 1);

		// Marshal the playerName string
		short nameLength = static_cast<short>(e.playerName.size());
		pt = (uchar*)marshal_signed_short(pt, (void*)&nameLength, datasize, 1);
		if (nameLength > 0) {
			char* playerNamePtr = const_cast<char*>(e.playerName.c_str());
			pt = (uchar*)marshal_char(pt, (void*)playerNamePtr, datasize, nameLength);
		}
	}

	return pt;
}

void* BLKC_MarshalWrapper::marshal( uchar* buf, BestTimeEntry& data, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER
	uchar* pt = buf;

	pt = (uchar*)marshal_int(pt, (void*)&data.size, datasize, 1);
	pt = (uchar*)marshal_int(pt, (void*)&data.mines, datasize, 1);
	pt = (uchar*)marshal_int(pt, (void*)&data.seconds, datasize, 1);

	// Marshal the playerName string
	short nameLength = static_cast<short>(data.playerName.size());
	pt = (uchar*)marshal_signed_short(pt, (void*)&nameLength, datasize, 1);
	if (nameLength > 0) {
		char* playerNamePtr = const_cast<char*>(data.playerName.c_str());
		pt = (uchar*)marshal_char(pt, (void*)playerNamePtr, datasize, nameLength);
	}

	return pt;
}

// ============================================================================================================
// =================================================== END ====================================================
// ============================================================================================================