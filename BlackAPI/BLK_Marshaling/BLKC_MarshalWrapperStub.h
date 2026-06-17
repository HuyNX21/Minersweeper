#if !defined(__BLKC_MARSHALWRAPPERSTUB_H__)
#define	__BLKC_MARSHALWRAPPERSTUB_H__

#include "BLKC_Common.h"
#include "BLKC_MarshalWrapper.h"

class BLKC_MarshalWrapperStub : public BLKC_MarshalWrapper
{
public:

	virtual uint32_t getInstanceId(void* instance);

	virtual uint32_t findInstanceId(void* instance);

	uint32_t getSessionID( uchar* buf, short* datasize );

	template<typename OBJ_T>
	void* marshalInstance( uchar* buf, OBJ_T& data, short* datasize, short num);

	virtual void* marshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize = 0, short num = 1 );
};


#endif