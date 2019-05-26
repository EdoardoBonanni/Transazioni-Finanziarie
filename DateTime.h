//
// Created by edoardo on 23/05/19.
//

#ifndef TRANSAZIONIFINANZIARIE_DATETIME_H
#define TRANSAZIONIFINANZIARIE_DATETIME_H


#include "Date.h"

class DateTime : public Date {
public:
    DateTime(int g, int mese, int a, int o, int min, int s, bool isBissextile);
    ~DateTime();

    DateTime& operator=(DateTime& that);
    bool operator==(const DateTime &dt);
    bool operator!=(const DateTime &dt);

    int getOra() const;
    int getMinuto() const;
    int getSecondo() const;

    void setOra(int ora);
    void setMinuto(int minuto);
    void setSecondo(int secondo);

private:
    bool checkOra(int o, int m, int s);
    int ora;
    int minuto;
    int secondo;
};


#endif //TRANSAZIONIFINANZIARIE_DATETIME_H
