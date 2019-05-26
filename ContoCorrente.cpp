//
// Created by edoardo on 29/08/18.
//


#include <algorithm>
#include <typeinfo>
#include <vector>
#include "ContoCorrente.h"
#include "Deposito.h"
#include "Bonifico.h"
#include "Prelievo.h"


ContoCorrente::ContoCorrente(Utenza* t, float s, float si){
    investimenti = std::list<Investimento*>();
    transazioni = std::list<Transazione*>();
    titolare = t;
    saldo = s;
    soldiInvestiti = si;
}

ContoCorrente::~ContoCorrente() {
    if(titolare != nullptr) {
        delete titolare;
    }
    investimenti.clear();
    transazioni.clear();

}

ContoCorrente::ContoCorrente(const ContoCorrente &that) : saldo(that.saldo), soldiInvestiti(that.soldiInvestiti) {
    investimenti = that.investimenti;
    transazioni = that.transazioni;
}

ContoCorrente& ContoCorrente::operator=(ContoCorrente &that) {
    investimenti.clear();
    transazioni.clear();
    investimenti = that.investimenti;
    transazioni = that.transazioni;
    saldo = that.saldo;
    soldiInvestiti = that.soldiInvestiti;
    return *this;
}

float ContoCorrente::getSaldo() const {
    return saldo;
}


void ContoCorrente::setSaldo(float saldo) {
    ContoCorrente::saldo = saldo;
}


float ContoCorrente::getSoldiInvestiti() const {
    return soldiInvestiti;
}

void ContoCorrente::setSoldiInvestiti(float soldiInvestiti) {
    ContoCorrente::soldiInvestiti = soldiInvestiti;
}

Utenza* ContoCorrente::getUtenza() const {
    return titolare;
}

bool ContoCorrente::addTransazione(Transazione *t, FileMgr* fm, std::string filename, bool& fatalerror) {
    if(t->getInvio() <= saldo) {
        transazioni.push_back(t);
        addTransactionToFile(t, fm, filename, fatalerror);
        if(typeid(t) == typeid(Deposito))
            saldo += t->getInvio();
        if(typeid(t) == typeid(Prelievo))
            saldo -= t->getInvio();
        if(typeid(t) == typeid(Bonifico)) {
            if (t->getMittente() == titolare)
                saldo -= t->getInvio();
            else
                saldo += t->getInvio();
        }
        t->setCompleted(true);
        return true;
    }
    return false;
}

bool ContoCorrente::addInvestimento(Investimento *i, FileMgr* fm, std::string filename, bool& fatalerror) {
    if(i->getInvestimento() <= saldo) {
        investimenti.push_back(i);
        addInvestmentToFile(i, fm, filename, fatalerror);
        saldo -= i->getInvestimento();
        soldiInvestiti += i->getInvestimento();
        i->setCompleted(true);
        return true;
    }
    return false;
}

bool ContoCorrente::removeInvestimento(Investimento *i, DateTime* now, FileMgr* fm, std::string filename, bool& fatalerror) {
    int pos=0;
    std::list<Investimento*>::iterator iter;
    for(iter=investimenti.begin(); iter != investimenti.end(); ++iter){
        if(*iter == i){
            break;
        }
        pos++;
    }
    if(iter != investimenti.end()) {
        i->simulateInvestment(now);
        investimenti.remove(i);
        removeInvestmentFromFile(i, fm, filename, fatalerror);
        saldo += i->getInvestimento() + i->getGuadagno();
        soldiInvestiti -= i->getInvestimento();
        return true;
    }
    return false;
}

