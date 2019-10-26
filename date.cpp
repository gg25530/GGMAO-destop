#include "date.h"
#include <iostream>
#include <sstream>
#include <vector>

datee::datee()
{
    m_annee = 2018;
    m_mois = 1;
    m_jour = 1;
}

datee::datee(int y,int m, int j)
{
    m_annee = y;
    m_mois = m;
    m_jour = j;
    if(!this->estvalide())
    {
        m_annee = 2018;
        m_mois = 1;
        m_jour = 1;
    }
}

datee::datee(datee const & b)
{
    m_annee = b.annee();
    m_mois = b.mois();
    m_jour = b.jour();
    if(!this->estvalide())
    {
        m_annee = 2018;
        m_mois = 1;
        m_jour = 1;
    }
}

bool datee::estegal(datee const& b)
{
    if(m_annee == b.annee() && m_mois == b.mois() && m_jour == b.jour())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool datee::estplusvieux(datee const & b)
{
    if(m_annee < b.annee() || (m_annee == b.annee() && m_mois < b.mois()) || (m_annee == b.annee() && m_mois == b.mois() && m_jour < b.jour() ))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void datee::set(int y, int m, int j)
{
    m_annee = y;
    m_mois = m;
    m_jour = j;
    if(!this->estvalide())
    {
        m_annee = 2018;
        m_mois = 1;
        m_jour = 1;
    }
}

int datee::mois()const
{
   return m_mois;
}

int datee::annee()const
{
     return m_annee;
}

int datee::jour()const
{
   return m_jour;
}

bool datee::estvalide()
{
    if(m_annee < 2049 && m_annee >1980 && m_mois >0 && m_mois < 13 && m_jour <32 && m_jour >0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string datee::text()const
{
    std::string t;
    t= std::to_string(m_jour);
    t+= "-";
    t+= std::to_string(m_mois);
    t+= "-";
    t+= std::to_string(m_annee);
    return t;
}

int datee::comparedate(std::string &a , std::string &b)  // -1 defaut //0 comprise entre date a et b // 1 plus vieux  // 2 plus recent
{
    int ya=0, yb=0,ma=0,mb=0,ja=0,jb=0, x=0,y=0,z=0;
    std::vector<std::string> elements;
    std::stringstream ss;
    std::string temp="";
    ss.clear();
    elements.clear();
    ss << a;
 while (getline(ss, temp,'-'))
 {
 elements.push_back(temp);
 }
 if(elements.size() != 3 )
 {
     return -1;
 }
 else
 {
     ya = std::atoi(elements[2].data());
     ma = std::atoi(elements[1].data());
     ja = std::atoi(elements[0].data());

 }
 ss.clear();
 elements.clear();
 ss << b;
while (getline(ss, temp,'-'))
{
elements.push_back(temp);
}
if(elements.size() != 3 )
{
    return -1;
}
else
{
    yb = std::atoi(elements[2].data());
    mb = std::atoi(elements[1].data());
    jb = std::atoi(elements[0].data());

}

 datee d(ya,ma,ja);
if(!d.estvalide()) return -1;
 d.set(yb,mb,jb);
 if(!d.estvalide()) return -1;

 x = ya * 365 + ma * 31 + ja;
 y = yb * 365 + mb * 31 + jb;
 z = m_annee * 365 + m_mois * 31 + m_jour;
 if(z < x )return 1;
 else if(z > x && z < y) return 0;
 else if(z == x ) return 0;
 else if(z == y) return 0;
 else if(z > y) return 2;
else return -1;
}
