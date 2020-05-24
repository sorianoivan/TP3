#include "server_file_exception.h"

#include <utility>

FileException::FileException(std::string&& error) {
    this->error = std::move(error);
}

const char *FileException::what() const noexcept {
    return error.c_str();
}

FileException::~FileException() {}


