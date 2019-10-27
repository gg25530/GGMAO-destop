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

void base::addbt(std::string tatelier,std::string tmachine,std::string type, std::string ttech,std::string tdate,std::string ttime,std::string tcommentaire,std::string lien_photo1,std::string lien_photo2,std::string lien_photo3,std::string lien_photo4)
{
    bt bt1;
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
        bt1.setdate(std::atoi(elements[2].data()),std::atoi(elements[1].data()),std::atoi(elements[0].data()));
        }
    bt1.setkey(indexbt);
    bt1.setatelier(tatelier);
    bt1.setmachine(tmachine);
    bt1.settype(type);
    bt1.settech(ttech);
    bt1.settime(ttime);
    bt1.setcommentaire(tcommentaire);
    bt1.setphoto1(lien_photo1);
    bt1.setphoto2(lien_photo2);
    bt1.setphoto3(lien_photo3);
    bt1.setphoto4(lien_photo4);
    bts.push_back(bt1);
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("bt",std::to_string(indexbt),"new","","","",aujourdui.toStdString());
    m_tracing.add(a);
    indexbt++;
    modif = true;
}

int base::nbbts()
{
  return bts.size();
}

std::string base::bt_atelier(int num) const
{
    return bts[num].atelier();

}

std::string base::bt_machine(int num) const
{
    return bts[num].machine();

}

int base::index_bts()
{
    return indexbt;
}

std::string base::bt_temps(int num) const
{
    return bts[num].time();

}

std::string base::bt_type(int num) const
{
    return bts[num].type();

}

std::string base::bt_tech(int num) const
{
    return bts[num].tech();

}

std::string base::bt_commentaire(int num) const
{
    return bts[num].commentaire();

}

std::string base::bt_date(int num) const
{
    return bts[num].date().text();

}

std::string base::bt_slu(int num) const
{
    return bts[num].slu();

}

std::string base::bt_skey(int num) const
{
    return bts[num].skey();

}

int base::bts_annee(int num) const
{
    return bts[num].date().annee();
}

int base::bts_mois(int num) const
{
    return bts[num].date().mois();
}

int base::bt_check_date(int num,std::string a,std::string b)
{
    return bts[num].date().comparedate(a,b);
}


void base::setdate_bt_param(std::string f)
{
    date_bt = f;
}

std::string base::getdate_bt_param()
{
    return date_bt;
}

void base::get_bt(bt & bon,int num)
{
    bon = bts[num];
}

void base::set_bt(bt & bon,int num)
{
    bts[num] = bon;
    modif = true;
}

int base::findbt(int num)
{
    for(uint i=0; i < bts.size(); i++)
    {
        if(bts[i].key() == num) return i;
    }


return -1;
}
