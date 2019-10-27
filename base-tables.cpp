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



void base::addtypetaf(std::string f)
{
    m_typetaf.push_back(f);
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("typetravail",f,"new","","","",aujourdui.toStdString());
    m_tracing.add(a);
    modif = true;

}

void base::adddestinataire(std::string f)
{
    m_destinataires.push_back(f);
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("destinataire",f,"new","","","",aujourdui.toStdString());
    m_tracing.add(a);
    modif = true;

}

void base::addatelier(std::string f)
{
     m_atelier.push_back(f);
     QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
     trace a("atelier",f,"new","","","",aujourdui.toStdString());
     m_tracing.add(a);
     modif = true;
}

void base::addtech(std::string f)
{
   m_tech.push_back(f);
   QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
   trace a("technicien",f,"new","","","",aujourdui.toStdString());
   m_tracing.add(a);
   modif = true;

}

void base::addcategorie(std::string f)
{
     m_categorie.push_back(f);
     QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
     trace a("categorie",f,"new","","","",aujourdui.toStdString());
     m_tracing.add(a);
     modif = true;

}

void base::addfabricant(std::string f)
{
     m_fabricants.push_back(f);
     QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
     trace a("fabricant",f,"new","","","",aujourdui.toStdString());
     m_tracing.add(a);
     modif = true;

}

void base::supprfabricant(std::string f)
{
    std::vector <std::string> tab;
    tab.clear();
    for (uint i = 0;i < m_fabricants.size();i++)
    {
        if(m_fabricants[i] != f) tab.push_back(m_fabricants[i]);

    }
    m_fabricants.clear();
    for (uint i = 0;i < tab.size();i++)
    {
        m_fabricants.push_back( tab[i]);

    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("fabricant",f,"suppr","","","",aujourdui.toStdString());
    m_tracing.add(a);
     modif = true;
}

void base::supprtech(std::string f)
{
    std::cout << f << m_tech.size() << std::endl;
    std::vector <std::string> tab;
    tab.clear();
    for (uint i = 0;i < m_tech.size();i++)
    {
        if(m_tech[i] != f) tab.push_back(m_tech[i]);

    }
    m_tech.clear();
    for (uint i = 0;i < tab.size();i++)
    {
        m_tech.push_back( tab[i]);

    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("technicien",f,"suppr","","","",aujourdui.toStdString());
    m_tracing.add(a);
     modif = true;

}

void base::supprcategorie(std::string f)
{
    std::vector <std::string> tab;
    tab.clear();
    for (uint i = 0;i < m_categorie.size();i++)
    {
        if(m_categorie[i] != f) tab.push_back(m_categorie[i]);

    }
    m_categorie.clear();
    for (uint i = 0;i < tab.size();i++)
    {
        m_categorie.push_back( tab[i]);

    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("categorie",f,"suppr","","","",aujourdui.toStdString());
    m_tracing.add(a);
     modif = true;
}

void base::suppratelier(std::string f)
{
    std::vector <std::string> tab;
    tab.clear();
    for (uint i = 0;i < m_atelier.size();i++)
    {
        if(m_atelier[i] != f) tab.push_back(m_atelier[i]);

    }
    m_atelier.clear();
    for (uint i = 0;i < tab.size();i++)
    {
        m_atelier.push_back( tab[i]);

    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("atelier",f,"suppr","","","",aujourdui.toStdString());
    m_tracing.add(a);
     modif = true;
}

void base::supprdestinataire(std::string f)
{
    std::vector <std::string> tab;
    tab.clear();
    for (uint i = 0;i < m_destinataires.size();i++)
    {
        if(m_destinataires[i] != f) tab.push_back(m_destinataires[i]);

    }
    m_destinataires.clear();
    for (uint i = 0;i < tab.size();i++)
    {
        m_destinataires.push_back( tab[i]);

    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("destinataire",std::to_string(indexmachine),"new","","","",aujourdui.toStdString());
    m_tracing.add(a);
     modif = true;
}

void base::supprtypetaf(std::string f)
{
    std::vector <std::string> tab;
    tab.clear();
    for (uint i = 0;i < m_typetaf.size();i++)
    {
        if(m_typetaf[i] != f) tab.push_back(m_typetaf[i]);

    }
    m_typetaf.clear();
    for (uint i = 0;i < tab.size();i++)
    {
        m_typetaf.push_back( tab[i]);

    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("typetravail",f,"suppr","","","",aujourdui.toStdString());
    m_tracing.add(a);
     modif = true;

}

int base::nbfabricants()
{
  return m_fabricants.size();
}

int base::nbateliers()
{
  return m_atelier.size();
}

int base::nbcategories()
{
  return m_categorie.size();
}

int base::nbtypetaf()
{
  return m_typetaf.size();
}

int base::nbdestinataires()
{
  return m_destinataires.size();
}

int base::nbtech()
{
  return m_tech.size();
}

void base::getlisttech(std::vector<std::string> &tech)
{
   tech = m_tech;
}

void base::getlistdestinataires(std::vector<std::string> &dest)
{
   dest = m_destinataires;
}

void base::getlistcategories(std::vector<std::string> &cat)
{
   cat = m_categorie;
}

void base::getlistfabricants(std::vector<std::string> &fab)
{
    fab = m_fabricants;
}

void base::getlisttypetaf(std::vector<std::string> &typetaf)
{
    typetaf = m_typetaf;
}

void base::getlistatelier(std::vector<std::string> &atelier)
{
    atelier = m_atelier;
}



