#ifndef BLKC_LOG_H
#define BLKC_LOG_H

#include <vector>
#include <stdint.h>
#include <sys/types.h>
#include <string>
#include <inttypes.h>
#include <cstdio>
#include <cstdarg>
#include <mutex>
#include <ctime>
#include <sys/syscall.h>
#include <unistd.h>
#include <cstring>

#include "Thread.h"

inline std::string getFuncName(const std::string& pretty) {
    size_t colons = pretty.find("::");
    if (colons == std::string::npos) {
        size_t start = pretty.rfind(' ') + 1;
        size_t end = pretty.find('(');
        return pretty.substr(start, end - start);
    }

    size_t start = pretty.rfind(' ', colons) + 1;

    size_t end = pretty.find('(');

    return pretty.substr(start, end - start);
}

inline const char* extractFileName(const char* path)
{
    const char* slash1 = strrchr(path, '/');
    const char* slash2 = strrchr(path, '\\');

    const char* slash = (slash1 > slash2) ? slash1 : slash2;

    return slash ? slash + 1 : path;
}

#define __FILE_NAME__ extractFileName(__FILE__)
#define __FUNC_NAME__ getFuncName(__PRETTY_FUNCTION__).c_str()

// #define BLK_ENABLE_LOG_DEBUG (1)
#if defined(BLK_ENABLE_LOG_DEBUG)
#define LOG_DEBUG(fmt, ...) log(DEBUG, __FILE_NAME__,__LINE__,__FUNC_NAME__, fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif

#define LOG_INFO(fmt, ...)  log(INFO,  __FILE_NAME__,__LINE__,__FUNC_NAME__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  log(WARN,  __FILE_NAME__,__LINE__,__FUNC_NAME__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) log(ERROR, __FILE_NAME__,__LINE__,__FUNC_NAME__, fmt, ##__VA_ARGS__)

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

inline const char* level_to_string(LogLevel level) {
    switch(level) {
        case DEBUG: return "DEBUG";
        case INFO:  return "INFO";
        case WARN:  return "WARN";
        case ERROR: return "ERROR";
        case FATAL: return "FATAL";
        default:    return "UNK";
    }
}

// Code color ANSI
#define COLOR_RESET   "\033[0m"
#define COLOR_DEBUG   "\033[36m"  // cyan
#define COLOR_INFO    "\033[32m"  // green
#define COLOR_WARN    "\033[33m"  // yellow
#define COLOR_ERROR   "\033[31m"  // red
#define COLOR_FATAL   "\033[1;31m"// bold red

inline const char* level_to_color(LogLevel level) {
    switch(level) {
        case DEBUG: return COLOR_DEBUG;
        case INFO:  return COLOR_INFO;
        case WARN:  return COLOR_WARN;
        case ERROR: return COLOR_ERROR;
        case FATAL: return COLOR_FATAL;
        default:    return COLOR_RESET;
    }
}

inline std::mutex log_mutex;

inline void log(LogLevel level, const char* file, int line, const char* func, const char* fmt, ...) {
    std::lock_guard<std::mutex> lock(log_mutex);

    std::string currentThreadName = "";

    Thread* current = Thread::currentThread();

    if (current != NULL)
    {
        currentThreadName = current->getName();
    }
    else
    {
        char threadName[16] = {0};
        pthread_getname_np(pthread_self(), threadName, sizeof(threadName));
        currentThreadName = threadName;

        if(currentThreadName.empty())
            currentThreadName = "Unknow thread";
    }

    const char* color = level_to_color(level);

    printf("%s[%s][%s][%s:%d - %s]%s ",
           color,
           level_to_string(level),
           currentThreadName.c_str(),
           file,
           line,
           func,
           COLOR_RESET);

    // message
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}


#endif // BLKC_LOG_H