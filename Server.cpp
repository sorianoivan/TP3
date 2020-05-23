#include "Server.h"

#include <utility>

Server::Server() {}

void Server::run(const char* port, std::string numbers) {//uso char* por el getaddrinfo
    FileReader file_reader(std::move(numbers));
    file_reader.processFile(secret_nums);

    bind_skt.setUpConnection(port);

    if (listen(bind_skt.getFd(), 10) == -1) throw SocketException("Error listen");

    /* aca voy a tirar el thread aceptador */
    Acceptor acceptor(std::move(secret_nums));//fijarme si estoy haciendo bien este move
    //close(bind_skt.getFd());
    acceptor.acceptClients(bind_skt);

    /* aca espero cin */

    /* aca cierro socket bind y join del aceptador  e imprimo */

}

Server::~Server() {}



