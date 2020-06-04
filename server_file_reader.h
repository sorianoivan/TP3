#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <vector>
#include <fstream>
#include <string>

#include "common_verifier.h"
#include "common_exception.h"

class FileReader {
private:
    std::ifstream file;
    Verifier verifier;
public:
    /* Constructor */
    explicit FileReader(std::string&& filename);
    /* Sobrecarga del operador () */
    void operator()(std::vector<unsigned int>& secret_nums);
    /* Destructor */
    ~FileReader();

private:
    void processFile(std::vector<unsigned int>& secret_nums);
};


#endif //_FILEREADER_H
