//
// Created by edoardo on 23/05/19.
//

#ifndef TRANSAZIONIFINANZIARIE_TRANSAZIONE_H
#define TRANSAZIONIFINANZIARIE_TRANSAZIONE_H

#include "string"
#include "Date.h"
#include "Utenza.h"
#include "DateTime.h"

class Transazione {
public:
    Transazione();
    Transazione(const std::string o, float i, Utenza* m,  DateTime* d, bool comp) : operazione(o), invio(i),  mittente(m), dataora(d), completed(comp) {}
    Transazione(const std::string o, float i, Utenza* m,  Utenza* r, DateTime* d, bool comp) : operazione(o), invio(i),  mittente(m), ricevitore(r), dataora(d), completed(comp) {}

    virtual ~Transazione() {}

    bool operator==(const Transazione &t);
    bool operator!=(const Transazione &t);

    float getInvio() const;
    DateTime *getDataora() const;
    bool isCompleted() const;
    Utenza *getMittente() const;
    Utenza *getRicevitore() const;
    const std::string &getOperazione() const;

    void setDataora(DateTime *dataora);
    void setCompleted(bool completed);
    void setOperazione(const std::string &operazione);

private:
    std::string operazione;
    Utenza* mittente;
    Utenza* ricevitore;
    float invio;
    DateTime* dataora;
    bool completed;
};


#endif //TRANSAZIONIFINANZIARIE_TRANSAZIONE_H
