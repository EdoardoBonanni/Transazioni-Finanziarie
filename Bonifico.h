//
// Created by edoardo on 23/05/19.
//

#ifndef TRANSAZIONIFINANZIARIE_BONIFICO_H
#define TRANSAZIONIFINANZIARIE_BONIFICO_H

#include "Transazione.h"
#include "ContoCorrente.h"

class Bonifico : public Transazione {
public:
    Bonifico(float bonifico, Utenza* me, Utenza* other, DateTime* d, bool comp);
};

#endif //TRANSAZIONIFINANZIARIE_BONIFICO_H
