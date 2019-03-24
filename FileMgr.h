//
// Created by edoardo on 22/03/19.
//

#ifndef TRANSAZIONIFINANZIARIE_FILEMGR_H
#define TRANSAZIONIFINANZIARIE_FILEMGR_H

#include<cstdio>
#include<stdexcept>
class FileMgr {
public:
    FileMgr(const char* filename, bool input);
    ~FileMgr();
    void write(const char* str);
    const char* read();
private:
    std::FILE* file_handle;
    FileMgr(const FileMgr &);
    FileMgr &  operator==(const FileMgr &);
};


#endif //TRANSAZIONIFINANZIARIE_FILEMGR_H
