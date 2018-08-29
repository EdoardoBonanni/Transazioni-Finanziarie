#include <iostream>
#include "Date.h"
#include "Utenza.h"
#include "ContoCorrente.h"

using namespace std;
int main() {
    //situazione contocorrente
    Utenza* poste = new Utenza("Poste italiane", "via togliatti", 2, "firenze");
    ContoCorrente* contoposte = new ContoCorrente(poste, 1000000);
    string nome, cognome;
    char sesso;
    int gn, mn, an;
    float deposito, invio;
    bool result;
    cout << "Inserisci i tuoi dati" << endl;
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
    Utenza* me = new Utenza(nome, cognome, sesso, gn, mn, an);
    ContoCorrente* myBankAccount = new ContoCorrente(me);
    cout << "Quanto denaro vuoi depositare sul tuo conto bancario?" << endl;
    cin >> deposito;
    myBankAccount->depositaDenaro(deposito);
    cout << "Inserisci il denaro da inviare a " << poste->getNome() << endl;
    cin >> invio;
    result = myBankAccount->InviaDenaro(invio, contoposte);
    if(result)
        cout << "Transazione avvenuta con successo" << endl;
    else
        cout << "Errore nella transazione " << endl;
    cout << "Il tuo saldo rimanente e' " << myBankAccount->getSaldo();
    return 0;
}