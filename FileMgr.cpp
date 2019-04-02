//
// Created by edoardo on 22/03/19.
//

#include <cstring>
#include "FileMgr.h"
FileMgr::FileMgr(std::string filename, bool input) {
    openFile(filename, input);
}

void FileMgr::openFile(std::string filename, bool input){
    try {
        if (input)
            file.open(filename, std::ios::in);
        else
            file.open(filename, std::fstream::app);
        fileExists=true;
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati deell'account" << std::endl;
        fileExists = false;
    }
}

FileMgr::~FileMgr() {
    file.flush();
    file.close();
}

std::string FileMgr::read(std::string filename) {
    std::string s ="", tot ="";
    try {
        if(!file.is_open()) {
            openFile(filename, true);
        }
        if (file.good()) {
            while (!file.eof()) {
                getline(file, s);
                tot += s;
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati" << std::endl;
    }
    file.close();
    return tot;
}

std::string FileMgr::readFirstLine(std::string filename) {
    std::string s ="";
    try {
        if(!file.is_open()) {
            openFile(filename, true);
        }
        if (file.good()) {
            getline(file, s);
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati" << std::endl;
    }
    file.close();
    return s;
}

std::string FileMgr::readSecondLastLine(std::string filename) {
    std::string s ="";
    try {
        size_t count = countLines(filename);
        if(!file.is_open()) {
            openFile(filename, true);
        }
        if (file.good()) {
            for (size_t i = 0; i < count - 1; ++i) {
                getline(file, s);
            }
            getline(file, s);
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati" << std::endl;
    }
    file.close();
    return s;
}

size_t FileMgr::countLines(std::string filename) {
    size_t count = 0;
    try {
        if(!file.is_open()) {
            openFile(filename, true);
        }
        if (file.good()) {
            std::string line;
            while (getline(file, line)) {
                ++count;
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura dei dati" << std::endl;
    }
    file.close();
    return count;
}

void FileMgr::write(std::string filename,std::string str) {
    try {
        if(!file.is_open())
            openFile(filename, false);
        if (file.good()) {
            if (!file.eof()) {
                file << str;
                file << "\n";
                file.flush();
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nel salvataggio dei dati" << std::endl;
    }
    file.close();
}

void FileMgr::openNewFile(std::string filename, std::string str) {
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
    }
    file.close();
}

bool FileMgr::isFileExists() const {
    return fileExists;
}

