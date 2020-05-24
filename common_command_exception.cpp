#include "common_command_exception.h"
#include <utility>

CommandException::CommandException(std::string &&error) {
    this->error = std::move(error);
}

const char *CommandException::what() const noexcept {
    return error.c_str();
}

CommandException::~CommandException() {}
