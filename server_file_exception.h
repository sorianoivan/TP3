#ifndef _FILEEXCEPTION_H
#define _FILEEXCEPTION_H

#include <exception>
#include <string>

class FileException : public std::exception {
private:
    std::string error;
public:
    explicit FileException(std::string&& error);
    const char* what() const noexcept;
    ~FileException();
};


#endif //_FILEEXCEPTION_H
