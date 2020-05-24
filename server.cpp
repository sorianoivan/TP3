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

    Acceptor acceptor(std::move(secret_nums));
    acceptor.acceptClients(bind_skt);

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



