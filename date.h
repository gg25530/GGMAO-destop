#ifndef DATE_H
#define DATE_H
#include <iostream>

class datee
{
public:
    datee();
    datee(int y,int m, int j);
    datee(datee const &);
    bool estegal(datee const& b);
    bool estplusvieux(datee const &);
    void set(int y, int m, int j);
    int mois()const ;
    int annee()const ;
    int jour()const ;
    int comparedate(std::string &a , std::string &b);  // -1 defaut //0 comprise entre date a et b // 1 plus vieux  // 2 plus recent
    bool estvalide();
    std::string text()const ;

    private:
    int m_annee;
    int m_mois;
    int m_jour;

};

#endif // DATE_H
