#ifndef INET_SOCKETS_H
#define INET_SOCKETS_H

#include <sys/socket.h>
#include <netdb.h>

int inetconnect(const char* host, const char* service, int type);

int inetListen(const char* service, int backlog, socklen_t* addrlen);

int inetbind(const char* service, int type, socklen_t* addrlen);

char* inetAddressStr(const struct sockaddr* arrd, socklen_t addrlen, char* addrStr, int addrStrLen);

#define IS_ADDR_STR_LEN 4096

#endif