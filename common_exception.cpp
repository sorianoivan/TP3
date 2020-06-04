#include "common_exception.h"

CommonException::CommonException(std::string&& error) {
    this->error = error;
}

const char *CommonException::what() const noexcept {
    return error.c_str();
}

CommonException::~CommonException() {}


