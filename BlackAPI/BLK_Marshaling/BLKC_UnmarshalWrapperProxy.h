
#if !defined(__BLKC_UNMARSHALWRAPPERPROXY_H__)
#define	__BLKC_UNMARSHALWRAPPERPROXY_H__

#include "BLKC_Common.h"
#include "BLKC_UnmarshalWrapper.h"
#include "BLKC_ProxyManager.h"

class BLKC_UnmarshalWrapperProxy : public BLKC_UnmarshalWrapper
{
    public:
        virtual void* getInstance(uint32_t instanceId);

        void setInstanceIdAndObjectPt(uint32_t instanceId, void* objectPt);

        template<typename OBJ_T,typename IMP_T>
        void* unmarshalInstance( uchar* buf, OBJ_T*& data, short* datasize, short num );

        virtual void* unmarshal( uchar* buf, BLKC_CallbackPointerContainer& data, short* datasize = 0, short num = 1 );
};

#endif