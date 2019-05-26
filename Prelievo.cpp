//
// Created by edoardo on 26/05/19.
//

#include "Prelievo.h"

Prelievo::Prelievo(float prelievo, Utenza *u, DateTime *d, bool comp)
    : Transazione(prelievo, u, "Prelievo", d, comp){
}
