
#include "Investimento.h"

Investimento::Investimento(std::string causale, float i, std::shared_ptr<Conto> c, std::shared_ptr<DateTime> d, bool comp) {
    this->causale = causale;
    conto = c;
    investimento = i;
    guadagno = 0;
    completed = comp;
    if(d->IsValid())
        dataora = d;
}

Investimento::~Investimento() {
}


Investimento::Investimento(const Investimento &that) {
    causale = that.causale;
    investimento = that.investimento;
    conto = that.conto;
    dataora = that.dataora;
    completed = that.completed;
    guadagno = that.guadagno;
}

Investimento& Investimento::operator=(Investimento &that) {
    causale = that.causale;
    investimento = that.investimento;
    conto = that.conto;
    dataora = that.dataora;
    completed = that.completed;
    guadagno = that.guadagno;
    return *this;
}


bool Investimento::operator==(const Investimento &i) {
    if(conto == i.conto && investimento == i.investimento && dataora->operator==(*(i.dataora))
       && causale == i.causale)
        return true;
    return false;
}

bool Investimento::operator!=(const Investimento &i) {
    return !(*this == i);
}

void Investimento::simulateInvestment(std::shared_ptr<DateTime> now) {
    if (dataora != now && completed) {
        float g = (rand() % 10000) - 100;
        g = round(g * 100.0) / 100.0;
        guadagno += g;
        if(guadagno==0)
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

void Investimento::setDataora(std::shared_ptr<DateTime> dataora) {
    Investimento::dataora = dataora;
}

void Investimento::setCompleted(bool completed) {
    Investimento::completed = completed;
}

float Investimento::getGuadagno() const {
    return guadagno;
}

std::shared_ptr<Conto> Investimento::getConto() const {
    return conto;
}

std::shared_ptr<DateTime> Investimento::getDataora() const {
    return dataora;
}


