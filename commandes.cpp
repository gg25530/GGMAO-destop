#include "commandes.h"
#include <sstream>

commandes::commandes()
{
     m_key=0;
     d.set(2018,1,1);
     m_fournisseur="";
     m_destinataire="";
     m_reference="";
     m_commentaire="";
     m_intprix = 0;
}

int commandes::key() const
{
    return m_key;
}


std::string commandes::fournisseur() const
{
    return m_fournisseur ;
}

std::string commandes::skey() const
{
    std::ostringstream ss;
    ss << m_key;
    return ss.str() ;
}

std::string commandes::destinataire() const
{
    return m_destinataire ;
}


std::string commandes::reference() const
{
    return m_reference;
}


std::string commandes::commentaire() const
{
    return m_commentaire;
}


std::string commandes::prix() const
{
    std::ostringstream ss;
    ss << m_intprix;
    return ss.str();
}


datee commandes::date()const
{
    return d;
}


void commandes::setfournisseur(std::string f)
{
    m_fournisseur = f;
}


void commandes::setdestinataire(std::string f)
{
    m_destinataire = f;
}


void commandes::setreference(std::string f)
{
    m_reference = f;
}


void commandes::setcommentaire(std::string f)
{
    m_commentaire = f;
}


void commandes::setprix(std::string f)
{
    m_intprix = std::atoi(f.c_str());
}


void commandes::setdate(int y , int m, int  j)
{
    d.set(y,m,j);
}

void commandes::setdate(std::string f)
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

void commandes::setkey(int key)
{
    m_key = key;
}














