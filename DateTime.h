//
// Created by edoardo on 23/05/19.
//

#ifndef TRANSAZIONIFINANZIARIE_DATETIME_H
#define TRANSAZIONIFINANZIARIE_DATETIME_H


#include "Date.h"

class DateTime : public Date {
public:
    DateTime(){}
    DateTime(int g, int mese, int a, int o, int min, int s, bool isBissextile);
    ~DateTime();

    DateTime(const DateTime& that);
    DateTime& operator=(DateTime& that);
    bool operator==(const DateTime &dt);
    bool operator!=(const DateTime &dt);

    int getOra() const;
    int getMinuto() const;
    int getSecondo() const;

    void setOra(const int o, bool isBissextile);
    void setMinuto(const int min, bool isBissextile);
    void setSecondo(const int s, bool isBissextile);
    virtual void setGiorno(const int g, bool isBissextile) override;
    virtual void setMese(const int mes, bool isBissextile) override;
    virtual void setAnno(const int a, bool isBissextile) override;

private:
    bool checkOra(int o, int m, int s);
    bool checkDateTime(int o, int min, int s, int g, int mes, int a, bool isBissextile);
    int ora;
    int minuto;
    int secondo;
};


#endif //TRANSAZIONIFINANZIARIE_DATETIME_H
