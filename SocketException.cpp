#include "SocketException.h"

SocketException::SocketException(std::string &&error) {
    this->error = std::move(error);
}

const char *SocketException::what() const noexcept {
    return error.c_str();
}

SocketException::~SocketException() {}


