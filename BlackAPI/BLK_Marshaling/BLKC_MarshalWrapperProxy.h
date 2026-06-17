
#if !defined(__BLKC_MARSHALWRAPPERPROXY_H__)
#define	__BLKC_MARSHALWRAPPERPROXY_H__

#include "BLKC_Common.h"
#include "BLKC_MarshalWrapper.h"
#include "BLKC_ProxyManager.h"

class BLKC_MarshalWrapperProxy : public BLKC_MarshalWrapper
{
public:
	virtual uint32_t getInstanceId(void* instance);

	template<typename OBJ_T>
	void* marshalInstance( uchar* buf, OBJ_T& data, short* datasize, short num);

	virtual void* marshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize = 0, short num = 1 );

};


#endif