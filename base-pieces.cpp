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

void base::addpieces(std::string tprix, std::string tfabricant,std::string tfournisseur,std::string tname,std::string treference,std::string tcommentaire)
{
       time_t now = time(0);
       tm *ltm = localtime(&now);
    pieces p;
    std::string t="";
    if(basep.capacity() >= basep.size())
    {
        basep.reserve(100);
    }
    basep.push_back(p);
    basep.back().modifierpiece(indexpieces,std::atoi(tprix.data()),0,  tfabricant ,tname , treference, tcommentaire,1900 + ltm->tm_year,1 + ltm->tm_mon,ltm->tm_mday,tfournisseur,t,t,t,t,t,t,t,t );
    modif = true;
    trace a("pieces",std::to_string(indexpieces),"new","","","",basep.back().date().text());
    m_tracing.add(a);
    indexpieces++;

}

void base::modifierpiece(int num ,int key ,std::string tprix, std::string tfabricant,std::string tname,std::string treference,std::string tcommentaire, std::string tfour1,std::string tfour2, std::string tfour3,std::string tdoc,std::string tplan, std::string tphoto,std::string templacement, std::string tadresse, std::string tcategorie,std::string tdate,std::string tqty)
{
    if(basep[num].key() == key)
    {
        trace a("","","","","","","");
        std::string temp_trace="";
        QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
        int qty=0,prix=0;
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
                if(std::atoi(elements[2].data()) != basep[num].date().annee() | std::atoi(elements[1].data()) != basep[num].date().mois() | std::atoi(elements[0].data()) != basep[num].date().jour())
                {
                    temp_trace = elements[0] + "-" + elements[1] + "-" + elements[2];
                    a.set("pieces",std::to_string(key),"mise a jour","date",basep[num].date().text(), temp_trace,aujourdui.toStdString());
                   m_tracing.add(a);
                }
            basep[num].setdate(std::atoi(elements[2].data()),std::atoi(elements[1].data()),std::atoi(elements[0].data()));
            }

        if(std::atoi(tqty.data()) != basep[num].qty() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","quantite",std::to_string(basep[num].qty()), tqty.data(),aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setqty(std::atoi(tqty.data()));

        if(std::atoi(tprix.data()) != basep[num].prix() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","prix",std::to_string(basep[num].prix()), tprix.data(),aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setprix(std::atoi(tprix.data()));

        if(templacement != basep[num].emplacement() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","emplacement",basep[num].emplacement(), templacement,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setemplacement(templacement);

        if(tadresse != basep[num].adresse() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","adresse",basep[num].adresse(),tadresse,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setadresse(tadresse);

        if(tcategorie != basep[num].categorie() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","categorie",basep[num].categorie(), tcategorie,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setcategorie(tcategorie);

        if(tfour1 != basep[num].fournisseur1() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","fournisseur 1",basep[num].fournisseur1(), tfour1,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setfournisseur1(tfour1) ;

        if(tfour2 != basep[num].fournisseur2() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","fournisseur 2",basep[num].fournisseur2(),tfour2,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setfournisseur2(tfour2) ;

        if(tfour3 != basep[num].fournisseur3() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","fournisseur 3",basep[num].fournisseur3(), tfour3,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setfournisseur3(tfour3) ;

        if(tdoc != basep[num].liendoc() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","lien doc",basep[num].liendoc(), tdoc,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setliendoc(tdoc) ;

        if(tplan != basep[num].lienplan() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","lien plan",basep[num].lienplan(), tplan,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setlienplan(tplan) ;

        if(tphoto != basep[num].lienphoto() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","lien photo",basep[num].lienphoto(), tphoto,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setlienphoto(tphoto) ;

        if(tfabricant != basep[num].fabricant() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","fabricant",basep[num].fabricant(), tfabricant,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setfabricant(tfabricant);

        if(tname != basep[num].name() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","nom",basep[num].name(), tname,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setname(tname);

        if(treference != basep[num].reference() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","reference",basep[num].reference(), treference,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setreference(treference);

        if(tcommentaire != basep[num].commentaire() )
        {
            a.set("pieces",std::to_string(key),"mise a jour","commentaire",basep[num].commentaire(), tcommentaire ,aujourdui.toStdString());
           m_tracing.add(a);
        }
        basep[num].setcommentaire(tcommentaire);
        modif = true;
    }
}

int base::nbpieces()
{
  return basep.size();
}

std::string base::pieces_fabricant(int num) const
{
return basep[num].fabricant();
}

std::string base::pieces_key(int num) const
{
return std::to_string(basep[num].key());
}

std::string base::pieces_prix(int num) const
{
return std::to_string(basep[num].prix());
}

std::string base::pieces_reference(int num) const
{
return basep[num].reference();
}

std::string base::pieces_nom(int num) const
{
return basep[num].name();
}

std::string base::pieces_commentaire(int num) const
{
return basep[num].commentaire();
}

std::string base::pieces_date(int num) const
{
    return basep[num].date().text();
}

std::string base::pieces_qty(int num) const
{
return std::to_string(basep[num].qty());
}

std::string base::pieces_cout(int num) const
{
return std::to_string(basep[num].qty() * basep[num].prix());
}

std::string base::pieces_four1(int num) const
{
return basep[num].fournisseur1();
}

std::string base::pieces_four2(int num) const
{
return basep[num].fournisseur2();
}

std::string base::pieces_four3(int num) const
{
return basep[num].fournisseur3();
}

std::string base::pieces_emplacement(int num) const
{
return basep[num].emplacement();
}

std::string base::pieces_adresse(int num) const
{
return basep[num].adresse();
}

std::string base::pieces_categorie(int num) const
{
return basep[num].categorie();
}

std::string base::pieces_liendoc(int num) const
{
return basep[num].liendoc();
}

std::string base::pieces_lienplan(int num) const
{
return basep[num].lienplan();
}

std::string base::pieces_lienphoto(int num) const
{
return basep[num].lienphoto();
}

int base::getpiece(int num_key)
{
    for(uint i=0; i< basep.size();i++)
    {
       if(basep[i].key() == num_key )
       {
           return i;
       }
    }
    return -1;
}

int base::pieces_check_date(int num,std::string a,std::string b)
{
    return basep[num].date().comparedate(a,b);
}
