#define _BSD_SOURCE

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "inet_socket.h"
#include "tlpi_hdr.h"

int inetConnect(const char* host, const char* service, int type)
{
    struct addrinfo hints;
    struct addrinfo* result, *rp;
    int sfd, s;

    memset(&hints, 0, sizeof(struct addrinfo));
    
}