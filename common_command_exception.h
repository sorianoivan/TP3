#ifndef _COMMANDEXCEPTION_H
#define _COMMANDEXCEPTION_H

#include <exception>
#include <string>
class CommandException : public std::exception {
private:
    std::string error;
public:
    explicit CommandException(std::string&& error);
    const char* what() const noexcept;
    ~CommandException();
};


#endif //_COMMANDEXCEPTION_H
