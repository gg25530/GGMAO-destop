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

void base::addmachine(std::string tatelier,std::string tzone,std::string tgroupe, std::string tfabricant,std::string tname,std::string treference,std::string tcommentaire,std::string tdate)
{
    machine mach;
    std::stringstream ss;
    std::string sousChaine;
    std::vector<std::string> elements;
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    ss.clear();
    ss << tdate;
    elements.clear();
    while (getline(ss, sousChaine,'-'))
    {
    elements.push_back(sousChaine);
    }
    if(elements.size() == 3)
        {
        mach.setdate(std::atoi(elements[2].data()),std::atoi(elements[1].data()),std::atoi(elements[0].data()));
        }
    mach.setkey(indexmachine);
    mach.setname(tname);
    mach.setatelier(tatelier);
    mach.setfabricant(tfabricant);
    mach.setreference(treference);
    mach.setcommentaire(tcommentaire);
    machines.push_back(mach);
    trace a("machine",tname,"new","","","",aujourdui.toStdString());
    m_tracing.add(a);
    indexmachine++;
    modif = true;
}

void base::suppr_piece_machine(int mach, int num)
{
    if(mach > -1)
    {
        machines[mach].delpiece(num);
    }
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    trace a("machine",std::to_string(num),"mise a jour","pieces","avec","",aujourdui.toStdString());
    m_tracing.add(a);
}

int base::nbmachines()
{
  return machines.size();
}

void base::getlistmachinesbt(std::vector<std::string> &bt,std::string machine)
{

}

void base::getlistmachinespieces(std::vector<int> &pieces,int machine)
{
     machines[machine].getpieces(pieces);
}

void base::getlistmachineplan(std::vector<std::string> &fichiers,int machine)
{
       if(machines[machine].lienplan1()!= "") fichiers.push_back(machines[machine].lienplan1());
       if(machines[machine].lienplan2()!= "") fichiers.push_back(machines[machine].lienplan2());
       if(machines[machine].lienplan3()!= "") fichiers.push_back(machines[machine].lienplan3());
       if(machines[machine].lienplan4()!= "") fichiers.push_back(machines[machine].lienplan4());
}

void base::getlistmachinedoc(std::vector<std::string> &fichiers,int machine)
{
    if(machines[machine].liendoc1()!= "") fichiers.push_back(machines[machine].liendoc1());
    if(machines[machine].liendoc2()!= "") fichiers.push_back(machines[machine].liendoc2());
    if(machines[machine].liendoc3()!= "") fichiers.push_back(machines[machine].liendoc3());
    if(machines[machine].liendoc4()!= "") fichiers.push_back(machines[machine].liendoc4());
}

void base::getlistmachinephoto(std::vector<std::string> &fichiers,int machine)
{
    if(machines[machine].lienphoto1()!= "") fichiers.push_back(machines[machine].lienphoto1());
    if(machines[machine].lienphoto2()!= "") fichiers.push_back(machines[machine].lienphoto2());
    if(machines[machine].lienphoto3()!= "") fichiers.push_back(machines[machine].lienphoto3());
    if(machines[machine].lienphoto4()!= "") fichiers.push_back(machines[machine].lienphoto4());
}

void base::getlistmachinereference(QLabel *f,int num)
{
    f->setText(machines[num].reference().c_str());
}

void base::getlistmachinedate(QLabel *f,int num)
{
    f->setText(machines[num].date().text().c_str());
}

void base::getlistmachinecommentaire(QLabel *f,int num)
{
    f->setText(machines[num].commentaire().c_str());
}

void base::getlistmachinefabricant(QLabel *f,int num)
{
    f->setText(machines[num].fabricant().c_str());
}

void base::getlistmachine(std::vector<std::string> &machine)
{
    machine.clear();
    for(uint i=0;i < machines.size(); i++)
    {
       machine.push_back(machines[i].name());
    }
}

void base::getlistmachineatelier(std::vector<std::string> &machine,std::string atelier)
{
    machine.clear();
    for(uint i=0;i < machines.size(); i++)
    {
      if(machines[i].atelier() == atelier) machine.push_back(machines[i].name());
    }
}

void base::getlistmachinespiece(std::vector<std::string> &machine,int num) // retourne liste machine utilisant la piece num = key piece
{
    std::vector <int> pieces;
    for(int a=0; a < machines.size(); a++)
    {
        pieces.clear();
       machines[a].getpieces(pieces);
        for(int b=0; b < pieces.size(); b++)
        {
            if(pieces[b] == num)
            {
                machine.push_back(machines[a].atelier() + " - " + machines[a].name());
            }
        }

    }


}

int base::findmachine(std::string mach)
{
    for(uint i=0;i < machines.size(); i++)
    {
      if(machines[i].name() == mach) return i;
    }
    return -1;
}

void base::machine_addpieces(std::vector<int> &pieces,int num_mach)
{
    if(num_mach > -1 && num_mach < machines.size())
    {
        bool find = false;
        std::vector<int> actuelles;
        actuelles.clear();
        machines[num_mach].getpieces(actuelles);
        for(uint i=0;i<pieces.size();i++)
        {
            find = false;
            for(uint j=0;j<actuelles.size();j++)
            {
                if(actuelles[j] == pieces[i]) find = true;
            }
            if(!find) machines[num_mach].addpiece(pieces[i]);
        }
        modif = true;

    }
}

void base::get_machine(machine & mach,int num)
{
    mach = machines[num];
}

void base::set_machine(machine & mach,int num)
{
    machines[num] = mach;
    modif = true;
}
