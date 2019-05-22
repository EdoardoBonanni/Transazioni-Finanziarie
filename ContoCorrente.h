//
// Created by edoardo on 29/08/18.
//


#ifndef TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H
#define TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H


#include "Utenza.h"

class ContoCorrente {
public:
    ContoCorrente(Utenza* t, float s=0);
    ~ContoCorrente();
    float getSaldo() const;
    bool InviaDenaro(float denaro, ContoCorrente* other);
    bool RiceviDenaro(float denaro, ContoCorrente* other);
    void DepositaDenaro(float denaro);
    bool PrelevaDenaro(float denaro);
private:
    float saldo;
    Utenza* titolare;
};


#endif //TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H
