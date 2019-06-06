//
// Created by edoardo on 29/08/18.
//


#ifndef TRANSAZIONIFINANZIARIE_UTENZA_H
#define TRANSAZIONIFINANZIARIE_UTENZA_H

#include <memory>
#include "string"
#include "Date.h"

class Utenza {
public:
    Utenza();
    Utenza(const std::string n, const std::string c, bool pf);
    Utenza(const std::string n, const std::string c, char s,
                    const int gn, const int mn, const int an, bool isBissextile);
    Utenza(const std::string n, const std::string c, char s,
           const int gn, const int mn, const int an, bool isBissextile,
           const std::string i,const int nc, const std::string p);
    Utenza(const std::string n,const std::string i,const int nc, const std::string p);


    Utenza(const Utenza& that);
    Utenza& operator=(Utenza& that);
    bool operator==(const Utenza &u);
    bool operator!=(const Utenza &u);

    ~Utenza();

    bool ispersonaFisica() const;
    const std::string getNome() const;
    const std::string getCognome() const;
    char getSesso() const;
    const std::string getIndirizzo() const;
    int getNumeroCivico() const;
    const std::string getProvincia() const;
    Date* getDataNascita() const;
    bool isPersonaFisica() const;

    void setNome(const std::string &nome);
    void setCognome(const std::string &cognome);
    void setSesso(char sesso);
    void setIndirizzo(const std::string &indirizzo);
    void setNumeroCivico(int numeroCivico);
    void setDataNascita(Date* dataNascita);
    void setProvincia(const std::string &provincia);

private:
    std::string nome;
    std::string cognome;
    char sesso;
    Date* dataNascita;
    std::string indirizzo;
    int numeroCivico;
    std::string provincia;
    bool personaFisica;
};


#endif //TRANSAZIONIFINANZIARIE_UTENZA_H
