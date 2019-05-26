//
#include<fstream>
#include <map>
#include <sstream>
#include "string"
#include <vector>
#include <iomanip>
#include <tgmath.h>
#include "time.h"
#include "Date.h"
#include "Utenza.h"
#include "ContoCorrente.h"
#include "FileMgr.h"
#include "Bonifico.h"
#include "Prelievo.h"
#include "Deposito.h"

using namespace std;
class Menu {
private:
    void cinClear(){
        cin.clear();
        cin.ignore();
    }
    void resetStream(stringstream& ss){
        ss.clear();
        ss.seekg(0);
        ss.seekp(0);
    }
    float readSaldo(vector<string> container, std::stringstream& ss, char delim){
        for (int i = 0; i < container.size(); i++)
            container.erase(container.begin(), container.end());
        string token;
        while (std::getline(ss, token, delim)) {
            container.push_back(token);
        }
        float s = stof(container[0]);
        return s;
    }
    DateTime* calcolaDateTime(){
        time_t t = time(0);
        struct tm *now;
        DateTime* dt = new DateTime(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, now->tm_hour, now->tm_min, now->tm_sec, true);
        return dt;
    }
public:
    void run() {
        srand(time(NULL));
        string searchName, nomeInvio, cognomeInvio, nome, cognome = " ", ind, prov, filename, filenameTransaction, filenameInvestment, filenameOther, filenameOtherInvestment, filenameOtherTransaction, str, causale;
        vector <string> container;
        float deposito, invio, prelievo, saldo, f, f1, investimento;
        bool res, res1, result, isBissextile = false, exitMenu = false, searchCognome = false, failure = false, fatalError = false, sendToYou =false;
        int switch1, switch2, gn, mn, an, pf, pfo, nc;
        const char *c;
        DateTime* dt;
        char sesso, delim1 = ' ';;
        std::stringstream ss;
        ContoCorrente *myBankAccount, *otherBankAccount;
        Utenza *me, *other;
        FileMgr *fileOtherUser, *fileOtherUserTransaction, *fileOtherUserInvestment;
        Bonifico* b;
        Investimento* i;
        Prelievo* p;
        Deposito* dep;
        cin.exceptions(std::istream::failbit);
        do {
            try {
                cout << "Inserisca 1 se si tratta di una persona fisica altrimenti 0" << endl;
                cin >> pf;
                failure = false;
            } catch (ios_base::failure &e) {
                failure = true;
                pf = -1;
                cinClear();
            }
        } while ((pf < 0 || pf > 1) || failure == true);
        if(pf==1)
            cout << "Inserisca il suo nome" << endl;
        else
            cout << "Inserisca il nome dell'azienda" << endl;
        cin >> nome;
        if (pf == 1) {
            cout << "Inserisca il suo cognome (senza spaziature per cognome doppio)" << endl;
            cin >> cognome;
            filename = nome + cognome + ".txt";
            filenameInvestment = nome + cognome + "Investment.txt";
            filenameTransaction = nome + cognome + "Transaction.txt";
        } else {
            filename = nome + ".txt";
            filenameInvestment = nome + "Investment.txt";
            filenameTransaction = nome + "Transaction.txt";
        }
        FileMgr *fileUtenze = new FileMgr(filename, true, fatalError);
        FileMgr *fileInvestmentUtenza = new FileMgr(filenameInvestment, true, fatalError);
        FileMgr *fileTransactionUtenza = new FileMgr(filenameTransaction, true, fatalError);
        if (fileUtenze->isFileExists() == false && !fatalError) {
            if (pf == 1) {
                do {
                    try {
                        cout << "Inserisca il suo giorno di nascita" << endl;
                        cin >> gn;
                        failure = false;
                    } catch (ios_base::failure &e) {
                        failure = true;
                        gn = -1;
                        cinClear();
                    }
                } while ((gn <= 0 || gn > 31) || failure == true);
                do {
                    try {
                        cout << "Inserisca il suo mese di nascita" << endl;
                        cin >> mn;
                        failure = false;
                    } catch (ios_base::failure &e) {
                        failure = true;
                        mn = -1;
                        cinClear();
                    }
                } while ((mn <= 0 || mn > 12) || failure == true);
                do {
                    try {
                        cout << "Inserisca il suo anno di nascita" << endl;
                        cin >> an;
                        failure = false;
                    } catch (ios_base::failure &e) {
                        failure = true;
                        an = -1;
                        cinClear();
                    }
                } while ((an <= 1900 || an > 2020) || failure == true);
                do {
                    try {
                        cout << "Inserisca il suo sesso (m,f)" << endl;
                        cin >> sesso;
                        failure = false;
                    } catch (ios_base::failure &e) {
                        failure = true;
                        sesso = 'a';
                        cinClear();
                    }
                } while ((sesso != 'm' && sesso != 'f') || failure == true);
                string ss(1, sesso);
                string gns = std::to_string(gn);
                string mns = std::to_string(mn);
                string ans = std::to_string(an);
                if(gn == 29 && mn == 2)
                    isBissextile = true;
                me = new Utenza(nome, cognome, sesso, gn, mn, an, isBissextile);
                str = nome + " " + cognome;
                if (!fatalError)
                    fileUtenze->openNewFile(filename, str, fatalError);
                str = ss + " " + gns + ":" + mns + ":" + ans;
                if (!fatalError)
                    fileUtenze->write(filename, str, fatalError);
            } else {
                cout << "Inserisca l'indirizzo" << endl;
                cin >> ind;
                do {
                    try {
                        cout << "Inserisca il numero civico" << endl;
                        cin >> nc;
                        failure = false;
                    } catch (ios_base::failure &e) {
                        failure = true;
                        nc = -1;
                        cinClear();
                    }
                } while ((nc <= 0) || failure == true);
                cout << "Inserisca la provincia" << endl;
                cin >> prov;
                string ncs = std::to_string(nc);
                me = new Utenza(nome, ind, nc, prov);
                str = nome;
                if (!fatalError)
                    fileUtenze->openNewFile(filename, str, fatalError);
                str = ind + " " + ncs + " " + prov;
                if (!fatalError)
                    fileUtenze->write(filename, str, fatalError);
            }
            myBankAccount = new ContoCorrente(me, 0, 0);
            dt = calcolaDateTime();
            str = "Account creato il " + std::to_string(dt->getGiorno()) + ":" +
                  std::to_string(dt->getMese()) + ":" + std::to_string(dt->getAnno()) +
                  " " + std::to_string(dt->getOra()) + ":" + std::to_string(dt->getMinuto()) + ":" +
                  std::to_string(dt->getSecondo());
            if(!fatalError)
                fileUtenze->write(filename, str, fatalError);
        } else if (fileUtenze->isFileExists() == true && !fatalError) {
            if (!fatalError) {
                if(pf)
                    searchCognome = true;
                me = new Utenza(nome, cognome, searchCognome);
                myBankAccount = new ContoCorrente(me, 0, 0);
                myBankAccount->getInvestimenti(fileInvestmentUtenza, filenameInvestment, fatalError);
                if(!fatalError)
                    myBankAccount->getTransazioni(fileTransactionUtenza, filenameTransaction, fatalError);
            }
        }
        while (exitMenu == false && !fatalError) {
            try {
                cout << endl;
                cout << "Inserire il numero corrispondente alla operazione che si vuole eseguire" << endl;
                cout << "1) Prelevare denaro dal proprio conto corrente" << endl;
                cout << "2) Depositare denaro sul proprio conto corrente" << endl;
                cout << "3) Effettuare un bonifico su un altro conto corrente" << endl;
                cout << "4) Effettuare un investimento" << endl;
                cout << "0) Per uscire" << endl;
                cin >> switch1;
                switch (switch1) {
                    case 1:
                        try {
                            f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                            cout << "Il suo credito è di " << f << endl;
                            cout << "Inserire il denaro che vuole prelevare dal proprio conto corrente" << endl;
                            cin >> prelievo;
                        } catch (ios_base::failure &e) {
                            cerr << "Errore nell'inserimento dati per il prelievo, ritorno al menu principale " << endl;
                            prelievo = 0;
                            cinClear();
                        }
                        f1 = round(prelievo * 100.0) / 100.0;
                        dt = calcolaDateTime();
                        p = new Prelievo(f1, me, dt, false);
                        res = myBankAccount->addTransazione(p, fileTransactionUtenza, filenameTransaction, fatalError);
                        if (!fatalError && !res) {
                            cout << "Prelievo avvenuto con successo" << endl;
                            f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                            cout << "Il suo credito adesso è di " << f << endl;
                        } else {
                            cout << "Problemi con l'operazione di prelievo" << endl;
                        }
                        break;
                    case 2:
                        cout << "Inserire il denaro che vuole depositare sul proprio conto corrente" << endl;
                        result = true;
                        while (result) {
                            try {
                                cout << "Premere 1 se ha finito di depositare altrimenti prema 0 per annullare il deposito"
                                        << endl;
                                cin >> switch2;
                                switch (switch2) {
                                    case 1:
                                        f1 = (rand() % 100000);
                                        f1 /= 100;
                                        deposito = round(f1 * 100.0) / 100.0;
                                        dt = calcolaDateTime();
                                        dep = new Deposito(deposito, me, dt, false);
                                        res = myBankAccount->addTransazione(dep, fileTransactionUtenza, filenameTransaction, fatalError);
                                        if(!fatalError && !res) {
                                            cout << "Il suo deposito di " << deposito << " è andato a buon fine"
                                                 << endl;
                                            f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                                            cout << "Il suo credito adesso è di " << f << endl;
                                        } else
                                            cout << "Problemi con l'operazione di deposito" << endl;
                                        result = false;
                                        break;
                                    case 0:
                                        cout << "Ha annullato la sua operazione di deposito" << endl;
                                        result = false;
                                        break;
                                    default:
                                        cout << "Ha inserito un valore associato a nessuna operazione " << endl;
                                        break;
                                }
                            } catch (ios_base::failure &e) {
                                switch2 = 5;
                                cinClear();
                            }
                        }
                        break;
                    case 3:
                        sendToYou = false;
                        do {
                            try {
                                cout << "Inserire 1 se vuole fare il bonifico ad persona fisica altrimenti 0 " << endl;
                                cin >> pfo;
                                failure = false;
                            } catch (ios_base::failure &e) {
                                failure = true;
                                pfo = -1;
                                cinClear();
                            }
                        } while ((pfo < 0 || pfo > 1) || failure == true);
                        cout << "Inserire il nome della persona a cui fare il bonifico" << endl;
                        cin >> nomeInvio;
                        if (pfo == 1) {
                            cout << "Inserire il cognome della persona a cui fare il bonifico" << endl;
                            cin >> cognomeInvio;
                            if (nomeInvio == nome && cognomeInvio == cognome)
                                sendToYou = true;
                            else {
                                filenameOther = nomeInvio + cognomeInvio + ".txt";
                                filenameOtherTransaction = nomeInvio + cognomeInvio + "Transaction.txt";
                            }
                        } else {
                            if (nome == nomeInvio)
                                sendToYou=true;
                            else {
                                filenameOther = nomeInvio + ".txt";
                                filenameOtherTransaction = nomeInvio + "Transaction.txt";
                            }
                        }
                        fileOtherUser = new FileMgr(filenameOther, true, fatalError);
                        fileOtherUserTransaction = new FileMgr(filenameTransaction, true, fatalError);
                        if (fileOtherUser->isFileExists() && !fatalError && !sendToYou) {
                            other = new Utenza(nomeInvio, cognomeInvio, pfo);
                            f = myBankAccount->getSaldo();
                            do{
                                try {
                                    cout << "Il suo credito è di " << f << endl;
                                    cout << "Inserire il valore del denaro che vuole inviare, inserire valore 0 se si vuole annullare il bonifico "
                                            << endl;
                                    cin >> invio;
                                    failure = false;
                                } catch (ios_base::failure &e) {
                                    failure = true;
                                    invio = -1;
                                    cinClear();
                                }
                            } while ((invio < 0) || failure == true);
                            f1 = round(invio * 100.0) / 100.0;
                            b = new Bonifico(f1, me, other, dt, false);
                            dt = calcolaDateTime();
                            if ((invio > 0) && !fatalError) {
                                res = myBankAccount->addTransazione(b, fileTransactionUtenza, filenameTransaction, fatalError);
                                res1 = otherBankAccount->addTransazione(b, fileOtherUserTransaction, filenameOtherTransaction, fatalError);
                                if(!fatalError && !res && !res1){
                                    cout << "Bonifico inviato con successo " << endl;
                                    f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                                    cout << "Hai inviato " << f1 << " euro addesso il tuo credito è di " << f << endl;
                                }
                                else
                                    cout << "Problemi nell'invio del bonifico" << endl;
                            } else if (invio == 0) {
                                cout << "Operazione annullata " << endl;
                            }
                        } else if(sendToYou) {
                            cout << "Non puoi fare un bonifico a te stesso" << endl;
                            cout << endl;
                        }else{
                            cout << "Conto corrente richiesto non trovato" << endl;
                        }
                        break;
                    case 4:
                        do {
                            try {
                                cout << "Inserire il valore del denaro che vuole investire " << endl;
                                cin >> investimento;
                                failure = false;
                            } catch (ios_base::failure &e) {
                                failure = true;
                                investimento = -1;
                                cinClear();
                            }
                        } while ((investimento<=0) || failure == true);
                        cout << "inserisci la causale " << endl;
                        cin >> causale;
                        f1 = round(investimento * 100.0) / 100.0;
                        dt = calcolaDateTime();
                        i = new Investimento(causale, f1, me, dt, false);
                        res = myBankAccount->addInvestimento(i, fileInvestmentUtenza, filenameInvestment, fatalError);
                        if(!fatalError && !res){
                            cout << "Investimento eseguito con successo " << endl;
                            f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                            cout << "Hai investito " << f1 << " euro addesso il tuo credito è di " << f << endl;
                            f = round(myBankAccount->getSoldiInvestiti() * 100.0) / 100.0;
                            cout << "Hai " << f1 << " euro investiti " << endl;
                        }
                        break;
                    case 0:
                        exitMenu = true;
                        break;
                    default:
                        cout << "Ha inserito un valore associato a nessuna operazione " << endl;
                        break;
                }
            } catch (ios_base::failure &e) {
                switch1 = -2;
                cinClear();
            }
        }
    }

};