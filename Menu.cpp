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
public:
    void run() {
        srand(time(NULL));
        string searchName, nomeInvio, cognomeInvio, nome, cognome = " ", ind, prov, filename, filenameOther, str, str1, posteName, fileNamePoste, token;
        vector <string> container;
        float deposito, invio, prelievo, saldo, f, f1;
        bool result, exitMenu = false, searchCognome = false, failure = false, fatalError = false, sendToYou =false;
        int switch1, switch2, gn, mn, an, pf, pfo, nc;
        const char *c;
        time_t t = time(0);
        struct tm *now;
        char sesso, delim1 = ' ';;
        std::stringstream ss;
        ContoCorrente *myBankAccount;
        ContoCorrente *otherBankAccount;
        Utenza *me;
        Utenza *other;
        FileMgr *fileOtherUser;
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
        cout << "Inserisca il suo nome (o il nome dell'azienda)" << std::endl;
        cin >> nome;
        if (pf == 1) {
            cout << "Inserisca il suo cognome (senza spaziature per cognome doppio)" << endl;
            cin >> cognome;
            filename = nome + cognome + ".txt";
        } else {
            filename = nome + ".txt";
        }
        FileMgr *fileUtenze = new FileMgr(filename, true, fatalError);
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
                me = new Utenza(nome, cognome, sesso, gn, mn, an);
                str = nome + " " + cognome;
                if (!fatalError)
                    fileUtenze->openNewFile(filename, str, fatalError);
                str = ss + " " + gns + "/" + mns + "/" + ans;
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
                str = nome + " X";
                if (!fatalError)
                    fileUtenze->openNewFile(filename, str, fatalError);
                str = ind + " " + ncs + " " + prov;
                if (!fatalError)
                    fileUtenze->write(filename, str, fatalError);
            }
            myBankAccount = new ContoCorrente(me, 0);
            now = localtime(&t);
            str = "Account creato il " + std::to_string(now->tm_mday) + "/" +
                  std::to_string((now->tm_mon + 1)) + "/" + std::to_string((now->tm_year + 1900)) +
                  " " + std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" +
                  std::to_string(now->tm_sec);
            if(!fatalError)
                fileUtenze->write(filename, str, fatalError);
            str = "0 euro disponibili sul suo conto";
            if(!fatalError)
                fileUtenze->write(filename, str, fatalError);
        } else if (fileUtenze->isFileExists() == true && !fatalError) {
            str = fileUtenze->readFirstLine(filename, fatalError);
            if (!fatalError) {
                ss.str("");
                ss << str;
                while (std::getline(ss, token, delim1) /*|| std::getline(ss, token, delim2)*/) {
                    container.push_back(token);
                }
                nome = container[0];
                cognome = container[1];
                if (cognome != "X")
                    searchCognome = true;
                me = new Utenza(nome, cognome, searchCognome);
                str = fileUtenze->readSecondLastLine(filename, fatalError);
                if (!fatalError) {
                    resetStream(ss);
                    ss << str;
                    for (int i = 0; i < container.size(); i++)
                        container.erase(container.begin(), container.end());
                    while (std::getline(ss, token, delim1) /*|| std::getline(ss, token, delim2)*/) {
                        container.push_back(token);
                    }
                    saldo = stof(container[0]);
                    myBankAccount = new ContoCorrente(me, saldo);
                    resetStream(ss);
                }
            }
        }
        posteName = "Poste";
        fileNamePoste = posteName + ".txt";
        FileMgr *filePoste = new FileMgr(fileNamePoste, true, fatalError);
        Utenza *poste = new Utenza(posteName, "via togliatti", 2, "firenze");
        ContoCorrente *contoposte = new ContoCorrente(poste, 1000000000);
        if (filePoste->isFileExists() == false && !fatalError) {
            str = poste->getNome() + " X";
            filePoste->openNewFile(fileNamePoste, str, fatalError);
            if (!fatalError) {
                str = poste->getIndirizzo() + " " + std::to_string(poste->getNumeroCivico()) + " " +
                      poste->getProvincia();
                filePoste->write(fileNamePoste, str, fatalError);
            }
        }
        while (exitMenu == false && !fatalError) {
            try {
                cout << endl;
                cout << "Inserire il numero corrispondente alla operazione che si vuole eseguire" << endl;
                cout << "1) Prelevare denaro dal proprio conto corrente" << endl;
                cout << "2) Depositare denaro sul proprio conto corrente" << endl;
                cout << "3) Effettuare un bonifico su un altro conto corrente" << endl;
                cout << "0) Per uscire" << endl;
                cin >> switch1;
                switch (switch1) {
                    case 1:
                        try {
                            f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                            cout << "Il suo credito è di " << f << endl;
                            cout << "Inserire il denaro che vuole prelevare dal proprio conto corrente" << endl;
                            cin >> prelievo;
                            if (myBankAccount->PrelevaDenaro(prelievo)) {
                                cout << "Prelievo avvenuto con successo" << endl;
                                f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                                cout << "Il suo credito adesso è di " << f << endl;
                                now = localtime(&t);
                                str = " ";
                                fileUtenze->write(filename, str, fatalError);
                                if (!fatalError) {
                                    ss.str("");
                                    f1 = round(prelievo * 100.0) / 100.0;
                                    ss << f1;
                                    str = "Prelievo di " + ss.str() + " avvenuto con successo";
                                    fileUtenze->write(filename, str, fatalError);
                                    if (!fatalError) {
                                        str = "Data " + std::to_string(now->tm_mday) + "/" +
                                              std::to_string((now->tm_mon + 1)) + "/" +
                                              std::to_string((now->tm_year + 1900)) +
                                              " " + std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) +
                                              ":" +
                                              std::to_string(now->tm_sec);
                                        fileUtenze->write(filename, str, fatalError);
                                        if (!fatalError) {
                                            ss.str("");
                                            ss << f;
                                            str = ss.str() + " euro disponibili sul tuo conto";
                                            fileUtenze->write(filename, str, fatalError);
                                        }
                                    }
                                }
                            } else {
                                cout << "Credito insufficiente" << endl;
                            }
                        } catch (ios_base::failure &e) {
                            cerr << "Errore nell'inserimento dati per il prelievo, ritorno al menu principale " << endl;
                            prelievo = 0;
                            cinClear();
                        }
                        break;
                    case 2:
                        cout << "Inserire il denaro che vuole depositare sul proprio conto corrente" << endl;
                        result = true;
                        while (result) {
                            try {
                                cout
                                        << "Premere 1 se ha finito di depositare altrimenti prema 0 per annullare il deposito"
                                        << endl;
                                cin >> switch2;
                                switch (switch2) {
                                    case 1:
                                        f1 = (rand() % 100000);
                                        f1 /= 100;
                                        deposito = round(f1 * 100.0) / 100.0;
                                        myBankAccount->DepositaDenaro(deposito);
                                        cout << "Il suo deposito di " << deposito << " è andato a buon fine" << endl;
                                        f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                                        cout << "Il suo credito adesso è di " << f << endl;
                                        now = localtime(&t);
                                        str = " ";
                                        fileUtenze->write(filename, str, fatalError);
                                        if (!fatalError) {
                                            ss.str("");
                                            ss << deposito;
                                            str = "Deposito di " + ss.str() + " avvenuto con successo";
                                            fileUtenze->write(filename, str, fatalError);
                                            if (!fatalError) {
                                                str = "Data " + std::to_string(now->tm_mday) + "/" +
                                                      std::to_string((now->tm_mon + 1)) + "/" +
                                                      std::to_string((now->tm_year + 1900)) +
                                                      " " + std::to_string(now->tm_hour) + ":" +
                                                      std::to_string(now->tm_min) +
                                                      ":" +
                                                      std::to_string(now->tm_sec);
                                                fileUtenze->write(filename, str, fatalError);
                                                if (!fatalError) {
                                                    ss.str("");
                                                    ss << f;
                                                    str = ss.str() + " euro disponibili sul tuo conto";
                                                    fileUtenze->write(filename, str, fatalError);
                                                }
                                            }
                                        }
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
                            else
                                filenameOther = nomeInvio + cognomeInvio + ".txt";
                        } else {
                            if (nome == nomeInvio)
                                sendToYou=true;
                            else
                                filenameOther = nomeInvio + ".txt";
                        }
                        fileOtherUser = new FileMgr(filenameOther, true, fatalError);
                        if (fileOtherUser->isFileExists() && !fatalError && !sendToYou) {
                            other = new Utenza(nomeInvio, cognomeInvio, pfo);
                            str = fileOtherUser->readSecondLastLine(filenameOther, fatalError);
                            if (!fatalError) {
                                resetStream(ss);
                                ss << str;
                                for (int i = 0; i < container.size(); i++)
                                    container.erase(container.begin(), container.end());
                                while (std::getline(ss, token, delim1) /*|| std::getline(ss, token, delim2)*/) {
                                    container.push_back(token);
                                }
                                saldo = stof(container[0]);
                                resetStream(ss);;
                                f = round(saldo * 100.0) / 100.0;
                                otherBankAccount = new ContoCorrente(other, f);
                                f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                                do {
                                    try {
                                        cout << "Il suo credito è di " << f << endl;
                                        cout
                                                << "Inserire il valore del denaro che vuole inviare, inserire valore 0 se si vuole annullare il bonifico "
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
                                if ((invio > 0) && myBankAccount->InviaDenaro(f1, otherBankAccount)) {
                                    cout << "Bonifico avvenuto con successo " << endl;
                                    f = round(myBankAccount->getSaldo() * 100.0) / 100.0;
                                    cout << "Hai inviato " << f1 << " euro addesso il tuo credito è di " << f << endl;
                                    now = localtime(&t);
                                    //me
                                    str = " ";
                                    fileUtenze->write(filename, str, fatalError);
                                    if (!fatalError) {
                                        ss.str("");
                                        ss << f1;
                                        if (pfo == 1)
                                            str = "Bonifico di " + ss.str() + " avvenuto con successo a " + nomeInvio +
                                                  " " + cognomeInvio;
                                        else
                                            str = "Bonifico di " + ss.str() + " avvenuto con successo a " + nomeInvio;
                                        fileUtenze->write(filename, str, fatalError);
                                        if (!fatalError) {
                                            str = "Data " + std::to_string(now->tm_mday) + "/" +
                                                  std::to_string((now->tm_mon + 1)) + "/" +
                                                  std::to_string((now->tm_year + 1900)) +
                                                  " " + std::to_string(now->tm_hour) + ":" +
                                                  std::to_string(now->tm_min) +
                                                  ":" +
                                                  std::to_string(now->tm_sec);
                                            fileUtenze->write(filename, str, fatalError);
                                            if (!fatalError) {
                                                ss.str("");
                                                ss << f;
                                                str = ss.str() + " euro disponibili sul tuo conto";
                                                fileUtenze->write(filename, str, fatalError);
                                                if (!fatalError) {
                                                    //other
                                                    str = " ";
                                                    fileOtherUser->write(filenameOther, str, fatalError);
                                                    if (!fatalError) {
                                                        ss.str("");
                                                        ss << f1;
                                                        if (pf == 1)
                                                            str = "Bonifico di " + ss.str() +
                                                                  " ricevuto con successo da " +
                                                                  nome +
                                                                  " " +
                                                                  cognome;
                                                        else
                                                            str = "Bonifico di " + ss.str() +
                                                                  " ricevuto con successo da " +
                                                                  nome;
                                                        fileOtherUser->write(filenameOther, str, fatalError);
                                                        if (!fatalError) {
                                                            str = "Data " + std::to_string(now->tm_mday) + "/" +
                                                                  std::to_string((now->tm_mon + 1)) + "/" +
                                                                  std::to_string((now->tm_year + 1900)) +
                                                                  " " + std::to_string(now->tm_hour) + ":" +
                                                                  std::to_string(now->tm_min) +
                                                                  ":" +
                                                                  std::to_string(now->tm_sec);
                                                            fileOtherUser->write(filenameOther, str, fatalError);
                                                            if (!fatalError) {
                                                                ss.str("");
                                                                f = round(otherBankAccount->getSaldo() * 100.0) / 100.0;
                                                                ss << f;
                                                                str = ss.str() + " euro disponibili sul tuo conto";
                                                                fileOtherUser->write(filenameOther, str, fatalError);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else if (invio == 0) {
                                    cout << "Operazione annullata " << endl;
                                } else {
                                    cout << "Credito insufficente, il tuo credito è di " << f << endl;
                                }
                            }
                        } else if(sendToYou) {
                            cout << "Non puoi fare un bonifico a te stesso" << endl;
                            cout << endl;
                        }else{
                            cout << "Conto corrente richiesto non trovato" << endl;
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
                switch1 = 4;
                cinClear();
            }
        }
    }

};