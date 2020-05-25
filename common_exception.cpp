#include "common_exception.h"

#include <utility>

CommonException::CommonException(std::string&& error) {
    this->error = std::move(error);
}

const char *CommonException::what() const noexcept {
    return error.c_str();
}

CommonException::~CommonException() {}


