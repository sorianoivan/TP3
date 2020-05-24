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
#include "server_messenger.h"
#include <atomic>

class Server {
private:
    Socket bind_skt;
    std::vector<int> secret_nums;
    std::vector<Thread*> clients;
    std::atomic<bool> done_accepting;

    int total_clients;
    int clients_removed;
    std::atomic<int> winners;
    //std::atomic<int> losers;
public:
    Server();
    void run(const char* port, std::string numbers);//hacerla con el operator()

    ~Server();

private:
    void getChar();
    bool doneAccepting();
    void acceptClients();
};


#endif //_SERVER_H
