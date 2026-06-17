#ifndef _BLKC_RECEIVECONTROLOBSERVER_H_
#define _BLKC_RECEIVECONTROLOBSERVER_H_

#include "Runnable.h"

class BLKC_ReceiveControlObserver
{
    public:
        BLKC_ReceiveControlObserver(){}
        virtual ~BLKC_ReceiveControlObserver(){}
        virtual void NotifyReceiveControl(Runnable* processor, uint32_t sockid) = 0;
};

#endif