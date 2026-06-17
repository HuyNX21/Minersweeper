#ifndef PCH_H
#define PCH_H

// ===== C++ STL =====
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <iterator>
#include <algorithm>
#include <utility>
#include <exception>

// ===== C standard (C++ style) =====
#include <cstdio>
#include <cstdlib>
#include <cstring>

// ===== POSIX / Linux =====
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <execinfo.h>

using namespace std;

#endif

