#ifndef _COMMONSOCKETEXCEPTION_H
#define _COMMONSOCKETEXCEPTION_H

#include <exception>
#include <string>

class SocketException : public std::exception {
private:
    std::string error;

public:
    explicit SocketException(std::string&& error);
    const char* what() const noexcept ;
    ~SocketException();

};


#endif //_COMMONSOCKETEXCEPTION_H
