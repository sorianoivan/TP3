#include "server.h"

#include <thread>

Server::Server() {
    done_accepting = false;
}

void Server::run(const char* port, std::string numbers) {//uso char* por el getaddrinfo
    FileReader file_reader(std::move(numbers));
    file_reader.processFile(secret_nums);

    bind_skt.setUpConnection(port);
    if (listen(bind_skt.getFd(), 10) == -1)
        throw SocketException("Error listen");

    //Acceptor acceptor(std::move(secret_nums));
    //acceptor.acceptClients(bind_skt);
    std::thread th(&Server::getChar, this);
    //while (!doneAccepting()){
        acceptClients();
    //}
    for (auto & client : clients){
        client->join();
    }
    th.join();

}

void Server::acceptClients() {
    int i = 0;
    while (!doneAccepting()) {
        Socket peer_skt = bind_skt.accept();
        if (peer_skt.getFd() != -1) {
            clients.push_back(new Messenger(std::move(peer_skt), secret_nums[0]));
            clients[i]->start();
            i++;
        }
    }
}


Server::~Server() {}

void Server::getChar() {
    char cmd;
    do {
        std::cin >> cmd;
    }while (cmd != 'q');
     done_accepting = true;
}

bool Server::doneAccepting() {
    return done_accepting;
}



