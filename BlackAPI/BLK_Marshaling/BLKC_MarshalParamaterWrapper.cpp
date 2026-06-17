#include "pch.h"
#include "BLKC_MarshalParamaterWrapper.h"

template<> 
void BLKC_NullEndArray<char>::calcDataSize()
{
	if( mDataptr == NULL )
	{
		mSize = 0;
	}else
	{
		std::string str(mDataptr);
		mSize = (short)str.size();
	}
}
#if 1
template<> 
void BLKC_NullEndArray<const char>::calcDataSize()
{
	if( mDataptr == NULL )
	{
		mSize = 0;
	}else
	{
		std::string str(mDataptr);
		mSize = (short)str.size();
	}
}
#endif

void BLKC_SpecificConversion::setAddrptr(char c_ID, void* vp_addrptr)
{
	mID = c_ID;
	mAddrptr = vp_addrptr;
}

void* BLKC_SpecificConversion::getAddrptr(char* c_ID)
{
	c_ID = &mID;
	return mAddrptr;
}

