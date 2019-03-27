//
// Created by edoardo on 22/03/19.
//

#ifndef TRANSAZIONIFINANZIARIE_FILEMGR_H
#define TRANSAZIONIFINANZIARIE_FILEMGR_H

#include<fstream>
#include<iostream>
#include<stdexcept>
class FileMgr{
public:
    FileMgr(std::string filename, bool input);
    ~FileMgr();
    void write(std::string filename, std::string str);
    std::string read(std::string filename);
    std::string readLine(std::string filename);
    void openNewFile(std::string filename, std::string str);
    bool isFileExists() const;
private:
    std::fstream file;
    bool fileExists;
};


#endif //TRANSAZIONIFINANZIARIE_FILEMGR_H
