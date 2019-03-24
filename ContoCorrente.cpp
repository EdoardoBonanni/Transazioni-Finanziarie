//
// Created by edoardo on 29/08/18.
//

#include "ContoCorrente.h"

ContoCorrente::ContoCorrente(Utenza* t, int s) : titolare(t) {
    saldo = 0;
    if(!t->ispersonaFisica())
        saldo = s;
}

float ContoCorrente::getSaldo() const {
    return saldo;
}

Utenza* ContoCorrente::getTitolare() const {
    return titolare;
}

bool ContoCorrente::InviaDenaro(float denaro, ContoCorrente* other) {
    if(denaro <= saldo) {
        other->saldo += denaro;
        saldo -= denaro;
        return true;
    }
    return false;
}

bool ContoCorrente::RiceviDenaro(float denaro, ContoCorrente *other) {
    if(denaro <= other->getSaldo()) {
        other->saldo -= other->getSaldo();
        saldo += denaro;
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