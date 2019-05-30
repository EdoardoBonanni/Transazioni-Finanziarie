
#ifndef TRANSAZIONIFINANZIARIE_TRANSAZIONE_H
#define TRANSAZIONIFINANZIARIE_TRANSAZIONE_H

#include "string"
#include "Date.h"
#include "DateTime.h"
#include "Conto.h"

class Conto;

enum class typeTransaction {
    Bonifico, Deposito, Prelievo
};

class Transazione {
public:
    Transazione(){}
    Transazione(const typeTransaction t, float i, Conto* m,  Conto* r, DateTime* d, bool comp);

    virtual ~Transazione();

    Transazione(const Transazione& that);
    Transazione& operator=(Transazione& that);
    bool operator==(const Transazione &t);
    bool operator!=(const Transazione &t);

    float getInvio() const;
    DateTime *getDataora() const;
    bool isCompleted() const;
    Conto* getMittente() const;
    Conto* getRicevitore() const;
    typeTransaction getType() const;

    void setDataora(DateTime *dataora);
    void setCompleted(bool completed);

private:
    typeTransaction type;
    Conto* mittente;
    Conto* ricevitore;
    float invio;
    DateTime* dataora;
    bool completed;
};


#endif //TRANSAZIONIFINANZIARIE_TRANSAZIONE_H
