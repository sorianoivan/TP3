#include "server_acceptor.h"

Acceptor::Acceptor(std::vector<int>&& secret_nums) {
    this->secret_nums = std::move(secret_nums);
}

void Acceptor::acceptClients(Socket& skt) {
    peer_skt = skt.accept();
    if (peer_skt.getFd() != -1) {
        Messenger messenger(std::move(peer_skt), secret_nums[0]);
        messenger.run();
    }
}

Acceptor::~Acceptor() {}

