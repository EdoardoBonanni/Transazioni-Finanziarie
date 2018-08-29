//
// Created by edoardo on 29/08/18.
//

#ifndef TRANSAZIONIFINANZIARIE_UTENZA_H
#define TRANSAZIONIFINANZIARIE_UTENZA_H

#include "string"
#include "Date.h"

class Utenza {

private:
public:
    Utenza(const std::string n, const std::string c, char s,
                    const int gn, const int mn, const int an);
    Utenza(const std::string n, const std::string c, char s,
           const int gn, const int mn, const int an,
           const std::string ln, const std::string pn, const std::string i,
           int nc, const std::string p);
    Utenza(const std::string n,const std::string i,const int nc, const std::string p);
    bool ispersonaFisica();
    const std::string getNome() const;

private:
    std::string nome;
    std::string cognome;
    char sesso;
    Date* dataNascita;
    std::string luogoNascita;
    std::string provinciaNascita;
    std::string indirizzo;
    int numeroCivico;
    std::string provincia;
    bool personaFisica;
};


#endif //TRANSAZIONIFINANZIARIE_UTENZA_H
