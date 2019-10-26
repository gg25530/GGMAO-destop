#include "bt.h"
#include <sstream>
#include <ctime>

bt::bt()
{
     m_key=0;
     m_time=0.0f;
     pieces.clear();
     d.set(2018,1,1);
    m_machine="";
     m_tech="";
     m_type="";
    m_commentaire="";
    m_atelier="";
    m_zone="";
     m_groupe="";
     m_photo1="";
     m_photo2="";
     m_photo3="";
     m_photo4="";
  m_lu=false;
}

bt::bt(int key, float time, std::vector<int> &p, datee dd, std::string machine, std::string tech,  std::string type, std::string commentaire, std::string atelier, std::string zone, std::string groupe, std::string photo1="",std::string photo2="",std::string photo3="",std::string photo4="")
{
    m_key=key;
    m_time=time;
    pieces=p;
    d=dd;
   m_machine=machine;
    m_tech=tech;
    m_type=type;
   m_commentaire=commentaire;
   m_atelier=atelier;
   m_zone=zone;
    m_groupe=groupe;
    m_photo1=photo1;
    m_photo2=photo2;
    m_photo3=photo3;
    m_photo4=photo4;
    m_lu=false;
}

void bt::clearpieces()
{
    pieces.clear();
}

int bt::key() const
{
 return m_key;
}

std::string bt::skey() const
{
    std::ostringstream ss;
    ss << m_key;
    return ss.str();
}

std::string bt::slu() const
{
    if(m_lu)
    {
       return "oui";
    }
    else
    {
        return "non";
    }
}

std::string bt::tech() const
{
return m_tech;
}


std::string bt::machine() const
{
return m_machine;
}


std::string bt::type() const
{
return m_type;
}


std::string bt::atelier() const
{
return m_atelier;
}


std::string bt::commentaire() const
{
return m_commentaire;
}


std::string bt::zone() const
{
return m_zone;
}


std::string bt::groupe() const
{
return m_groupe;
}

std::string bt::photo1() const
{
return m_photo1;
}

std::string bt::photo2() const
{
return m_photo2;
}
std::string bt::photo3() const
{
return m_photo3;
}
std::string bt::photo4() const
{
return m_photo4;
}

datee bt::date()const
{
return d;
}


bool bt::lu() const
{
return m_lu;
}


std::string bt::time() const
{


return std::to_string(m_time);
}


void bt::getpieces(std::vector<int> &tab)
{
tab = pieces;
}


void bt::settech(std::string f)
{
m_tech = f;
}


void bt::setmachine(std::string f)
{
m_machine = f;
}


void bt::settype(std::string f)
{
m_type = f;
}


void bt::setatelier(std::string f)
{
m_atelier = f;
}


void bt::setzone(std::string f)
{
m_zone = f;
}


void bt::setgroupe(std::string f)
{
m_groupe = f;
}

void bt::setphoto1(std::string f)
{
m_photo1 = f;
}

void bt::setphoto2(std::string f)
{
m_photo2 = f;
}

void bt::setphoto3(std::string f)
{
m_photo3 = f;
}

void bt::setphoto4(std::string f)
{
m_photo4 = f;
}

void bt::setdate(int y , int m, int  j)
{
d.set(y,m,j);
}

void bt::setdate(std::string f)
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

void bt::setkey(int key)
{
m_key = key;
}

void bt::setlu(std::string lu)
{
   if(lu == "1" || lu == "true")
   {
       m_lu =true;
   }
   else
   {
       m_lu =false;
   }
}

void bt::settime(std::string time)
{
    m_time = std::atof(time.c_str());
}

void bt::addpiece(int key)
{
pieces.push_back(key);
}


void bt::delpiece(int key)
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


void bt::setcommentaire(std::string comm)
{
m_commentaire = comm;
}



