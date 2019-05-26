//
// Created by edoardo on 23/05/19.
//

#ifndef TRANSAZIONIFINANZIARIE_DEPOSITO_H
#define TRANSAZIONIFINANZIARIE_DEPOSITO_H

#include "ContoCorrente.h"

class Deposito : public Transazione {
public:
    Deposito(float deposito, Utenza* u, DateTime* d, bool comp);
};

#endif //TRANSAZIONIFINANZIARIE_DEPOSITO_H