bool ContoCorrente::getTransazioni(FileMgr* fm, std::string filename, bool &fatalerror) {
    std::string str = fm->read(filename, fatalerror);
    if(!fatalerror) {
        std::vector<std::string> container;
        std::stringstream ss(str);
        char delim1 = ' ', delim2 = ':';
        float denaro;
        Utenza *u1;
        Utenza *u2;
        DateTime* dt;
        Bonifico* b;
        Prelievo* p;
        Deposito* dep;
        bool pf1 = false, pf2 = false, isBissexstile = false;
        int giorno, mese, anno, ora, minuto, secondo;
        std::string token, type, nome1, cognome1, nome2, cognome2;
        transazioni.clear();
        while (std::getline(ss, token, delim1) || std::getline(ss, token, delim2)) {
            container.push_back(token);
            type = container[0];
            if (type == "Bonifico") {
                //formato linea file
                //Bonifico da nome1 cognome1 a nome2 cognome 2 di denaro g:m:a o:m:s
                nome1 = container[3];
                cognome1 = container[4];
                nome2 = container[6];
                cognome2 = container[7];
                denaro = stof(container[9]);
                giorno = stoi(container[10]);
                mese = stoi(container[11]);
                anno = stoi(container[12]);
                ora = stoi(container[13]);
                minuto = stoi(container[14]);
                secondo = stoi(container[15]);
                if (cognome1 != "X")
                    pf1 = true;
                u1 = new Utenza(nome1, cognome1, pf1);
                if (cognome2 != "X")
                    pf2 = true;
                u2 = new Utenza(nome2, cognome2, pf2);
                if(mese==2 && giorno==29)
                    isBissexstile=true;
                dt = new DateTime(giorno, mese, anno, ora, minuto, secondo, isBissexstile);
                b = new Bonifico(denaro, u1, u2, dt, true);
                saldo -= denaro;
                transazioni.push_back(b);
            } else {
                //formato linea file
                //Prelievo nome1 cognome1 di denaro g:m:a o:m:s
                //Deposito nome1 cognome1 di denaro g:m:a o:m:s
                nome1 = container[2];
                cognome1 = container[3];
                denaro = stof(container[5]);
                giorno = stoi(container[6]);
                mese = stoi(container[7]);
                anno = stoi(container[8]);
                ora = stoi(container[9]);
                minuto = stoi(container[10]);
                secondo = stoi(container[11]);
                if (cognome1 != "X")
                    pf1 = true;
                u1 = new Utenza(nome1, cognome1, pf1);
                if(mese==2 && giorno==29)
                    isBissexstile=true;
                dt = new DateTime(giorno, mese, anno, ora, minuto, secondo, isBissexstile);
                if(type=="Prelievo") {
                    p = new Prelievo(denaro, u1, dt, true);
                    saldo -= denaro;
                    transazioni.push_back(p);
                }
                if(type=="Deposito") {
                    dep = new Deposito(denaro, u1, dt, true);
                    saldo += denaro;
                    transazioni.push_back(dep);
                }
            }
        }

        return true;
    }
    return false;
}

bool ContoCorrente::getInvestimenti(FileMgr *fm, std::string filename, bool &fatalerror) {
    std::string str = fm->read(filename, fatalerror);
    if(!fatalerror) {
        std::vector<std::string> container;
        std::stringstream ss(str);
        char delim1 = ' ', delim2 = ':';
        float denaro;
        Utenza *u1;
        DateTime* dt;
        Investimento* i;
        bool pf1 = false, isBissexstile = false;
        int giorno, mese, anno, ora, minuto, secondo;
        std::string token, causale, type, nome1, cognome1;
        investimenti.clear();
        while (std::getline(ss, token, delim1) || std::getline(ss, token, delim2)) {
            container.push_back(token);
            type = container[0];
            if (type == "Investimento") {
                //formato linea file
                //Investimento nome cognome di denaro per causale g:m:a o:m:s
                nome1 = container[2];
                cognome1 = container[3];
                denaro = stof(container[5]);
                causale = container[7];
                giorno = stoi(container[8]);
                mese = stoi(container[9]);
                anno = stoi(container[10]);
                ora = stoi(container[11]);
                minuto = stoi(container[12]);
                secondo = stoi(container[13]);
                if (cognome1 != "X")
                    pf1 = true;
                u1 = new Utenza(nome1, cognome1, pf1);
                if(mese==2 && giorno==29)
                    isBissexstile=true;
                dt = new DateTime(giorno, mese, anno, ora, minuto, secondo, isBissexstile);
                i = new Investimento("Investimento", denaro, u1, dt, true);
                saldo -= denaro;
                soldiInvestiti += denaro;
            }
        }
        return true;
    }
    return false;
}

