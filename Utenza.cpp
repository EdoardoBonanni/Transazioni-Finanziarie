//
// Created by edoardo on 29/08/18.
//

#include "Utenza.h"

Utenza::Utenza(const std::string n, const std::string c, bool pf) : nome(n), cognome(c) {
    if(pf)
        personaFisica=true;
    else
        personaFisica=false;
}

Utenza::Utenza(const std::string n, const std::string c, char s,
                        const int gn, const int mn, const int an)
        :nome(n), cognome(c), sesso(s) {
    dataNascita = new Date(gn, mn, an);
    personaFisica = true;
}
/*Utenza::Utenza(const std::string n, const std::string c, char s,
               const int gn, const int mn, const int an,
               const std::string ln, const std::string pn, const std::string i,
               int nc, const std::string p) : nome(n), cognome(c),
                                                       sesso(s),
                                                       luogoNascita(ln),
                                                       provinciaNascita(pn),
                                                       indirizzo(i),
                                                       numeroCivico(nc),
                                                       provincia(p) {
    dataNascita = new Date(gn, mn, an);
    personaFisica = true;
}*/

Utenza::Utenza(const std::string n,const std::string i,const int nc,const std::string p) :
        nome(n), indirizzo(i), numeroCivico(nc), provincia(p){
    personaFisica = false;
}


bool Utenza::ispersonaFisica() {
    return personaFisica;
}

const std::string Utenza::getNome() const {
    return nome;
}

const std::string Utenza::getCognome() const {
    return cognome;
}

Utenza::~Utenza() {
    delete dataNascita;
}

char Utenza::getSesso() const {
    return sesso;
}

const std::string Utenza::getIndirizzo() const {
    return indirizzo;
}

int Utenza::getNumeroCivico() const {
    return numeroCivico;
}

const std::string Utenza::getProvincia() const {
    return provincia;
}
