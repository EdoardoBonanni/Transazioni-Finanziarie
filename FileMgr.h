//
// Created by edoardo on 22/03/19.
//

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

    void write(std::string filename, std::string str, bool &fatalError);
    std::string read(std::string filename, bool &fatalError);
    void openNewFile(std::string filename, std::string str, bool &fatalError);
    bool isFileExists() const;
    void deleteLine(std::string filename, std::string str, bool &fatalerror);

private:
    std::fstream file;
    bool fileExists;

    void openFile(std::string filename, bool input, bool &fatalError);
    size_t countLines(std::string filename, bool &fatalError);
};


#endif //TRANSAZIONIFINANZIARIE_FILEMGR_H
