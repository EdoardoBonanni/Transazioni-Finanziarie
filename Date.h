//
// Created by edoardo on 29/08/18.
//

#ifndef TRANSAZIONIFINANZIARIE_DATE_H
#define TRANSAZIONIFINANZIARIE_DATE_H


class Date {
public:
    Date(int g, int m, int a);
    int getGiorno() const;
    int getMese() const;
    int getAnno() const;
    void setGiorno(int g);
    void setMese(int m);
    void setAnno(int a);
private:
    int giorno;
    int mese;
    int anno;
};


#endif //TRANSAZIONIFINANZIARIE_DATE_H
