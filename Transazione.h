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
    Transazione(float i, Utenza* m,  const std::string o, DateTime* d, bool comp) : invio(i),  mittente(m), operazione(o), completed(comp) {
        if(completed)
            dataora = d;
    }
    Transazione(float i, Utenza* m,  Utenza* r, const std::string o, DateTime* d, bool comp) : invio(i),  mittente(m), ricevitore(r), operazione(o), completed(comp) {
        if(completed)
            dataora=d;
    }

    virtual ~Transazione() {}

    bool operator==(const Transazione &t);
    bool operator!=(const Transazione &t);

    float getInvio() const;
    DateTime *getDataora() const;
    bool isCompleted() const;
    Utenza *getMittente() const;
    Utenza *getRicevitore() const;

    void setDataora(DateTime *dataora);
    void setCompleted(bool completed);

private:
    Utenza* mittente;
    Utenza* ricevitore;
    float invio;
    std::string operazione;
    DateTime* dataora;
    bool completed;
};


#endif //TRANSAZIONIFINANZIARIE_TRANSAZIONE_H
