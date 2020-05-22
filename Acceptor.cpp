#include "Acceptor.h"

Acceptor::Acceptor(std::vector<int>&& secret_nums) {
    this->secret_nums = std::move(secret_nums);
}

void Acceptor::acceptClients(Socket& skt) {
    //while skt not closed(meterle la variable bool a commonsocket)
    /*try {
        peer_skt = skt.accept();
    } catch (SocketException& e) {                 //Ver si conviene exception o no
        std::cerr << e.what() << std::endl
    }*/
    peer_skt = skt.accept();
    if (peer_skt.getFd() != -1) {
        //agarrar numero secreto correcto de la lista. pAra eso voya  tener q tener una variable cantClientes
        //add client to list
        Messenger client(std::move(peer_skt), secret_nums[0]);
        client.run();
        //start communication with client thread
        //iterate list and remove finished clients
    }

    //stop and remove all clients in list
}

Acceptor::~Acceptor() {}
