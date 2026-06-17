
#ifndef __BLKC_PORTNUMBER_H_
#define __BLKC_PORTNUMBER_H_


typedef unsigned short PORT_NUM_T;
static const PORT_NUM_T SERVER_SERVER_PORT = 50000;
static const PORT_NUM_T CLIENT_SERVER_PORT = 50001;

#define SOCKET_FILE_PATH	"/var/spool/sockets/BlackApi/"

#define SOCKET_FILE_SERVER	"ServerProcess"

#define SOCKET_FILE_CLIENT	"ClientProcess"

#endif // __BLKC_PORTNUMBER_H_