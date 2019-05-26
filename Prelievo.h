//
// Created by edoardo on 23/05/19.
//

#ifndef TRANSAZIONIFINANZIARIE_PRELIEVO_H
#define TRANSAZIONIFINANZIARIE_PRELIEVO_H


#include "Transazione.h"
#include "ContoCorrente.h"

class Prelievo : public Transazione {
public:
    Prelievo(float prelievo, Utenza* u, DateTime* d, bool comp);
};


#endif //TRANSAZIONIFINANZIARIE_PRELIEVO_H
