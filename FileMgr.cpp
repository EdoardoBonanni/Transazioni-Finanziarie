//
// Created by edoardo on 22/03/19.
//

#include <cstring>
#include "FileMgr.h"
FileMgr::FileMgr(std::string filename, bool input) {
    fileExists=true;
    try {
        if (input)
            file.open(filename, std::fstream::in);
        else
            file.open(filename, std::fstream::app);
    }catch(std::ios_base::failure ex){
        std::cout << "Il file " << filename << " non può essere aperto o non esiste" << std::endl;
        fileExists = false;
    }
}

FileMgr::~FileMgr() {
    file.close();
}

std::string FileMgr::read(std::string filename) {
    std::string s ="", tot ="";
    try {
        if(file.is_open()) {
            while (!file.eof()) {
                getline(file, s);
                tot += s;
            }
        }else{
            file.open(filename, std::fstream::in);
            while (!file.eof()) {
                getline(file, s);
                tot += s;
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura del file" << std::endl;
    }
    delete file;
    return tot;
}

std::string FileMgr::readLine(std::string filename) {
    std::string s ="";
    try {
        if(file.is_open()) {
            /*while (!file.eof()) {
                getline(file, s);
                tot += s;
            }*/
        }else{
            file.open(filename, std::fstream::in);
            /*while (!file.eof()) {
                getline(file, s);
                tot += s;
            }*/
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella lettura del file" << std::endl;
    }
    delete file;
    return s;
}

void FileMgr::write(std::string filename,std::string str) {
    try {
        if(file.is_open()) {
            if (!file.eof()) {
                file << str;
                file << "\n";
                file.flush();
            }
        }else{
            file.open(filename, std::fstream::app);
            if (!file.eof()) {
                file << str;
                file << "\n";
                file.flush();
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella scrittura del file" << std::endl;
    }
}

void FileMgr::openNewFile(std::string filename, std::string str) {
    try {
        file.open(filename, std::fstream::out);
        if(file.is_open()) {
            if (!file.eof()) {
                file << str;
                file << "\n";
                file.flush();
            }
        }
    }catch(std::ios_base::failure ex){
        std::cout << "Errore nella creazione del nuovo file" << std::endl;
    }
    delete file;
}

bool FileMgr::isFileExists() const {
    return fileExists;
}

