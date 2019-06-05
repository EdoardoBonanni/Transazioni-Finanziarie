
#ifndef TRANSAZIONIFINANZIARIE_DATE_H
#define TRANSAZIONIFINANZIARIE_DATE_H


class Date {
public:
    Date(){};
    Date(int g, int m, int a, bool isBissextile);

    virtual ~Date();

    Date(const Date& that);
    Date& operator=(Date& that);
    bool operator==(const Date &d);
    bool operator!=(const Date &d);

    int getGiorno() const;
    int getMese() const;
    int getAnno() const;
    bool IsValid() const;

    virtual void setGiorno(const int g, bool isBissextile);
    virtual void setMese(const int m, bool isBissextile);
    virtual void setAnno(const int a, bool isBissextile);

protected:
    bool checkData(int g, int m, int a, bool isBissextile);
    int giorno;
    int mese;
    int anno;
    bool isValid;
};


#endif //TRANSAZIONIFINANZIARIE_DATE_H
