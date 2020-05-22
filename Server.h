#ifndef _SERVER_H
#define _SERVER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "FileException.h"
#include "SocketException.h"
#include "FileReader.h"
#include "Socket.h"
#include "Acceptor.h"

class Server {
private:
    Socket bind_skt;
    std::vector<int> secret_nums;
public:
    Server();
    void run(const char* port, std::string numbers);
    ~Server();

private:
};


#endif //_SERVER_H
