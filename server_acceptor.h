#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H

#include "common_socket.h"
#include "server_messenger.h"
#include <iostream>
#include <vector>

class Acceptor {
private:
    Socket peer_skt;
    std::vector<int> secret_nums;

    //int total_clients;
    //std::vector<Messenger*> clients; capaz va Thread*
public:
    explicit Acceptor(std::vector<int>&& secret_nums);
    void acceptClients(Socket& skt);//static por lo de thread, cambiar dsps
    //void operator()();
    ~Acceptor();
};


#endif //_ACCEPTOR_H
