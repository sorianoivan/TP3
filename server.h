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
    std::vector<Thread*> clients;
    std::atomic<bool> done_accepting;

    int total_clients;
    int clients_removed;
public:
    Server();
    void run(const char* port, std::string numbers);

    ~Server();

private:
    void getChar();
    bool doneAccepting();
    void acceptClients();
    //bool isClientDone(Thread *client);

};


#endif //_SERVER_H
