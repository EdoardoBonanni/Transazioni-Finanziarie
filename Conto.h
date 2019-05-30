


#ifndef TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H
#define TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H


#include "Utenza.h"
#include "FileMgr.h"
#include "Investimento.h"
#include "Transazione.h"
#include <list>

class Transazione;
class Investimento;
class FileMgr;

class Conto {
public:
    Conto(std::shared_ptr<Utenza> t, std::string n, float s=0, float si=0);
    ~Conto();

    Conto(const Conto& that);
    Conto& operator=(Conto& that);

    float getSaldo() const;
    float getSoldiInvestiti() const;
    std::shared_ptr<Utenza> getUtenza() const;

    const std::string &getNome() const;

    void setSaldo(float saldo);
    void setSoldiInvestiti(float soldiInvestiti);

    bool addInvestimento(Investimento* i, FileMgr* fm, bool& fatalerror);
    bool removeInvestimento(Investimento* i, std::shared_ptr<DateTime> now, FileMgr* fm, bool& fatalerror);
    bool addTransazione(std::shared_ptr<Transazione> t, FileMgr* fm, bool& fatalerror);

private:
    float saldo;
    float soldiInvestiti;
    std::list<Investimento*> investimenti;
    std::list<std::shared_ptr<Transazione>> transazioni;
    std::string nome;
    std::shared_ptr<Utenza> titolare;

    bool addInvestmentToFile(Investimento* i, FileMgr* fm, bool& fatalerror);
    bool removeInvestmentFromFile(Investimento* i, FileMgr* fm, bool& fatalerror);
    bool addTransactionToFile(std::shared_ptr<Transazione> t, FileMgr* fm, bool& fatalerror);
    std::string createInvestmentString(Investimento* i);
};


#endif //TRANSAZIONIFINANZIARIE_CONTOCORRENTE_H
