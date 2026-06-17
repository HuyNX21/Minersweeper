#include "pch.h"
#include "BLKC_Log.h"
#include "SignalHandle.h"

extern std::string getGDBBacktrace()
{
    std::string backtrace;
    pid_t pid = getpid();
 
    char command[CMDLEN] = {};
    char lineBuf[LINELEN] = {};
    snprintf( command, sizeof( command ), "gdb -batch -iex \"set auto-load safe-path /lib\" -ex bt -pid %d < /dev/null 2> /dev/null", pid );
 
    FILE* fp = popen( command, "r" );
 
    if ( NULL != fp ) {
        while ( fgets( lineBuf, sizeof( lineBuf ), fp ) ) {
            if ( '#' == lineBuf[0] ) {
                backtrace += lineBuf;
            }
        }
        pclose( fp );
    } else {
        LOG_ERROR( "popen( %s, r)", command );
    }
 
    return backtrace;
}

extern void seg_handler(int sig, siginfo_t *info, void *ucontext) {

	LOG_ERROR("[Signal segF] Detected SIGSEGV from process!");
	cout << getGDBBacktrace();
    _exit(1);
}