#include "machine.h"
#include <sstream>

machine::machine()
{
    m_key=0;
     pieces.clear();
     d.set(2018,1,1);
    m_fabricant="";
     m_name="";
     m_serial="";
     m_commentaire="";
     m_liendoc1="";
     m_lienplan1="";
     m_lienphoto1="";
     m_liendoc2="";
     m_lienplan2="";
     m_lienphoto2="";
     m_liendoc3="";
     m_lienplan3="";
     m_lienphoto3="";
     m_liendoc4="";
    m_lienplan4="";
     m_lienphoto4="";
     m_atelier="";
    m_zone="";
     m_groupe="";
}


int machine::key() const
{
return m_key;
}

void machine::clearpieces()
{
    pieces.clear();
}

std::string machine::fabricant() const
{
return m_fabricant;
}

std::string machine::name() const
{
return m_name;
}

std::string machine::atelier() const
{
return m_atelier;
}

std::string machine::reference() const
{
 return m_serial;
}

std::string machine::commentaire() const
{
return m_commentaire;
}

std::string machine::liendoc1() const
{
    return m_liendoc1;
}

std::string machine::lienplan1() const
{
    return m_lienplan1;
}

std::string machine::lienphoto1() const
{
    return m_lienphoto1;
}

std::string machine::liendoc2() const
{
    return m_liendoc2;
}

std::string machine::lienplan2() const
{
    return m_lienplan2;
}

std::string machine::lienphoto2() const
{
    return m_lienphoto2;
}

std::string machine::liendoc3() const
{
    return m_liendoc3;
}

std::string machine::lienplan3() const
{
    return m_lienplan3;
}

std::string machine::lienphoto3() const
{
    return m_lienphoto3;
}

std::string machine::liendoc4() const
{
    return m_liendoc4;
}

std::string machine::lienplan4() const
{
    return m_lienplan4;
}

std::string machine::lienphoto4() const
{
   return m_lienphoto4;
}

datee machine::date()const
{
return d;
}

void machine::getpieces(std::vector<int> &tab)
{
tab = pieces;
}

void machine::setliendoc1(std::string f)
{
    m_liendoc1 = f;
}

void machine::setatelier(std::string f)
{
    m_atelier = f;
}

void machine::setlienplan1(std::string f)
{
    m_lienplan1 = f;
}

void machine::setlienphoto1(std::string f)
{
    m_lienphoto1 = f;
}

void machine::setliendoc2(std::string f)
{
    m_liendoc2 = f;
}

void machine::setlienplan2(std::string f)
{
    m_lienplan2 = f;
}

void machine::setlienphoto2(std::string f)
{
    m_lienphoto2 = f;
}

void machine::setliendoc3(std::string f)
{
    m_liendoc3 = f;
}

void machine::setlienplan3(std::string f)
{
    m_lienplan3 = f;
}

void machine::setlienphoto3(std::string f)
{
    m_lienphoto3 = f;
}

void machine::setliendoc4(std::string f)
{
    m_liendoc4 = f;
}

void machine::setlienplan4(std::string f)
{
  m_lienplan4 = f;
}

void machine::setlienphoto4(std::string f)
{
m_lienphoto4 = f;
}

void machine::setdate(int y , int m, int  j)
{
 d.set(y,m,j);
}

void machine::setdate(std::string f)
{
    std::stringstream ss;
    std::string sousChaine;
    std::vector<std::string> elements;
    ss.clear();
    ss << f;
    elements.clear();
    while (getline(ss, sousChaine,'-'))
    {
    elements.push_back(sousChaine);
    }
    if(elements.size() == 3)
        {
        d.set(std::atoi(elements[2].data()),std::atoi(elements[1].data()),std::atoi(elements[0].data()));
        }
}

void machine::setkey(int key)
{
  m_key = key;
}

void machine::addpiece(int key)
{
  pieces.push_back(key);
}

void machine::delpiece(int key)
{
    int x = -1;

    for(uint i=0; i < pieces.size(); i++)
    {
        if(key == pieces[i])
        {
            x = i;
        }
    }
    if(x > -1)
    {
        pieces.erase(pieces.begin()+x);
    }

}

void machine::setfabricant(std::string fab)
{
   m_fabricant = fab;
}

void machine::setname(std::string name)
{
  m_name = name;
}

void machine::setreference(std::string ref)
{
  m_serial = ref;

}

void machine::setcommentaire(std::string comm)
{
  m_commentaire = comm;
}
