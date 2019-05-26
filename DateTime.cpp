//
// Created by edoardo on 23/05/19.
//

#include "DateTime.h"

DateTime::DateTime(int g, int mes, int a, int o, int min, int s, bool isBissextile){
    if(checkOra(o, min, s) && checkData(g, mes, a, isBissextile)) {
        secondo = s;
        minuto = min;
        ora = o;
        ora=o;
        minuto=min;
        secondo=s;
    }
}

DateTime& DateTime::operator=(DateTime &that) {
    secondo = that.secondo;
    minuto = that.minuto;
    ora = that.ora;
    giorno = that.giorno;
    mese = that.mese;
    anno = that.anno;
    return *this;
}

bool DateTime::operator==(const DateTime &dt) {
    if(giorno == dt.giorno && mese == dt.mese && anno == dt.anno
       && secondo == dt.secondo && minuto == dt.minuto && ora == dt.ora)
        return true;
    return false;
}

bool DateTime::operator!=(const DateTime &dt) {
    return !(*this == dt);
}

bool DateTime::checkOra(int o, int m, int s) {
    if(o>=0 && o<=60 && m>0 && m<=60 && s>=0 && s<=60)
        return true;
    return false;
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

void DateTime::setOra(int ora) {
    DateTime::ora = ora;
}

void DateTime::setMinuto(int minuto) {
    DateTime::minuto = minuto;
}

void DateTime::setSecondo(int secondo) {
    DateTime::secondo = secondo;
}

DateTime::~DateTime() {}
