#include <iostream>
#include <map>
#include "Date.h"
#include "Utenza.h"
#include "ContoCorrente.h"

using namespace std;
int main() {
    //situazione contocorrente
    Utenza* poste = new Utenza("Poste italiane", "via togliatti", 2, "firenze");
    ContoCorrente* contoposte = new ContoCorrente(poste, 1000000);
    map<ContoCorrente*, pair<string,string>> lstConti;
    pair<ContoCorrente*, pair<string,string>> pair1 = {contoposte, {poste->getNome(), " " } };
    lstConti.insert(pair1);
    Utenza* person1 = new Utenza("Pippo", "Pluto", 'm', 7, 3, 1990);
    ContoCorrente* conto1 = new ContoCorrente(person1);
    pair<ContoCorrente*, pair<string,string>> pair2 = {conto1, {person1->getNome(), person1->getCognome() } };
    lstConti.insert(pair2);
    /*string nome, cognome;
    char sesso;
    int gn, mn, an;*/
    pair<string,string> pairn;
    string searchName, nomeInvio, cognomeInvio;
    float deposito, invio, prelievo;
    bool result, trovato, correctInsert;
    int switch1, switch2, switch3, d;
    /*cout << "Inserisci i tuoi dati" << endl;
    cout << "Inserisci il tuo nome" << endl;
    cin >> nome;
    cout << "Inserisci il tuo cognome" << endl;
    cin >> cognome;
    cout << "Inserisci il tuo sesso" << endl;
    cin >> sesso;
    cout << "Inserisci il tuo giorno di nascita" << endl;
    cin >> gn;
    cout << "Inserisci il tuo mese di nascita" << endl;
    cin >> mn;
    cout << "Inserisci il tuo anno di nascita" << endl;
    cin >> an;
    Utenza* me = new Utenza(nome, cognome, sesso, gn, mn, an);*/
    Utenza* me = new Utenza("Edoardo", "Bonanni", 'm', 2, 3, 1998);
    ContoCorrente* myBankAccount = new ContoCorrente(me);
    pair<ContoCorrente*, pair<string,string>> pair3 = {myBankAccount, {me->getNome(), me->getCognome() } };
    lstConti.insert(pair3);
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
                        for(auto i : lstConti){
                            if(i.second.first == nomeInvio && i.second.second == cognomeInvio){
                                //puntatore al contocorrente trovato
                                trovato = true;
                                break;
                            }
                        }
                        correctInsert=false;
                        if(trovato){
                            while(correctInsert){
                                cout << "Inserire il valore del denaro che vuole inviare, inserire valore 0 se si vuole annullare il bonifico " << endl;
                                cin >> invio;
                                if(invio >= 0)
                                    correctInsert=true;
                            }
                            if(invio > 0 && myBankAccount->InviaDenaro(invio, //puntatore al contocorrente trovato)) {
                                cout << "Inserire il valore del denaro che vuole inviare, inserire valore 0 se si vuole annullare il bonifico " << endl;
                                cin >> invio;;
                            }
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
    }/*
    cout << "Inserisci il denaro da inviare a " << poste->getNome() << endl;
    cin >> invio;
    result = myBankAccount->InviaDenaro(invio, contoposte);
    if(result)
        cout << "Transazione avvenuta con successo" << endl;
    else
        cout << "Errore nella transazione " << endl;
    cout << "Il tuo saldo rimanente e' " << myBankAccount->getSaldo();*/
    return 0;
}