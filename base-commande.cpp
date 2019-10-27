#include "base.h"
#include "pieces.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "machine.h"
#include "bt.h"
#include <ctime>
#include <QStringList>
#include <QDate>
#include "commandes.h"
#include "traceur.h"
#include "trace.h"
#include "fournisseurs.h"
#include <QtWidgets>
#include <QHostInfo>

void base::addcommande(std::string tfournisseur,std::string treference,std::string tprix, std::string tdestinataire,std::string tdate,std::string tcommentaire)
{
    commandes comm;
    std::stringstream ss;
    std::string sousChaine;
    std::vector<std::string> elements;
    ss.clear();
    ss << tdate;
    elements.clear();
    while (getline(ss, sousChaine,'-'))
    {
    elements.push_back(sousChaine);
    }
    if(elements.size() == 3)
        {
        comm.setdate(std::atoi(elements[2].data()),std::atoi(elements[1].data()),std::atoi(elements[0].data()));
        }
    comm.setkey(indexcommandes);
    comm.setfournisseur(tfournisseur);
    comm.setdestinataire(tdestinataire);
    comm.setprix(tprix);
    comm.setreference(treference);
    comm.setcommentaire(tcommentaire);
    m_commandes.push_back(comm);
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("comande",std::to_string(indexcommandes),"new","","","",aujourdui.toStdString());
    m_tracing.add(a);
    indexcommandes++;
    modif = true;
}

int base::nbcommandes()
{
  return m_commandes.size();
}

std::string base::commande_fournisseur(int num) const
{
    return m_commandes[num].fournisseur();

}

std::string base::commande_reference(int num) const
{
    return m_commandes[num].reference();

}

std::string base::commande_prix(int num) const
{
    return m_commandes[num].prix();

}

int base::commande_prixint(int num) const
{
   return std::atoi(m_commandes[num].prix().c_str());
}

int base::commande_mois(int num) const
{
    return m_commandes[num].date().mois();
}

int base::commande_annee(int num) const
{
     return m_commandes[num].date().annee();
}

int base::commande_jour(int num) const
{
     return m_commandes[num].date().jour();
}

std::string base::commande_commentaire(int num) const
{
    return m_commandes[num].commentaire();

}

std::string base::commande_date(int num) const
{
    return m_commandes[num].date().text();

}

std::string base::commande_destinataire(int num) const
{
    return m_commandes[num].destinataire();

}

std::string base::commande_skey(int num) const
{
    return m_commandes[num].skey();

}

int base::commande_check_date(int num,std::string a,std::string b)
{
    return m_commandes[num].date().comparedate(a,b);
}

void base::setdate_commande_param(std::string f)
{
    date_commande = f;
}

std::string base::getdate_commande_param()
{
    return date_commande;
}

void base::get_commande(commandes & bon,int num)
{
    bon = m_commandes[num];
}

void base::set_commmande(commandes &bon, int num)
{
    m_commandes[num] = bon;
    modif = true;
}

int base::findcommande(int num)
{
    for(uint i=0; i < m_commandes.size(); i++)
    {
        if(m_commandes[i].key() == num) return i;
    }


return -1;
}
