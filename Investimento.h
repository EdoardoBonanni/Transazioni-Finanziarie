//
// Created by edoardo on 23/05/19.
//

#ifndef TRANSAZIONIFINANZIARIE_INVESTIMENTO_H
#define TRANSAZIONIFINANZIARIE_INVESTIMENTO_H

#include <tgmath.h>
#include "DateTime.h"
#include "Utenza.h"

class Investimento {
public:
    Investimento();
    Investimento(std::string c, float i, Utenza* u, DateTime* d, bool comp);

    bool operator==(const Investimento &i);

    const std::string &getCausale() const;
    float getInvestimento() const;
    bool isCompleted() const;
    float getGuadagno() const;
    Utenza *getUtenza() const;
    DateTime *getDataora() const;

    void setDataora(DateTime *dataora);
    void setCompleted(bool completed);

    void simulateInvestment(DateTime* now);


private:
    std::string causale;
    float investimento;
    Utenza* utenza;
    DateTime* dataora;
    bool completed;
    float guadagno;



};

#endif //TRANSAZIONIFINANZIARIE_INVESTIMENTO_H
