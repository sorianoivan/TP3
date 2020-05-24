#ifndef _SERVER_H
#define _SERVER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "server_file_exception.h"
#include "common_socket_exception.h"
#include "server_file_reader.h"
#include "common_socket.h"
#include "server_acceptor.h"
#include <atomic>

class Server {
private:
    Socket bind_skt;
    std::vector<int> secret_nums;
    std::atomic<bool> done_accepting;
public:
    Server();
    void run(const char* port, std::string numbers);
    void getChar();
    bool doneAccepting();
    ~Server();

private:
};


#endif //_SERVER_H
