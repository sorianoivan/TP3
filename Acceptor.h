#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H

#include "Socket.h"
#include "Messenger.h"
#include <iostream>
#include <vector>

class Acceptor {
private:
    Socket peer_skt;
    std::vector<int> secret_nums;
    //std::vector<Messenger*> clients; capaz va Thread*
public:
    explicit Acceptor(std::vector<int>&& secret_nums);
    void acceptClients(Socket& skt);
    ~Acceptor();
};


#endif //_ACCEPTOR_H
