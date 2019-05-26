//
// Created by edoardo on 26/05/19.
//

#include "Bonifico.h"

Bonifico::Bonifico(float bonifico, Utenza *me, Utenza *other, DateTime *d, bool comp)
 : Transazione(bonifico, me, other, "Bonifico", d, comp){}
