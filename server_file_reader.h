#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "common_verifier.h"
#include "common_exception.h"

class FileReader {
private:
    std::ifstream file;
    Verifier verifier;
public:
    /* Constructor */
    explicit FileReader(std::string&& filename);
    /* Lee el archivo y mete los numeros leidos en el vector secret_nums.
     * Si alguno de los numeros no cumple con el formato o el archivo esta
     * vacio lanza una excepcion */
    void processFile(std::vector<int>& secret_nums);
    /* Sobrecarga del operador () */
    void operator()(std::vector<int>& secret_nums);
    /* Destructor */
    ~FileReader();
};


#endif //_FILEREADER_H
