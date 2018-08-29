//
// Created by edoardo on 29/08/18.
//

#include "Date.h"

int Date::getGiorno() const {
    return giorno;
}

int Date::getMese() const {
    return mese;
}

int Date::getAnno() const {
    return anno;
}

void Date::setGiorno(int g) {
    giorno = g;
}

void Date::setMese(int m) {
    mese = m;
}

void Date::setAnno(int a) {
    anno = a;
}

Date::Date(int g, int m, int a) : giorno(g), mese(m), anno(a) {}
