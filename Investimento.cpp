
#include "Investimento.h"

Investimento::Investimento(std::string c, float i, Utenza *u, DateTime *d, bool comp) {
    causale = c;
    utenza = u;
    investimento = i;
    guadagno = 0;
    completed = comp;
    if(d->IsValid())
        dataora = d;
}

Investimento::~Investimento() {}


Investimento::Investimento(const Investimento &that) {
    causale = that.causale;
    investimento = that.investimento;
    utenza = that.utenza;
    dataora = that.dataora;
    completed = that.completed;
    guadagno = that.guadagno;
}

Investimento& Investimento::operator=(Investimento &that) {
    causale = that.causale;
    investimento = that.investimento;
    utenza = that.utenza;
    dataora = that.dataora;
    completed = that.completed;
    guadagno = that.guadagno;
    return *this;
}


bool Investimento::operator==(const Investimento &i) {
    if(utenza->operator==(*(i.utenza)) && investimento == i.investimento && dataora->operator==(*(i.dataora))
       && causale == i.causale)
        return true;
    return false;
}

bool Investimento::operator!=(const Investimento &i) {
    return !(*this == i);
}

void Investimento::simulateInvestment(DateTime *now) {
    if (dataora != now && completed) {
        float g = (rand() % 10000) - 100;
        g = round(g * 100.0) / 100.0;
        guadagno += g;
        if(guadagno=0)
            guadagno=1;
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


