
#ifndef TRANSAZIONIFINANZIARIE_INVESTIMENTO_H
#define TRANSAZIONIFINANZIARIE_INVESTIMENTO_H

#include <tgmath.h>
#include "DateTime.h"
#include "Utenza.h"
#include "Conto.h"

class Conto;

class Investimento {
public:
    Investimento(){}
    Investimento(std::string causale, float i, Conto* c, DateTime* d, bool comp);

    virtual ~Investimento();

    Investimento(const Investimento& that);
    Investimento& operator=(Investimento& that);
    bool operator==(const Investimento &i);
    bool operator!=(const Investimento &i);

    const std::string &getCausale() const;
    float getInvestimento() const;
    bool isCompleted() const;
    float getGuadagno() const;
    Conto *getConto() const;
    DateTime *getDataora() const;

    void setDataora(DateTime *dataora);
    void setCompleted(bool completed);

    void simulateInvestment(DateTime* now);


private:
    std::string causale;
    float investimento;
    Conto* conto;
    DateTime* dataora;
    bool completed;
    float guadagno;



};

#endif //TRANSAZIONIFINANZIARIE_INVESTIMENTO_H
