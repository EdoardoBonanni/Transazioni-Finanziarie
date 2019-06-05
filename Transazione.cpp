
#include "Transazione.h"


Transazione::Transazione(const typeTransaction t, float i, std::shared_ptr<Conto> m, std::shared_ptr<Conto> r, DateTime* d, bool comp) {
    type = t;
    switch(type){
        case typeTransaction::Deposito:
            invio = i;
            mittente = m;
            dataora = d;
            completed = comp;
            break;
        case typeTransaction::Prelievo:
            invio = i;
            mittente = m;
            dataora = d;
            completed = comp;
            break;
        case typeTransaction::Bonifico:
            invio = i;
            mittente = m;
            ricevitore = r;
            dataora = d;
            completed = comp;
            break;
    }
}

Transazione::~Transazione() {
    if(dataora!= nullptr)
        delete dataora;
}

Transazione::Transazione(const Transazione &that) {
    type = that.type;
    switch(type){
        case typeTransaction::Deposito:
            invio = that.invio;
            mittente = that.mittente;
            dataora = that.dataora;
            completed = that.completed;
            break;
        case typeTransaction::Prelievo:
            invio = that.invio;
            mittente = that.mittente;
            dataora = that.dataora;
            completed = that.completed;
            break;
        case typeTransaction::Bonifico:
            invio = that.invio;
            mittente = that.mittente;
            ricevitore = that.ricevitore;
            dataora = that.dataora;
            completed = that.completed;
            break;
    }
}

Transazione& Transazione::operator=(Transazione &that) {
    type = that.type;
    switch(type){
        case typeTransaction::Deposito:
            invio = that.invio;
            mittente = that.mittente;
            dataora = that.dataora;
            completed = that.completed;
            break;
        case typeTransaction::Prelievo:
            invio = that.invio;
            mittente = that.mittente;
            dataora = that.dataora;
            completed = that.completed;
            break;
        case typeTransaction::Bonifico:
            invio = that.invio;
            mittente = that.mittente;
            ricevitore = that.ricevitore;
            dataora = that.dataora;
            completed = that.completed;
            break;
    }
    return *this;
}

bool Transazione::operator==(const Transazione &t) {
    if(mittente == t.mittente && ricevitore == t.ricevitore
       && invio == t.invio && dataora == t.dataora
       && type == t.type && completed == t.completed)
        return true;
    return false;
}

bool Transazione::operator!=(const Transazione &t){
    return !(*this == t);
}

float Transazione::getInvio() const {
    return invio;
}

DateTime* Transazione::getDataora() const {
    return dataora;
}

bool Transazione::isCompleted() const {
    return completed;
}

void Transazione::setDataora(DateTime* dataora) {
    Transazione::dataora = dataora;
}

void Transazione::setCompleted(bool completed) {
    Transazione::completed = completed;
}

std::shared_ptr<Conto> Transazione::getMittente() const {
    return mittente;
}

std::shared_ptr<Conto> Transazione::getRicevitore() const {
    return ricevitore;
}

typeTransaction Transazione::getType() const {
    return type;
}
