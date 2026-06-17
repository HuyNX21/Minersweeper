#if !defined(__BLKC_UNMARSHALWRAPPERSTUB_H__)
#define	__BLKC_UNMARSHALWRAPPERSTUB_H__

#include "BLKC_Common.h"
#include "BLKC_UnmarshalWrapper.h"

class BLKC_UnmarshalWrapperStub : public BLKC_UnmarshalWrapper
{
public:
	virtual void* getInstance(uint32_t instanceId);

	uint32_t getInstanceId(void* instance);

	template<typename OBJ_T>
	void* unmarshalInstance( uchar* buf, OBJ_T*& data, short* datasize, short num );

	virtual void* unmarshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize = 0, short num = 1 );
};

#endif