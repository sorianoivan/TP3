#ifndef _COMMONSOCKET_H
#define _COMMONSOCKET_H

#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "SocketException.h"

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
    //void setUpConnection(const std::string port) hacer la del cliente con polimorfismo
    Socket accept();
    int getFd() const;
    int receive(void* msg, int len) const;
    int send(const void *msg, int msg_len) const;

    ~Socket();
private:
    explicit Socket(int fd);
    void _setAddrInfo(struct addrinfo** results, const char* port);//server
    //void _setAddrInfo(struct addrinfo** results, const char* port);hacer la del cliente con polimorfismo
    void _bind(addrinfo *results, int &skt);


};


#endif //_COMMONSOCKET_H
