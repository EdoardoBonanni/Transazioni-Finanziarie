//
// Created by edoardo on 26/05/19.
//

#include "Deposito.h"

Deposito::Deposito(float deposito, Utenza *u, DateTime *d, bool comp)
    : Transazione(deposito, u, "Deposito", d, comp){
}
