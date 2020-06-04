#include "common_socket_exception.h"

SocketException::SocketException(std::string &&error) {
    this->error = error;
}

const char *SocketException::what() const noexcept {
    return error.c_str();
}

SocketException::~SocketException() {}


