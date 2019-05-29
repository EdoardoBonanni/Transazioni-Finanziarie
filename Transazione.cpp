//
// Created by edoardo on 23/05/19.
//

#include "Transazione.h"

bool Transazione::operator==(const Transazione &t) {
    if(mittente == t.mittente && ricevitore == t.ricevitore
       && invio == t.invio && dataora == t.dataora
       && operazione == t.operazione && completed == t.completed)
        return true;
    return false;
}

bool Transazione::operator!=(const Transazione &t){
    return !(*this == t);
}

float Transazione::getInvio() const {
    return invio;
}

DateTime *Transazione::getDataora() const {
    return dataora;
}

bool Transazione::isCompleted() const {
    return completed;
}

void Transazione::setDataora(DateTime *dataora) {
    Transazione::dataora = dataora;
}

void Transazione::setCompleted(bool completed) {
    Transazione::completed = completed;
}

Utenza *Transazione::getMittente() const {
    return mittente;
}

Utenza *Transazione::getRicevitore() const {
    return ricevitore;
}

void Transazione::setOperazione(const std::string &operazione) {
    Transazione::operazione = operazione;
}

const std::string &Transazione::getOperazione() const {
    return operazione;
}
