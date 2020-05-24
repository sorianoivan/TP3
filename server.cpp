#include "server.h"

#include <thread>
#include <algorithm>

Server::Server() {
    done_accepting = false;
    total_clients = 0;
    clients_removed = 0;
}

bool isClientDone(Thread* client) {
    if (client->isDone()){
        client->join();
        delete client;
        return true;
    }
    return false;
}

void Server::run(const char* port, std::string numbers) {//uso char* por el getaddrinfo
    FileReader file_reader(std::move(numbers));
    file_reader.processFile(secret_nums);

    bind_skt.setUpConnection(port);
    if (listen(bind_skt.getFd(), 10) == -1)
        throw SocketException("Error listen");

    std::thread th(&Server::getChar, this);

    acceptClients();

    for (auto & client : clients) {
        client->join();
        delete client;
    }
    th.join();
}

void Server::acceptClients() {
    unsigned int curr_num;
    while (!doneAccepting()) {
        Socket peer_skt;
        try {
            peer_skt = bind_skt.accept();
        } catch (std::exception& e) {}
        if (peer_skt.getFd() != -1) {
            curr_num = total_clients % secret_nums.size();
            clients.push_back(new Messenger(std::move(peer_skt), secret_nums[curr_num]));
            clients[total_clients - clients_removed]->start();
            total_clients++;
        }

        int clients_before = clients.size();
        clients.erase(std::remove_if(clients.begin(), clients.end(), isClientDone), clients.end());
        int clients_after = clients.size();
        clients_removed += clients_before - clients_after;
    }
}

Server::~Server() {}

void Server::getChar() {
    char cmd;
    do {
        std::cin >> cmd;
    }while (cmd != 'q');
    done_accepting = true;
    shutdown(bind_skt.getFd(), SHUT_RDWR);
    close(bind_skt.getFd());

}

bool Server::doneAccepting() {
    return done_accepting;
}



