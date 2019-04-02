#include <iostream>
#include<fstream>
#include <map>
#include <sstream>
#include <iterator>
#include <vector>
#include "Date.h"
#include "Utenza.h"
#include "ContoCorrente.h"
#include "FileMgr.h"

using namespace std;
int main() {
    //lettura file Utenze
    string nome, cognome, filename, str, posteName, fileNamePoste;
    char sesso;
    float saldo;
    int gn, mn, an;
    ContoCorrente* myBankAccount;
    map<pair<string,string>, ContoCorrente*> lstConti;
    cout << "Inserisca il suo nome (solo primo nome)" << std::endl;
    cin >> nome;
    cout << "Inserisca il suo cognome (senza spaziature per cognome doppio)" << endl;
    cin >> cognome;
    filename = nome + cognome +".txt";
    FileMgr* fileUtenze = new FileMgr(filename, true);
    if(fileUtenze->isFileExists() == false) {
        cout << "Inserisca il suo giorno di nascita" << endl;
        cin >> gn;
        cout << "Inserisca il suo mese di nascita" << endl;
        cin >> mn;
        cout << "Inserisca il suo anno di nascita" << endl;
        cin >> an;
        cout << "Inserisca il suo sesso" << endl;
        cin >> sesso;
        string ss(1,sesso);
        string gns = std::to_string(gn);
        string mns = std::to_string(mn);
        string ans = std::to_string(an);
        Utenza* me = new Utenza(nome, cognome, sesso, gn, mn, an);
        myBankAccount = new ContoCorrente(me, 0);
        str = nome + " " + cognome;
        fileUtenze->openNewFile(filename, str);
        str = ss + " " + gns + "/" + mns + "/" + ans;
        fileUtenze->write(filename, str);
    }else{
        str = fileUtenze->readFirstLine(filename);
        //divisione stringa nome e cognome
        vector<string> container, container1;
        char delim1 = ' ';
        //char delim2 = ' ';
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim1) /*|| std::getline(ss, token, delim2)*/) {
            container.push_back(token);
        }
        nome = container[0];
        cognome = container[1];
        Utenza* me = new Utenza(nome, cognome);
        str = fileUtenze->readSecondLastLine(filename);
        std::stringstream ss1(str);
        while (std::getline(ss1, token, delim1) /*|| std::getline(ss, token, delim2)*/) {
            container1.push_back(token);
        }
        saldo = stof(container[0]);
        myBankAccount = new ContoCorrente(me, saldo);
    }
    //situazione contocorrente
    posteName = "Poste";
    fileNamePoste = posteName +".txt";
    FileMgr* filePoste = new FileMgr(fileNamePoste, true);
    Utenza* poste = new Utenza(posteName, "via togliatti", 2, "firenze");
    ContoCorrente* contoposte = new ContoCorrente(poste, 1000000000);
    const char* c;
    if(filePoste->isFileExists() == false) {
        /*if (poste->ispersonaFisica())
            str = poste->getNome() + " " + poste->getCognome();
        else*/
        str = poste->getNome() + " X";
        filePoste->openNewFile(fileNamePoste, str);
        str = poste->getIndirizzo() + " " + std::to_string(poste->getNumeroCivico()) + " " + poste->getProvincia();
        filePoste->write(fileNamePoste, str);
    }
    pair<pair<string,string>, ContoCorrente*> pair1 = {{poste->getNome(), " " }, contoposte  };
    lstConti.insert(pair1);
    /*Utenza* person1 = new Utenza("Pippo", "Pluto", 'm', 7, 3, 1990);
    ContoCorrente* conto1 = new ContoCorrente(person1);
    pair<pair<string,string>, ContoCorrente*> pair2 = {{person1->getNome(), person1->getCognome() }, conto1 };
    lstConti.insert(pair2);*/
    pair<string,string> pairn;
    map<pair<string,string>, ContoCorrente*>::const_iterator iter;
    string searchName, nomeInvio, cognomeInvio;
    float deposito, invio, prelievo;
    bool result, trovato, correctInsert;
    int switch1, switch2, switch3, d;
    /*Utenza* me = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998);
    ContoCorrente* myBankAccount = new ContoCorrente(me);
    pair< pair<string,string>, ContoCorrente*> pair3 = {{me->getNome(), me->getCognome() }, myBankAccount  };
    lstConti.insert(pair3);*/
    while(true){
        cout << "Inserire il numero corrispondente alla operazione che si vuole eseguire" << endl;
        cout << "1) Prelevare denaro dal proprio conto corrente" << endl;
        cout << "2) Depositare denaro sul proprio conto corrente" << endl;
        cout << "3) Effettuare un bonifico su un altro conto corrente" << endl;
        cin >> switch1;
        switch(switch1){
            case 1:
                cout << "Inserire il denaro che vuole prelevare dal proprio conto corrente" << endl;
                cin >> prelievo;
                if(myBankAccount->PrelevaDenaro(prelievo)){
                    cout << "Prelievo avvenuto con successo" << endl;
                    cout << "Il suo credito adesso è di " << myBankAccount->getSaldo() << endl;
                }
                else{
                    cout << "Credito insufficiente" << endl;
                    cout << "Il suo credito è di " << myBankAccount->getSaldo() << endl;
                }
                break;
            case 2:
                cout << "Inserire il denaro che vuole depositare sul proprio conto corrente" << endl;
                result = true;
                while(result){
                    cout << "Premere 1 se ha finito di depositare altrimenti prema 2 per annullare il deposito" << endl;
                    cin >> switch2;
                    switch (switch2){
                        case 1:
                            d = rand() % 1000000;
                            deposito = (float)d/100;
                            myBankAccount->DepositaDenaro(deposito);
                            cout << "Il suo deposito di " << deposito << " è andato a buon fine" <<endl;
                            cout << "Il suo credito adesso è di " << myBankAccount->getSaldo() << endl;
                            result = false;
                            break;
                        case 2:
                            cout << "Ha annullato la sua operazione di deposito" <<endl;
                            result = false;
                            break;
                        default:
                            cout << "Ha inserito un valore associato a nessuna operazione " <<endl;
                            break;
                    }
                }
                break;
            case 3:
                result=true;
                while(result){
                    cout << "Premere 1 se vuole inviare un bonifico ad una persona fisica, Altrimenti prema 2" << endl;
                    cin >> switch3;
                    switch (switch3){
                    case 1:
                        cout << "Inserire il nome e cognome della persona a cui fare il bonifico " << endl;
                        cout << "Inserire il nome" << endl;
                        cin >> nomeInvio;
                        cout << "Inserire il cognome" << endl;
                        cin >> cognomeInvio;
                        trovato = false;
                        iter = lstConti.find(make_pair(nomeInvio, cognomeInvio));
                        correctInsert=false;
                        if(iter != lstConti.end()){
                            while(correctInsert){
                                cout << "Inserire il valore del denaro che vuole inviare, inserire valore 0 se si vuole annullare il bonifico " << endl;
                                cin >> invio;
                                if(invio >= 0)
                                    correctInsert=true;
                            }
                            if(invio > 0 && myBankAccount->InviaDenaro(invio, iter->second)) {
                                cout << "Bonifico avvenuto con successo " << endl;
                                cout << "Hai inviato " << invio <<" euro addesso il tuo credito è di " << myBankAccount->getSaldo() << endl;
                            }
                            else if(invio == 0){
                                cout << "Operazione annullata " << endl;
                            }
                            else if(!myBankAccount->InviaDenaro(invio, iter->second)){
                                cout << "Credito insufficente, il tuo credito è di " << myBankAccount->getSaldo() << endl;
                            }
                        }
                        else{
                            cout << "Nessun conto corrente con quel nome trovato" << endl;
                        }
                        result = false;
                        break;
                    case 2:

                        result = false;
                        break;
                    default:
                        cout << "Ha inserito un valore associato a nessuna operazione " <<endl;
                        break;
                    }
                }
                break;
            default:
                cout << "Ha inserito un valore associato a nessuna operazione " << endl;
                break;
        }
    }

    return 0;
}