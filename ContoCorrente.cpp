//
// Created by edoardo on 29/08/18.
//

#include "ContoCorrente.h"

ContoCorrente::ContoCorrente(Utenza* t, float s){
    titolare = t;
    saldo = s;
}

float ContoCorrente::getSaldo() const {
    return saldo;
}

bool ContoCorrente::InviaDenaro(float denaro, ContoCorrente* other) {
    if(denaro <= this->saldo) {
        other->saldo += denaro;
        this->saldo -= denaro;
        return true;
    }
    return false;
}

bool ContoCorrente::RiceviDenaro(float denaro, ContoCorrente *other) {
    if(denaro <= other->getSaldo()) {
        other->saldo -= other->getSaldo();
        this->saldo += denaro;
        return true;
    }
    return false;
}

void ContoCorrente::DepositaDenaro(float denaro) {
    saldo += denaro;
}

bool ContoCorrente::PrelevaDenaro(float denaro) {
    if (denaro > saldo)
        return false;
    saldo -= denaro;
    return true;
}