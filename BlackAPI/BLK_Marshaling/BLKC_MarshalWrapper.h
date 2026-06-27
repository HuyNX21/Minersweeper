
#if !defined(__BLKC_MARSHALWRAPPER_H__)
#define	__BLKC_MARSHALWRAPPER_H__

#include <vector>

#include "BLKC_Common.h"
#include "BLKC_MarshalParamaterWrapper.h"
#include "BLKC_CallbackPointerContainer.h"

// forward declare GameState	
enum class GameState;
struct BestTimeEntry;

// #define BLK_MARSHALING_WRAPPER_DEBUG (1)
#if defined(BLK_MARSHALING_WRAPPER_DEBUG)
#define DEBUG_PRINT_MARSHALING_WRAPPER std::cout << __FILE__<<":"<<__LINE__<<"    "<<__PRETTY_FUNCTION__ << std::endl;
#else
#define DEBUG_PRINT_MARSHALING_WRAPPER
#endif

extern void* mMarshalDummy;

class BLKC_MarshalWrapper
{
    public: 
        template< typename T1, typename T2, typename T3, typename T4, typename T5>
        uchar* marshalParams(uchar* pt, short* size, T1&, T2&, T3&, T4&, T5&);
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        uchar* marshalParams(uchar* pt, short* size, T1&, T2&, T3&, T4&, T5&, T6&);

        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        uchar* marshalParams(uchar* pt, short* size, T1&, T2&, T3&, T4&, T5&, T6&, T7& );

        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        uchar* marshalParams(uchar* pt, short* size, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8& );
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
        uchar* marshalParams(uchar* pt, short* size, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&);
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
        uchar* marshalParams(uchar* pt, short* size, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&);
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
            typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
        uchar* marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
                                T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17 );
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
            typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19 >
        uchar* marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
                                T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17, T18& a18, T19& a19 );

        template< typename T1, typename T2, typename T3, typename T4, typename T5>
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1&, T2&, T3&, T4&, T5&);
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1&, T2&, T3&, T4&, T5&, T6&);

        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1&, T2&, T3&, T4&, T5&, T6&, T7& );

        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8& );
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&);
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&);
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
            typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
                                T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17 );
        
        template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
            typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19 >
        uchar* marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
                                T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17, T18& a18, T19& a19 );

        virtual void* marshal( unsigned char* buf, signed char& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, signed char*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, unsigned char& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, unsigned char*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, wchar_t& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, wchar_t*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, bool& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, bool*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, char& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, char*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, int32_t& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, int32_t*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, uint32_t& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, uint32_t*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, signed short& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, signed short*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, const signed short& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, const signed short*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, unsigned short& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, unsigned short*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, int64_t& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, int64_t*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, uint64_t& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, uint64_t*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, const uint32_t& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, const uint32_t*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, float& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, float*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, double& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, double*& data, short* datasize, short num = 1 );

        virtual void* marshal( unsigned char* buf, long double& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, long double*& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, void*& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, BLKS_COMMONID*& data, short* datasize = 0, short num = 1 );

		// virtual void* marshal( uchar* buf, BLKS_COMMONID*& data, MESSAGE_SIZE_T* datasize = 0, MESSAGE_SIZE_T num = 1 );

        virtual uint32_t getInstanceId(void* instance) = 0;

		virtual void* marshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize = 0, short num = 1 ) = 0;

		// BLKC_SizeArray 
		template<typename ARRAY_T>
		uchar* marshalSizeArray( uchar* buf, BLKC_SizeArray<ARRAY_T>& SizeArray, short* datasize = 0, short num = 1  );

		virtual void* marshal( uchar* buf, BLKC_SizeArray<char>& SizeArray, short* datasize = 0, short num = 1  );
			
		virtual void* marshal( uchar* buf, BLKC_SizeArray<uchar>& SizeArray, short* datasize = 0, short num = 1  );
			
		virtual void* marshal( uchar* buf, BLKC_SizeArray<uint32_t>& SizeArray, short* datasize = 0, short num = 1  );
			
		virtual void* marshal( uchar* buf, BLKC_SizeArray<ushort>& SizeArray, short* datasize = 0, short num = 1  );
			
		virtual void* marshal( uchar* buf, BLKC_SizeArray<short>& SizeArray, short* datasize = 0, short num = 1  );

		virtual void* marshal( uchar* buf, BLKC_SizeArray<int32_t>& SizeArray, short* datasize = 0, short num = 1 );

		template<typename ARRY_T>
		void* marshal( uchar* buf, const std::vector< BLKC_SizeArray<ARRY_T> >& list, short* datasize = 0, short num = 1 );

		// ============================================================================================================
		// ==================================== marshal new defined data type here ====================================
		// ============================================================================================================
		virtual void* marshal( unsigned char* buf, GameState& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, std::vector<PointCellOpened>& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, std::vector<std::pair<int,int>>& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, std::vector<BestTimeEntry>& data, short* datasize, short num = 1 );

		virtual void* marshal( unsigned char* buf, BestTimeEntry& data, short* datasize, short num = 1 );

		// ============================================================================================================
		// =================================================== END ====================================================
		// ============================================================================================================
};

