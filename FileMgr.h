
#ifndef TRANSAZIONIFINANZIARIE_FILEMGR_H
#define TRANSAZIONIFINANZIARIE_FILEMGR_H

#include<fstream>
#include<iostream>
#include<stdexcept>
#include "Transazione.h"

class FileMgr{
public:
    FileMgr(std::string filename, bool input, bool &fatalError);
    ~FileMgr();

    void write(std::string str, bool &fatalError);
    std::string read(bool &fatalError);
    void openNewFile(std::string str, bool &fatalError);
    void deleteLine(std::string str, bool &fatalerror);

    const std::string &getFilename() const;
    bool isFileExists() const;

private:
    std::fstream file;
    std::string filename;
    bool fileExists;

    void openFile(bool input, bool &fatalError);
};


#endif //TRANSAZIONIFINANZIARIE_FILEMGR_H
