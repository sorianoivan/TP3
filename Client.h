#ifndef _CLIENT_H
#define _CLIENT_H

#include "Socket.h"
#include "Verifier.h"
#include <iostream>

class Client {
private:
    Socket client_skt;
    Verifier verifier;
public:
    Client();
    void run(const char* host, const char* port);
    ~Client();

    void getCommand();

    int receiveResponse();
};


#endif //_CLIENT_H