template< typename T1, typename T2, typename T3, typename T4, typename T5> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	pt = (uchar*)marshal(pt, a10, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
		  typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
										     T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17 )
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	pt = (uchar*)marshal(pt, a10, size);
	pt = (uchar*)marshal(pt, a11, size);
	pt = (uchar*)marshal(pt, a12, size);
	pt = (uchar*)marshal(pt, a13, size);
	pt = (uchar*)marshal(pt, a14, size);
	pt = (uchar*)marshal(pt, a15, size);
	pt = (uchar*)marshal(pt, a16, size);
	pt = (uchar*)marshal(pt, a17, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
		  typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19 >
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, short* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
										     T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17, T18& a18, T19& a19 )
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	pt = (uchar*)marshal(pt, a10, size);
	pt = (uchar*)marshal(pt, a11, size);
	pt = (uchar*)marshal(pt, a12, size);
	pt = (uchar*)marshal(pt, a13, size);
	pt = (uchar*)marshal(pt, a14, size);
	pt = (uchar*)marshal(pt, a15, size);
	pt = (uchar*)marshal(pt, a16, size);
	pt = (uchar*)marshal(pt, a17, size);
	pt = (uchar*)marshal(pt, a18, size);
	pt = (uchar*)marshal(pt, a19, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> 
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10)
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	pt = (uchar*)marshal(pt, a10, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
		  typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17 >
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
										     T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17 )
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	pt = (uchar*)marshal(pt, a10, size);
	pt = (uchar*)marshal(pt, a11, size);
	pt = (uchar*)marshal(pt, a12, size);
	pt = (uchar*)marshal(pt, a13, size);
	pt = (uchar*)marshal(pt, a14, size);
	pt = (uchar*)marshal(pt, a15, size);
	pt = (uchar*)marshal(pt, a16, size);
	pt = (uchar*)marshal(pt, a17, size);
	
	return pt;
}

template< typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
		  typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19 >
uchar* BLKC_MarshalWrapper::marshalParams(uchar* pt, MESSAGE_SIZE_T* size, T1& a1, T2& a2, T3& a3, T4& a4, T5& a5, T6& a6, T7& a7, T8& a8, T9& a9, T10& a10,
										     T11& a11, T12& a12, T13& a13, T14& a14, T15& a15, T16& a16, T17& a17, T18& a18, T19& a19 )
{
	pt = (uchar*)marshal(pt, a1, size);
	pt = (uchar*)marshal(pt, a2, size);
	pt = (uchar*)marshal(pt, a3, size);
	pt = (uchar*)marshal(pt, a4, size);
	pt = (uchar*)marshal(pt, a5, size);
	pt = (uchar*)marshal(pt, a6, size);
	pt = (uchar*)marshal(pt, a7, size);
	pt = (uchar*)marshal(pt, a8, size);
	pt = (uchar*)marshal(pt, a9, size);
	pt = (uchar*)marshal(pt, a10, size);
	pt = (uchar*)marshal(pt, a11, size);
	pt = (uchar*)marshal(pt, a12, size);
	pt = (uchar*)marshal(pt, a13, size);
	pt = (uchar*)marshal(pt, a14, size);
	pt = (uchar*)marshal(pt, a15, size);
	pt = (uchar*)marshal(pt, a16, size);
	pt = (uchar*)marshal(pt, a17, size);
	pt = (uchar*)marshal(pt, a18, size);
	pt = (uchar*)marshal(pt, a19, size);
	
	return pt;
}

template<typename ARRAY_T>
uchar* BLKC_MarshalWrapper::marshalSizeArray( uchar* buf, BLKC_SizeArray<ARRAY_T>& SizeArray, short* datasize, short num )
{
	DEBUG_PRINT_MARSHALING_WRAPPER

	short arraySize = 0;
	ARRAY_T* array = SizeArray.getDataptr();

	if( array != NULL )
	{
		arraySize = SizeArray.getSize();
	}

	buf = (uchar*)marshal(buf, arraySize, datasize );

	if( array != NULL )
	{
		buf = (uchar*)marshal(buf, array, datasize, arraySize );
	}

	return buf;
}

template<typename ARRY_T>
void* BLKC_MarshalWrapper::marshal( uchar* buf, const std::vector< BLKC_SizeArray<ARRY_T> >& list, short* datasize, short num )
{
    uchar* data_pt = buf;
    short listsize = static_cast<short>(list.size());

    data_pt = (uchar*)marshal(data_pt, listsize, datasize);

    if (listsize == 0) {
        return data_pt;
    }

    for (const auto& sizeArray : list) {
        data_pt = (uchar*)marshal(data_pt, sizeArray, datasize, num);
    }

    return data_pt;
}

#endif