bool ContoCorrente::addTransactionToFile(Transazione *t, FileMgr *fm, std::string filename, bool &fatalerror) {
    std::string str;
    if(typeid(t) == typeid(Bonifico)) {
        //formato linea file
        //Bonifico da nome1 cognome1 a nome2 cognome 2 di denaro g:m:a o:m:s
        str = "Bonifico da " + t->getMittente()->getNome() + " ";
        if(t->getMittente()->ispersonaFisica())
            str += t->getMittente()->getCognome() + " a ";
        else
            str += "X a ";
        str += t->getRicevitore()->getNome() + " ";
        if(t->getRicevitore()->ispersonaFisica())
            str+= t->getRicevitore()->getCognome() + " di ";
        else
            str += "X di ";
        str += std::to_string(t->getInvio())
               + std::to_string(t->getDataora()->getGiorno()) + ":" + std::to_string(t->getDataora()->getMese())
               + std::to_string(t->getDataora()->getAnno()) + " " + std::to_string(t->getDataora()->getOra()) + ":"
               + std::to_string(t->getDataora()->getMinuto()) + ":" +std::to_string(t->getDataora()->getSecondo());
    }
    else {
        if (typeid(t) == typeid(Deposito))
            //formato linea file
            //Deposito nome1 cognome1 di denaro g:m:a o:m:s
            str = "Deposito ";
        if (typeid(t) == typeid(Prelievo))
            //formato linea file
            //Prelievo nome1 cognome1 di denaro g:m:a o:m:s
            str = "Prelievo ";
        str += t->getMittente()->getNome() + " ";
        if(t->getMittente()->ispersonaFisica())
            str += t->getMittente()->getCognome() + " di ";
        else
            str += "X di ";
        str += std::to_string(t->getInvio())
               + std::to_string(t->getDataora()->getGiorno()) + ":" + std::to_string(t->getDataora()->getMese())
               + std::to_string(t->getDataora()->getAnno()) + " " + std::to_string(t->getDataora()->getOra()) + ":"
               + std::to_string(t->getDataora()->getMinuto()) + ":" +std::to_string(t->getDataora()->getSecondo());
    }
    fm->write(filename, str, fatalerror);
    return fatalerror;
}

bool ContoCorrente::addInvestmentToFile(Investimento *i, FileMgr *fm, std::string filename, bool &fatalerror) {
    std::string str = createInvestmentString(i);
    fm->write(filename, str, fatalerror);
    return fatalerror;
}

std::string ContoCorrente::createInvestmentString(Investimento *i) {
    //formato linea file
    //Investimento nome cognome di denaro per causale g:m:a o:m:s
    std::string str = "Investimento ";
    str += i->getUtenza()->getNome() + " ";
    if(i->getUtenza()->ispersonaFisica())
        str += i->getUtenza()->getCognome() + " di ";
    else
        str += "X di ";
    str += std::to_string(i->getInvestimento()) + " per " + i->getCausale() + " "
           + std::to_string(i->getDataora()->getGiorno()) + ":" + std::to_string(i->getDataora()->getMese())
           + std::to_string(i->getDataora()->getAnno()) + " " + std::to_string(i->getDataora()->getOra()) + ":"
           + std::to_string(i->getDataora()->getMinuto()) + ":" +std::to_string(i->getDataora()->getSecondo());
    return str;
}

bool ContoCorrente::removeInvestmentFromFile(Investimento *i, FileMgr *fm, std::string filename, bool &fatalerror) {
    std::string str = createInvestmentString(i);
    fm->deleteLine(filename, str, fatalerror);
    return fatalerror;

}