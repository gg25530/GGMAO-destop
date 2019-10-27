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

void base::addfournisseur(std::string f)
{
    fournisseurs four;
    four.setname(f);
     m_fournisseurs.push_back(four);
     QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
     trace a("fournisseur",f,"new","","","",aujourdui.toStdString());
     m_tracing.add(a);
     modif = true;

}

void base::supprfournisseur(std::string f)
{
    std::vector <fournisseurs> tab;
    tab.clear();
    for (uint i = 0;i < m_fournisseurs.size();i++)
    {
        if(m_fournisseurs[i].name() != f) tab.push_back(m_fournisseurs[i]);

    }
    m_fournisseurs.clear();
    for (uint i = 0;i < tab.size();i++)
    {
        m_fournisseurs.push_back( tab[i]);

    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("fournisseur",f,"suppr","","","",aujourdui.toStdString());
    m_tracing.add(a);
     modif = true;
}

void base::getfournisseur(fournisseurs & four, std::string name)
 {
     for(uint i=0;i < m_fournisseurs.size(); i++)
     {
        if(m_fournisseurs[i].name() == name)
        {
            four = m_fournisseurs[i];
        }
     }
 }

void base::setfournisseur(fournisseurs & four)
 {
     for(uint i=0;i < m_fournisseurs.size(); i++)
     {
        if(m_fournisseurs[i].name() == four.name())
        {
            m_fournisseurs[i] = four;
        }
     }
 }

int base::nbfournisseurs()
{
  return m_fournisseurs.size();
}

void base::getlistfournisseurs(std::vector<std::string> &four)
{

    four.clear();
    for(int b=0; b < m_fournisseurs.size(); b++)
    {
        four.push_back(m_fournisseurs[b].name());

    }

}
