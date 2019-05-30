
#include "ContoCorrente.h"


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
    for(auto iter = investimenti.begin(); iter != investimenti.end(); iter++){
        delete (*iter);
        investimenti.erase(iter);
    }
    for(auto iter = transazioni.begin(); iter != transazioni.end(); iter++){
        delete (*iter);
        transazioni.erase(iter);
    }
    investimenti.clear();
    transazioni.clear();
}

ContoCorrente::ContoCorrente(const ContoCorrente &that) : saldo(that.saldo), soldiInvestiti(that.soldiInvestiti) {
    titolare = that.titolare;
    investimenti = that.investimenti;
    transazioni = that.transazioni;
}

ContoCorrente& ContoCorrente::operator=(ContoCorrente &that) {
    investimenti.clear();
    transazioni.clear();
    if(titolare!= nullptr)
        delete titolare;
    titolare = that.titolare;
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

bool ContoCorrente::addTransazione(Transazione *t, FileMgr* fm, bool& fatalerror) {
    if(t->getOperazione() == "Deposito") {
        saldo += t->getInvio();
        //saldo = round(saldo * 100.0) / 100.0;
        transazioni.push_back(t);
        addTransactionToFile(t, fm, fatalerror);
        return true;
    }
    else {
        if (t->getOperazione() == "Prelievo") {
            if (t->getInvio() <= saldo) {
                transazioni.push_back(t);
                addTransactionToFile(t, fm, fatalerror);
                saldo -= t->getInvio();
                //saldo = round(saldo * 100.0) / 100.0;
                t->setCompleted(true);
                return true;
            }
        }
        if (t->getOperazione() == "Bonifico") {
            if (t->getMittente() == titolare) {
                if (t->getInvio() <= saldo) {
                    transazioni.push_back(t);
                    addTransactionToFile(t, fm, fatalerror);
                    saldo -= t->getInvio();
                    //saldo = round(saldo * 100.0) / 100.0;
                    t->setCompleted(true);
                    return true;
                }
            }
            else {
                transazioni.push_back(t);
                addTransactionToFile(t, fm, fatalerror);
                saldo += t->getInvio();
                //saldo = round(saldo * 100.0) / 100.0;
                t->setCompleted(true);
                return true;
            }
        }
    }
    return false;
}

bool ContoCorrente::addInvestimento(Investimento *i, FileMgr* fm, bool& fatalerror) {
    if(i->getInvestimento() <= saldo) {
        investimenti.push_back(i);
        addInvestmentToFile(i, fm, fatalerror);
        saldo -= i->getInvestimento();
        //saldo = round(saldo * 100.0) / 100.0;
        soldiInvestiti += i->getInvestimento();
        //soldiInvestiti = round(soldiInvestiti * 100.0) / 100.0;
        i->setCompleted(true);
        return true;
    }
    return false;
}

bool ContoCorrente::removeInvestimento(Investimento *i, DateTime* now, FileMgr* fm, bool& fatalerror) {
    int pos=0;
    std::list<Investimento*>::iterator iter;
    for(iter=investimenti.begin(); iter != investimenti.end(); ++iter){
        if((*iter)->operator==(*i)){
            break;
        }
        pos++;
    }
    if(pos < investimenti.size()) {
        i->simulateInvestment(now);
        investimenti.remove(i);
        removeInvestmentFromFile(i, fm, fatalerror);
        saldo += i->getInvestimento() + i->getGuadagno();
        soldiInvestiti -= i->getInvestimento();
        return true;
    }
    return false;
}

bool ContoCorrente::addTransactionToFile(Transazione *t, FileMgr *fm, bool &fatalerror) {
    std::string str;
    if(t->getOperazione() == "Bonifico") {
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
        //float invio = round(t->getInvio() * 100.0) / 100.0;
        float invio = t->getInvio();
        str += std::to_string(invio) + " ";
        str += std::to_string(t->getDataora()->getGiorno()) + ":" + std::to_string(t->getDataora()->getMese()) + ":"
               + std::to_string(t->getDataora()->getAnno()) + " " + std::to_string(t->getDataora()->getOra()) + ":"
               + std::to_string(t->getDataora()->getMinuto()) + ":" +std::to_string(t->getDataora()->getSecondo());
    }
    else {
        if (t->getOperazione() == "Deposito")
            //formato linea file
            //Deposito nome1 cognome1 di denaro g:m:a o:m:s
            str = "Deposito ";
        if (t->getOperazione() == "Prelievo")
            //formato linea file
            //Prelievo nome1 cognome1 di denaro g:m:a o:m:s
            str = "Prelievo ";
        str += t->getMittente()->getNome() + " ";
        if(t->getMittente()->ispersonaFisica())
            str += t->getMittente()->getCognome() + " di ";
        else
            str += "X di ";
        //float invio = round(t->getInvio() * 100.0) / 100.0;
        float invio = t->getInvio();
        str += std::to_string(t->getInvio()) + " ";
        str += std::to_string(t->getDataora()->getGiorno()) + ":" + std::to_string(t->getDataora()->getMese()) + ":"
               + std::to_string(t->getDataora()->getAnno()) + " " + std::to_string(t->getDataora()->getOra()) + ":"
               + std::to_string(t->getDataora()->getMinuto()) + ":" +std::to_string(t->getDataora()->getSecondo());
    }
    fm->write(str, fatalerror);
    if(fatalerror)
        return false;
    return true;
}

bool ContoCorrente::addInvestmentToFile(Investimento *i, FileMgr *fm, bool &fatalerror) {
    std::string str = createInvestmentString(i);
    fm->write(str, fatalerror);
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
    //float investimento = round(i->getInvestimento() * 100.0) / 100.0;
    float investimento = i->getInvestimento();
    str += std::to_string(investimento) + " per " + i->getCausale() + " "
           + std::to_string(i->getDataora()->getGiorno()) + ":" + std::to_string(i->getDataora()->getMese()) + ":"
           + std::to_string(i->getDataora()->getAnno()) + " " + std::to_string(i->getDataora()->getOra()) + ":"
           + std::to_string(i->getDataora()->getMinuto()) + ":" +std::to_string(i->getDataora()->getSecondo());
    return str;
}

bool ContoCorrente::removeInvestmentFromFile(Investimento *i, FileMgr *fm, bool &fatalerror) {
    std::string str = createInvestmentString(i);
    fm->deleteLine(str, fatalerror);
    if(fatalerror)
        return false;
    return true;
}
