#ifndef _SIGNALHANDLE_H_
#define _SIGNALHANDLE_H_

#include <signal.h>

static const int32_t    CMDLEN =        ( 256+1 );
static const int32_t    LINELEN =       ( 1024+1 );

extern std::string getGDBBacktrace();
extern void seg_handler(int sig, siginfo_t *info, void *ucontext);

#endif