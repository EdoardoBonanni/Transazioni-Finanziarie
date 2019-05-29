//
// Created by edoardo on 23/05/19.
//

#include "DateTime.h"

bool DateTime::checkOra(int o, int m, int s) {
    if(o>=0 && o<=24 && m>0 && m<=60 && s>=0 && s<=60)
        return true;
    return false;
}
bool DateTime::checkDateTime(int o, int min, int s, int g, int mes, int a, bool isBissextile) {
    if(checkOra(o, min, s) && checkData(g, mes, a, isBissextile)){
        return true;
    }
    return  false;
}

DateTime::DateTime(int g, int mes, int a, int o, int min, int s, bool isBissextile){
    if(checkDateTime(o, min, s, g, mes, a, isBissextile)) {
        giorno = g;
        mese = mes;
        anno = a;
        ora=o;
        minuto=min;
        secondo=s;
        isValid = true;
    }else{
            isValid=false;
    }
}

DateTime::DateTime(const DateTime &that) {
    if(that.isValid) {
        secondo = that.secondo;
        minuto = that.minuto;
        ora = that.ora;
        giorno = that.giorno;
        mese = that.mese;
        anno = that.anno;
    }
    isValid = that.isValid;
}

DateTime& DateTime::operator=(DateTime &that) {
    if(that.isValid) {
        secondo = that.secondo;
        minuto = that.minuto;
        ora = that.ora;
        giorno = that.giorno;
        mese = that.mese;
        anno = that.anno;
    }
    isValid = that.isValid;
    return *this;
}

bool DateTime::operator==(const DateTime &dt) {
    if(giorno == dt.giorno && mese == dt.mese && anno == dt.anno
       && secondo == dt.secondo && minuto == dt.minuto && ora == dt.ora && isValid)
        return true;
    return false;
}

bool DateTime::operator!=(const DateTime &dt) {
    return !(*this == dt);
}

int DateTime::getOra() const {
    return ora;
}

int DateTime::getMinuto() const {
    return minuto;
}

int DateTime::getSecondo() const {
    return secondo;
}

void DateTime::setOra(const int o, bool isBissextile) {
    if(checkDateTime(o, minuto, secondo, giorno, mese, anno, isBissextile))
        this->ora = o;
}

void DateTime::setMinuto(const int min, bool isBissextile) {
    if(checkDateTime(ora, min, secondo, giorno, mese, anno, isBissextile))
        this->minuto = min;
}

void DateTime::setSecondo(const int s, bool isBissextile) {
    if(checkDateTime(ora, minuto, s, giorno, mese, anno, isBissextile))
        this->secondo = s;
}

void DateTime::setAnno(const int a, bool isBissextile){
    if(checkDateTime(ora, minuto, secondo, giorno, mese, a, isBissextile))
        this->anno = a;
}

void DateTime::setMese(const int mes, bool isBissextile){
    if(checkDateTime(ora, minuto, secondo, giorno, mes, anno, isBissextile))
        this->mese = mes;
}

void DateTime::setGiorno(const int g, bool isBissextile){
    if(checkDateTime(ora, minuto, secondo, g, mese, anno, isBissextile))
        this->giorno = g;
}

DateTime::~DateTime() {}
