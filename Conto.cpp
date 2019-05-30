
#include "Conto.h"


Conto::Conto(std::shared_ptr<Utenza> t, std::string n, float s, float si){
    investimenti = std::list<Investimento*>();
    transazioni = std::list<std::shared_ptr<Transazione>>();
    titolare = t;
    nome = n;
    saldo = s;
    soldiInvestiti = si;
}

Conto::~Conto() {
    for(auto iter = investimenti.begin(); iter != investimenti.end(); iter++){
        delete (*iter);
        investimenti.erase(iter);
    }
    for(auto iter = transazioni.begin(); iter != transazioni.end(); iter++){
        transazioni.erase(iter);
    }
    investimenti.clear();
    transazioni.clear();
}

Conto::Conto(const Conto &that) {
    saldo = that.saldo;
    soldiInvestiti= that.soldiInvestiti;
    titolare = that.titolare;
    nome = that.nome;
    investimenti = that.investimenti;
    transazioni = that.transazioni;
}

Conto& Conto::operator=(Conto &that) {
    investimenti.clear();
    transazioni.clear();
    titolare = that.titolare;
    investimenti = that.investimenti;
    transazioni = that.transazioni;
    nome = that.nome;
    saldo = that.saldo;
    soldiInvestiti = that.soldiInvestiti;
    return *this;
}

float Conto::getSaldo() const {
    return saldo;
}


void Conto::setSaldo(float saldo) {
    Conto::saldo = saldo;
}


float Conto::getSoldiInvestiti() const {
    return soldiInvestiti;
}

void Conto::setSoldiInvestiti(float soldiInvestiti) {
    Conto::soldiInvestiti = soldiInvestiti;
}

std::shared_ptr<Utenza> Conto::getUtenza() const {
    return titolare;
}

bool Conto::addTransazione(std::shared_ptr<Transazione> t, FileMgr* fm, bool& fatalerror) {
    switch(t->getType()){
        case typeTransaction::Deposito:
            saldo += t->getInvio();
            //saldo = round(saldo * 100.0) / 100.0;
            transazioni.push_back(t);
            addTransactionToFile(t, fm, fatalerror);
            return true;
        case typeTransaction::Prelievo:
            if (t->getInvio() <= saldo) {
                transazioni.push_back(t);
                addTransactionToFile(t, fm, fatalerror);
                saldo -= t->getInvio();
                //saldo = round(saldo * 100.0) / 100.0;
                t->setCompleted(true);
                return true;
            }
        case typeTransaction::Bonifico:
            if (t->getMittente()->getUtenza() == titolare && nome == t->getMittente()->getNome()) {
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
    return false;
}

bool Conto::addInvestimento(Investimento* i, FileMgr* fm, bool& fatalerror) {
    if(i->getInvestimento() <= saldo) {
        i->setCompleted(true);
        investimenti.push_back(i);
        addInvestmentToFile(i, fm, fatalerror);
        saldo -= i->getInvestimento();
        //saldo = round(saldo * 100.0) / 100.0;
        soldiInvestiti += i->getInvestimento();
        //soldiInvestiti = round(soldiInvestiti * 100.0) / 100.0;
        return true;
    }
    return false;
}

bool Conto::removeInvestimento(Investimento* i, std::shared_ptr<DateTime> now, FileMgr* fm, bool& fatalerror) {
    int pos=0;
    std::list<Investimento*>::iterator iter;
    for(iter=investimenti.begin(); iter != investimenti.end(); ++iter){
        if((*iter)->operator==(*i)){
            break;
        }
        pos++;
    }
    if(pos <= investimenti.size()) {
        i->simulateInvestment(now);
        investimenti.remove(i);
        removeInvestmentFromFile(i, fm, fatalerror);
        saldo += i->getInvestimento() + i->getGuadagno();
        soldiInvestiti -= i->getInvestimento();
        return true;
    }
    return false;
}

bool Conto::addTransactionToFile(std::shared_ptr<Transazione> t, FileMgr* fm, bool &fatalerror) {
    std::string str;
    if(t->getType() == typeTransaction::Bonifico) {
        //formato linea file
        //Bonifico da nome1 cognome1 a nome2 cognome 2 di denaro g:m:a o:m:s
        str = "Bonifico da " + t->getMittente()->getNome() + " di " + t->getMittente()->getUtenza()->getNome() + " ";
        if(t->getMittente()->getUtenza()->ispersonaFisica())
            str += t->getMittente()->getUtenza()->getCognome() + " a ";
        else
            str += "X a ";
        str += t->getRicevitore()->getNome() + " di " + t->getRicevitore()->getUtenza()->getNome() + " ";
        if(t->getRicevitore()->getUtenza()->ispersonaFisica())
            str+= t->getRicevitore()->getUtenza()->getCognome() + " di ";
        else
            str += "X di ";
        //float invio = round(t->getInvio() * 100.0) / 100.0;
        float invio = t->getInvio();
        str += std::to_string(invio) + " ";
        str += std::to_string(t->getDataora()->getGiorno()) + ":" + std::to_string(t->getDataora()->getMese()) + ":"
               + std::to_string(t->getDataora()->getAnno()) + " " + std::to_string(t->getDataora()->getOra()) + ":"
               + std::to_string(t->getDataora()->getMinuto() )+ ":" +std::to_string(t->getDataora()->getSecondo());
    }
    if(t->getType() == typeTransaction::Deposito || t->getType() == typeTransaction::Prelievo) {
        if (t->getType() == typeTransaction::Deposito)
            //formato linea file
            //Deposito nome1 cognome1 di denaro g:m:a o:m:s
            str = "Deposito da ";
        if (t->getType() == typeTransaction::Prelievo)
            //formato linea file
            //Prelievo nome1 cognome1 di denaro g:m:a o:m:s
            str = "Prelievo da ";
        str += t->getMittente()->getNome() + " di " + t->getMittente()->getUtenza()->getNome() + " ";
        if(t->getMittente()->getUtenza()->ispersonaFisica())
            str += t->getMittente()->getUtenza()->getCognome() + " di ";
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

bool Conto::addInvestmentToFile(Investimento* i, FileMgr* fm, bool &fatalerror) {
    std::string str = createInvestmentString(i);
    fm->write(str, fatalerror);
    return fatalerror;
}

std::string Conto::createInvestmentString(Investimento* i) {
    //formato linea file
    //Investimento nome cognome di denaro per causale g:m:a o:m:s
    std::string str = "Investimento da ";
    str += i->getConto()->getNome() + " di " + i->getConto()->getUtenza()->getNome() + " ";
    if(i->getConto()->getUtenza()->ispersonaFisica())
        str += i->getConto()->getUtenza()->getCognome() + " di ";
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

bool Conto::removeInvestmentFromFile(Investimento* i, FileMgr* fm, bool &fatalerror) {
    std::string str = createInvestmentString(i);
    fm->deleteLine(str, fatalerror);
    if(fatalerror)
        return false;
    return true;
}

const std::string &Conto::getNome() const {
    return nome;
}
