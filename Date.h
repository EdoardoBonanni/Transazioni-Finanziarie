//
// Created by edoardo on 29/08/18.
//

#ifndef TRANSAZIONIFINANZIARIE_DATE_H
#define TRANSAZIONIFINANZIARIE_DATE_H


class Date {
public:
    Date(){};
    Date(int g, int m, int a, bool isBissextile);

    ~Date();

    Date(const Date& that);
    Date& operator=(Date& that);
    bool operator==(const Date &d);
    bool operator!=(const Date &d);

    int getGiorno() const;
    int getMese() const;
    int getAnno() const;

    void setGiorno(int g);
    void setMese(int m);
    void setAnno(int a);

protected:
    bool checkData(int g, int m, int a, bool isBissextile);
    int giorno;
    int mese;
    int anno;
};


#endif //TRANSAZIONIFINANZIARIE_DATE_H
