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
                        const int gn, const int mn, const int an, bool isBissextile)
        :nome(n), cognome(c), sesso(s) {
    dataNascita = new Date(gn, mn, an, isBissextile);
    personaFisica = true;
}

Utenza::Utenza(const std::string n,const std::string i,const int nc,const std::string p) :
        nome(n), indirizzo(i), numeroCivico(nc), provincia(p){
    personaFisica = false;
}

Utenza::Utenza(const Utenza &that) {
    if(that.ispersonaFisica()){
        nome = that.nome;
        cognome = that.cognome;
        dataNascita->setGiorno(that.dataNascita->getGiorno());
        dataNascita->setMese(that.dataNascita->getMese());
        dataNascita->setAnno(that.dataNascita->getAnno());
    }else{
        nome = that.nome;
        indirizzo = that.indirizzo;
        numeroCivico = that.numeroCivico;
        provincia = that.provincia;
    }
}

Utenza& Utenza::operator=(Utenza &that) {
    if(that.ispersonaFisica()){
        if(dataNascita!= nullptr)
            delete dataNascita;
        nome = that.nome;
        cognome = that.cognome;
        dataNascita->setGiorno(that.dataNascita->getGiorno());
        dataNascita->setMese(that.dataNascita->getMese());
        dataNascita->setAnno(that.dataNascita->getAnno());
    }else{
        nome = that.nome;
        indirizzo = that.indirizzo;
        numeroCivico = that.numeroCivico;
        provincia = that.provincia;
    }
    return *this;
}

bool Utenza::operator==(const Utenza &u) {
    if(personaFisica==true && u.ispersonaFisica()==true) {
        if (nome == u.nome && cognome == u.cognome && dataNascita == u.dataNascita)
            return true;

    }
    if(personaFisica == false && u.ispersonaFisica()==false){
        if(nome == u.nome && indirizzo == u.indirizzo && numeroCivico == u.numeroCivico && provincia == u.provincia)
            return true;
    }
    return false;
}

bool Utenza::operator!=(const Utenza &u) {
    if(personaFisica==true && u.ispersonaFisica()==true) {
        if (nome == u.nome && cognome == u.cognome && dataNascita == u.dataNascita)
            return false;

    }
    if(personaFisica == false && u.ispersonaFisica()==false){
        if(nome == u.nome && indirizzo == u.indirizzo && numeroCivico == u.numeroCivico && provincia == u.provincia)
            return false;
    }
    return true;
}


bool Utenza::ispersonaFisica() const {
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
