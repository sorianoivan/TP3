#ifndef _COMMONSOCKET_H
#define _COMMONSOCKET_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "common_socket_exception.h"

class Socket {
private:
    int fd; //file descriptor

public:
    Socket();
    Socket(const Socket& skt) = delete;//borro constr por copia
    Socket(Socket&& skt) noexcept;//constructor por movimiento

    Socket& operator=(const Socket& skt) = delete;
    Socket& operator=(Socket&& skt) noexcept;

    void setUpConnection(const char* port);//server
    void setUpConnection(const char *host, const char *port);//client
    //void setUpConnection(const char *host, const char *port);
    Socket accept();
    int getFd() const;
    int receive(void* msg, int len) const;
    int send(const void *msg, int msg_len) const;

    ~Socket();

private:
    explicit Socket(int fd);
    void _setAddrInfo(struct addrinfo** results, const char* port);
    /*void _setAddrInfo(struct addrinfo** results, const char* host,
                      const char* port, const char* mode);*/

    void _bind(addrinfo *results, int &skt);
    void _setAddrInfo(addrinfo **results, const char *host, const char *port);
};


#endif //_COMMONSOCKET_H
