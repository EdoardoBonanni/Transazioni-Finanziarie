//
// Created by edoardo on 26/05/19.
//

#include "Investimento.h"

Investimento::Investimento(std::string c, float i, Utenza *u, DateTime *d, bool comp) {
    causale = c;
    utenza = u;
    investimento = i;
    guadagno = 0;
    completed = comp;
    dataora = d;
}

bool Investimento::operator==(const Investimento &i) {
    if(utenza ==  i.utenza && investimento == i.investimento && dataora == i.dataora
       && causale == i.causale)
        return true;
    return false;
}


void Investimento::simulateInvestment(DateTime *now) {
    if (dataora != now) {
        float g = (rand() % 10000) - 100;
        g = round(g * 100.0) / 100.0;
        guadagno += g;
    }
}

const std::string &Investimento::getCausale() const {
    return causale;
}

float Investimento::getInvestimento() const {
    return investimento;
}

bool Investimento::isCompleted() const {
    return completed;
}

void Investimento::setDataora(DateTime *dataora) {
    Investimento::dataora = dataora;
}

void Investimento::setCompleted(bool completed) {
    Investimento::completed = completed;
}

float Investimento::getGuadagno() const {
    return guadagno;
}

Utenza *Investimento::getUtenza() const {
    return utenza;
}

DateTime *Investimento::getDataora() const {
    return dataora;
}

