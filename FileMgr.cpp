
#include <cstring>
#include "FileMgr.h"
FileMgr::FileMgr(std::string filename, bool input, bool &fatalError) {
    this->filename = filename;
    openFile(input, fatalError);
    file.close();
}

void FileMgr::openFile(bool input, bool &fatalError){
    try {
        if (input)
            file.open(filename, std::ios::in);
        else
            file.open(filename, std::fstream::app);
        if(file.is_open())
            fileExists=true;
        else
            fileExists=false;
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati dell'account" << std::endl;
        fileExists = false;
        fatalError = true;
    }
}

FileMgr::~FileMgr() {
    file.flush();
    file.close();
}

void FileMgr::deleteLine(std::string str, bool &fatalerror) {
    std::string line;
    std::ofstream temp;
    temp.open("temp.txt");
    try {
        if(!file.is_open()) {
            openFile(true, fatalerror);
        }
        if (file.good()) {
            while (!file.eof()) {
                getline(file, line);
                if (line != str)
                {
                    temp << line << std::endl;
                }
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati" << std::endl;
        fatalerror = true;
    }
    temp.close();
    file.close();
    const char* filenameModified = filename.c_str();
    remove(filenameModified);
    rename("temp.txt",filenameModified);
}

std::string FileMgr::read(bool &fatalError) {
    std::string s ="", tot ="";
    try {
        if(!file.is_open()) {
            openFile(true, fatalError);
        }
        if (file.good()) {
            while (!file.eof()) {
                getline(file, s);
                tot += s;
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati" << std::endl;
        fatalError = true;
    }
    file.close();
    return tot;
}

void FileMgr::write(std::string str, bool &fatalError) {
    try {
        if(!file.is_open())
            openFile(false, fatalError);
        if (file.good()) {
            if (!file.eof()) {
                file << str;
                file << "\n";
                file.flush();
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nel salvataggio dei dati" << std::endl;
        fatalError = true;
    }
    file.close();
}

void FileMgr::openNewFile(std::string str, bool &fatalError) {
    try {
        file.open(filename, std::fstream::out);
        if(file.good()) {
            if (!file.eof()) {
                file << str;
                file << "\n";
                file.flush();
            }
        }
        fileExists=true;
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella creazione del nuovo utente" << std::endl;
        fatalError = true;
    }
    file.close();
}

bool FileMgr::isFileExists() const {
    return fileExists;
}

const std::string &FileMgr::getFilename() const {
    return filename;
}

