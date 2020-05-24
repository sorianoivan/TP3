#include "common_command_exception.h"

CommandException::CommandException(std::string &&error) {
    this->error = std::move(error);
}

const char *CommandException::what() const noexcept {
    return error.c_str();
}

CommandException::~CommandException() {}