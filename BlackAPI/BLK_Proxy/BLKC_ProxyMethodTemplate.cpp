
#include "pch.h"
#include "BLKC_ProxyMethodTemplate.h"
#include "BLKC_MarshalWrapperProxy.h"
#include "BLKC_UnmarshalWrapperProxy.h"


BLKC_MarshalWrapper* BLKC_ProxyMethodTemplate::mMarshalWrapper = NULL;
BLKC_UnmarshalWrapper* BLKC_ProxyMethodTemplate::mUnmarshalWrapper = NULL;

BLKC_MarshalWrapper* BLKC_ProxyMethodTemplate::getMarshalWrapper()
{
	static BLKC_MarshalWrapperProxy c_MarshalWrapperProxy;
	
	if( mMarshalWrapper == NULL )
	{
		mMarshalWrapper = &c_MarshalWrapperProxy;
	}
	
	return mMarshalWrapper;
}
BLKC_UnmarshalWrapper* BLKC_ProxyMethodTemplate::getUnmarshalWrapper()
{
	static BLKC_UnmarshalWrapperProxy c_UnmarshalWrapperProxy;
	
	if( mUnmarshalWrapper == NULL )
	{
		mUnmarshalWrapper = &c_UnmarshalWrapperProxy;
	}
	
	return mUnmarshalWrapper;
}