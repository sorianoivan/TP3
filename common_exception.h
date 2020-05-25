#ifndef _FILEEXCEPTION_H
#define _FILEEXCEPTION_H

#include <exception>
#include <string>

class CommonException : public std::exception {
private:
    std::string error;

public:
    explicit CommonException(std::string&& error);
    const char* what() const noexcept;
    ~CommonException();
};

#endif //_FILEEXCEPTION_H
