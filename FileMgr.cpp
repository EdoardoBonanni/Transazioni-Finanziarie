//
// Created by edoardo on 22/03/19.
//

#include "FileMgr.h"
FileMgr::FileMgr(const char *filename, bool input) {
    if(input)
        file_handle = std::fopen(filename, "r+");
    else
        file_handle = std::fopen(filename, "w+");
    if(!file_handle)
        throw std::runtime_error("file open failure");
}

FileMgr::~FileMgr() {
    if(std::fclose(file_handle))
        fflush(file_handle);


}

const char* FileMgr::read() {
    char mybuffer[200];
    char* result;
    while(result != NULL){
        result = std::fgets(mybuffer, 200, file_handle);
        //stampa riga
    }
}

void FileMgr::write(const char *str) {
    if(EOF == std::fputs(str, file_handle))
        throw std::runtime_error("file write failure");

}