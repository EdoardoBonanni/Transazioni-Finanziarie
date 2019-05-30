


#ifndef TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H
#define TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H


#include "Utenza.h"
#include "Transazione.h"
#include "Investimento.h"
#include "FileMgr.h"
#include <list>

class ContoCorrente {
public:
    ContoCorrente(Utenza* t, float s=0, float si=0);
    ~ContoCorrente();

    ContoCorrente(const ContoCorrente& that);
    ContoCorrente& operator=(ContoCorrente& that);

    float getSaldo() const;
    float getSoldiInvestiti() const;
    Utenza* getUtenza() const;
    void setSaldo(float saldo);

    void setSoldiInvestiti(float soldiInvestiti);

    bool addInvestimento(Investimento* i, FileMgr* fm, bool& fatalerror);
    bool removeInvestimento(Investimento* i, DateTime* now, FileMgr* fm, bool& fatalerror);
    bool addTransazione(Transazione* t, FileMgr* fm, bool& fatalerror);

private:
    float saldo;
    float soldiInvestiti;
    std::list<Investimento*> investimenti;
    std::list<Transazione*> transazioni;
    Utenza* titolare;

    bool addInvestmentToFile(Investimento* i, FileMgr* fm, bool& fatalerror);
    bool removeInvestmentFromFile(Investimento* i, FileMgr* fm, bool& fatalerror);
    bool addTransactionToFile(Transazione* t, FileMgr* fm, bool& fatalerror);
    std::string createInvestmentString(Investimento* i);
};


#endif //TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H
