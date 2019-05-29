//
// Created by edoardo on 29/08/18.
//

#include "Date.h"

Date::Date(int g, int m, int a, bool isBissextile) {
    if(checkData(g, m, a, isBissextile)){
        giorno = g;
        mese = m;
        anno = a;
        isValid=true;
    }else{
        isValid=false;
    }
}

Date::~Date() {}

bool Date::checkData(int g, int m, int a, bool isBissextile) {
    if(a>1900 && a<2020){
        if((m==4 || m==6 || m==9 || m==11) && g<=30 && g>0)
            return true;
        if(m==2 && g<=29 && g>0 && isBissextile)
            return true;
        if(m==2 && g<=28 && g>0)
            return true;
        if(g>0 && g<=31 && (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12))
            return  true;
    }
    return false;
}

Date::Date(const Date &that) {
    if(that.isValid) {
        giorno = that.giorno;
        mese = that.mese;
        anno = that.anno;
    }
    isValid = that.isValid;
}

Date& Date::operator=(Date &that) {
    if(that.isValid) {
        giorno = that.giorno;
        mese = that.mese;
        anno = that.anno;
    }
    isValid = that.isValid;
    return *this;
}

bool Date::operator==(const Date &d) {
    if(giorno == d.giorno && mese == d.mese && anno == d.anno && isValid)
        return true;
    else
        return  false;
}

bool Date::operator!=(const Date &d) {
    return !(*this == d);;
}

int Date::getGiorno() const {
    return giorno;
}

int Date::getMese() const {
    return mese;
}

int Date::getAnno() const {
    return anno;
}

void Date::setGiorno(const int g, bool isBissextile) {
    if(checkData(g, mese, anno, isBissextile))
        giorno = g;
}

void Date::setMese(const int m, bool isBissextile) {
    if(checkData(giorno, m, anno, isBissextile))
        mese = m;
}

void Date::setAnno(const int a, bool isBissextile) {
    if(checkData(giorno, mese, a, isBissextile))
        anno = a;
}

bool Date::IsValid() const {
    return isValid;
}

