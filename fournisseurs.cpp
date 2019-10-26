#include "fournisseurs.h"
#include <sstream>
#include <ctime>

fournisseurs::fournisseurs()
{
      m_name="";
      m_num_bureau="";
      m_num_portable="";
      m_name_commercial="";
      m_commentaire="";
      m_num_client="";
      m_num_contrat="";
      m_adresse_mail_1="";
      m_adresse_mail_2="";
      m_adresse_postale="";

}

fournisseurs::fournisseurs(std::string name,std::string num_bureau,std::string num_portable,std::string name_commercial,std::string commentaire,std::string num_client,std::string num_contrat,std::string mail_1,std::string mail_2,std::string adresse_postale)

{
    m_name=name;
    m_num_bureau=num_bureau;
    m_num_portable=num_portable;
    m_name_commercial=name_commercial;
    m_commentaire=commentaire;
    m_num_client=num_client;
    m_num_contrat=num_contrat;
    m_adresse_mail_1=mail_1;
    m_adresse_mail_2=mail_2;
    m_adresse_postale=adresse_postale;

}

std::string fournisseurs::name() const
{
    return m_name;
}

std::string fournisseurs::num_bureau() const
{
    return m_num_bureau;
}

std::string fournisseurs::num_portable() const
{
    return m_num_portable;
}

std::string fournisseurs::name_commercial() const
{
    return m_name_commercial;
}

std::string fournisseurs::commentaire() const
{
    return m_commentaire;
}

std::string fournisseurs::num_client() const
{
    return m_num_client;
}

std::string fournisseurs::num_contrat() const
{
    return m_num_contrat;
}

std::string fournisseurs::mail_1() const
{
    return m_adresse_mail_1;
}

std::string fournisseurs::mail_2() const
{
    return m_adresse_mail_2;
}

std::string fournisseurs::adresse_postale() const
{
    return m_adresse_postale;
}


void fournisseurs::setname(std::string f)
{
    m_name = f;
}

void fournisseurs::setnum_bureau(std::string f)
{
    m_num_bureau = f;
}

void fournisseurs::setnum_portable(std::string f)
{
    m_num_portable = f;
}

void fournisseurs::setname_commercial(std::string f)
{
    m_name_commercial = f;
}

void fournisseurs::setcommentaire(std::string f)
{
    m_commentaire = f;
}

void fournisseurs::setnum_client(std::string f)
{
    m_num_client = f;
}

void fournisseurs::setnum_contrat(std::string f)
{
    m_num_contrat = f;
}

void fournisseurs::setmail_1(std::string f)
{
    m_adresse_mail_1 = f;
}

void fournisseurs::setmail_2(std::string f)
{
    m_adresse_mail_2 = f;
}
void fournisseurs::setadresse_postale(std::string f)
{
    m_adresse_postale = f;
}


