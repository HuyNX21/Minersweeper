#include "pch.h"
#include "BLKC_StubMethodTemplate.h"

#include "BLKC_MarshalWrapper.h"
#include "BLKC_UnmarshalWrapper.h"
#include "BLKC_MarshalWrapperStub.h"
#include "BLKC_UnmarshalWrapperStub.h"

BLKC_MarshalWrapper* BLKC_StubMethodTemplate::mMarshalWrapper = NULL;
BLKC_UnmarshalWrapper* BLKC_StubMethodTemplate::mUnmarshalWrapper = NULL;

BLKC_MarshalWrapper* BLKC_StubMethodTemplate::getMarshalWrapper()
{
	static BLKC_MarshalWrapperStub c_MarshalWrapperStub;
	
	if( mMarshalWrapper == NULL )
	{
		mMarshalWrapper = &c_MarshalWrapperStub;
	}
	
	return mMarshalWrapper;
}

BLKC_UnmarshalWrapper* BLKC_StubMethodTemplate::getUnmarshalWrapper()
{
	static BLKC_UnmarshalWrapperStub c_UnmarshalWrapperStub;
	
	if( mUnmarshalWrapper == NULL )
	{
		mUnmarshalWrapper = &c_UnmarshalWrapperStub;
	}
	
	return mUnmarshalWrapper;
}
