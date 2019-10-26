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


base::base()
{
     basep.clear();
     machines.clear();
     bts.clear();
     m_commandes.clear();
     indexpieces=0;
     indexmachine=0;
     indexbt=0;
     indexcommandes=0;
     age.set(2018,1,1);
     corrompue = 0;  // 0= pas chargee  1 = corrompue au chargement  2 = chargement reussi
     modif = false;
      m_fabricants.clear();
      m_fournisseurs.clear();
      m_tech.clear();
      m_typetaf.clear();
      m_atelier.clear();
      m_destinataires.clear();
      m_categorie.clear();
      m_path = "";
      m_name ="";
}

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

int base::iscorrompue()
{
    return corrompue;
}

std::string base::path() const
{
    return m_path;
}

void base::setpath(std::string dossier)
{
    m_path = dossier;
    m_tracing.setpath(m_path);
}

std::string base::name() const
{
    return m_name;
}

void base::setname(std::string dossier)
{
    m_name = dossier;
}
void base::majbase()
{

std::string temp="";
    temp = m_path;
    temp += m_name;
    temp += ".ggm";

    std::ifstream flux(temp.c_str());
    int tableactuelle = 0;
    std::stringstream ss;
    std::string sousChaine;
    std::vector<std::string> elements;
    std::string delim = ";";
    pieces p;
    bt btnew;
    commandes commandenew;
    machine machinenew;
    fournisseurs fournisseurnew;
    std::string ligne="";

    if (flux)
    {

            ////////// ouverture fichier  ////////////////






        while (getline(flux, ligne))
        {



       if(ligne.substr(0,2) == "//"  )
       {
           tableactuelle ++;  // changement d'etape

       }
       else if(ligne.substr(0,2) == "/*"  )
       {

           // ne tient pas compte des commentaires dans le fichier
       }
       else if(ligne.substr(0,2) != "//" && ligne.substr(0,2) != "/*")
       {



           ///////////// recup des parametres generaux   //////////////
           if(tableactuelle==0)
           {

               ss.clear();
               ss << ligne;
               elements.clear();
               while (getline(ss, sousChaine,';'))
               {


               elements.push_back(sousChaine);
               }
               if(elements.size() ==7)
               {
                  age.set(std::atoi( elements[0].data()),std::atoi( elements[1].data()),std::atoi( elements[2].data()));
                  indexpieces = std::atoi( elements[3].data());
                  indexbt = std::atoi( elements[4].data());
                  indexmachine = std::atoi( elements[5].data());
                  indexcommandes = std::atoi( elements[6].data());

               }
               else
               {
                   corrompue = 1;
               }
           }
            /////////////////////////////////////// table pieces  /////
          else if(tableactuelle==1)
           {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {

            elements.push_back(sousChaine);
            }
            if(elements.size() ==19)
            {
                basep.push_back(p);
                basep.back().modifierpiece(std::atoi( elements[0].data() ),std::atoi( elements[1].data() ),std::atoi( elements[2].data() ),  elements[3].data() ,elements[4].data() , elements[5].data() , elements[6].data(),std::atoi( elements[7].data() ),std::atoi( elements[8].data() ),std::atoi( elements[9].data() ),elements[10].data(),elements[11].data(),elements[12].data(),elements[13].data(),elements[14].data(),elements[15].data(),elements[16].data(),elements[17].data(),elements[18].data() );
                if(basep.capacity() >= basep.size())
                {
                    basep.reserve(100);
                }
            }
            else
            {
                corrompue = 3;
            }
           }
            ////////////////////////////////////// table techs  //////
          else if(tableactuelle==2)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() ==1)
            {
             m_tech.push_back(elements[0].data());
            }
            else
            {
                corrompue = 4;
            }
          }
            ///////////////////////////////////// table fournisseurs ////
          else if(tableactuelle==3)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() ==10)
            {
                fournisseurnew.setname(elements[0].data());
                fournisseurnew.setname_commercial(elements[1].data());
                fournisseurnew.setnum_bureau(elements[2].data());
                fournisseurnew.setnum_client(elements[3].data());
                fournisseurnew.setnum_contrat(elements[4].data());
                fournisseurnew.setnum_portable(elements[5].data());
                fournisseurnew.setadresse_postale(elements[6].data());
                fournisseurnew.setmail_1(elements[7].data());
                fournisseurnew.setmail_2(elements[8].data());
                fournisseurnew.setcommentaire(elements[9].data());
             m_fournisseurs.push_back(fournisseurnew);
            }
            else
            {
                corrompue = 5;
            }
          }
            //////////////////////////////////// table fabricants  ////////
          else if(tableactuelle==4)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() ==1)
            {
             m_fabricants.push_back(elements[0].data());
            }
            else
            {
                corrompue = 6;
            }
          }
          //////////////////////////////////// table type de taf  ////////
          else if(tableactuelle==5)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() ==1)
            {
             m_typetaf.push_back(elements[0].data());
            }
            else
            {
                corrompue = 7;
            }
          }
          //////////////////////////////////// table ateliers  ////////
          else if(tableactuelle==6)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() ==1)
            {
             m_atelier.push_back(elements[0].data());
            }
            else
            {
                corrompue = 8;
            }
          }
           //////////////////////////////////// table destinataires  ////////
           else if(tableactuelle==7)
           {
                ss.clear();
                ss << ligne;
                elements.clear();
             while (getline(ss, sousChaine,';'))
             {
             elements.push_back(sousChaine);
             }
             if(elements.size() ==1)
             {
              m_destinataires.push_back(elements[0].data());
             }
             else
             {
                 corrompue = 9;
             }
           }
          //////////////////////////////////// table bts  ////////
          else if(tableactuelle==8)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() > 16)
            {
                btnew.clearpieces();
                btnew.setkey(std::atoi(elements[0].data()));
                btnew.setdate(std::atoi(elements[10].data()),std::atoi(elements[11].data()),std::atoi(elements[12].data()));
                btnew.settech(elements[1].data());
                btnew.setmachine(elements[2].data());
                btnew.settype(elements[3].data());
                btnew.setatelier(elements[4].data());
                btnew.setcommentaire(elements[5].data());
                btnew.setzone(elements[6].data());
                btnew.setgroupe(elements[7].data());
                btnew.setlu(elements[8].data());
                btnew.settime(elements[9].data());
                btnew.setphoto1(elements[13].data());
                btnew.setphoto2(elements[14].data());
                btnew.setphoto3(elements[15].data());
                btnew.setphoto4(elements[16].data());
                for(uint j=13; j < elements.size() ; j++)
                {
                    btnew.addpiece(std::atoi(elements[j].data())) ;
                }
                bts.push_back(btnew);
            }
            else
            {
                corrompue = 10;
            }
          }
          //////////////////////////////////// table commandes  ////////
          else if(tableactuelle==9)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() ==9)
            {
                commandenew.setkey(std::atoi(elements[0].data()));
                commandenew.setdate(std::atoi(elements[6].data()),std::atoi(elements[7].data()),std::atoi(elements[8].data()));
                commandenew.setfournisseur(elements[1].data());
                commandenew.setreference(elements[2].data());
                commandenew.setdestinataire(elements[4].data());
                commandenew.setprix(elements[3].data());
                commandenew.setcommentaire(elements[5].data());
                m_commandes.push_back(commandenew);
            }
            else
            {
                corrompue = 11;
            }

          }
          //////////////////////////////////// table machines  ////////
          else if(tableactuelle==10)
          {
               ss.clear();
               ss << ligne;
               elements.clear();
            while (getline(ss, sousChaine,';'))
            {
            elements.push_back(sousChaine);
            }
            if(elements.size() > 20)
            {

                machinenew.clearpieces();
                machinenew.setkey(std::atoi(elements[0].data()));
                machinenew.setatelier(elements[17].data());
                machinenew.setdate(std::atoi(elements[18].data()),std::atoi(elements[19].data()),std::atoi(elements[20].data()));
                machinenew.setfabricant(elements[1].data());
                machinenew.setname(elements[2].data());
                machinenew.setreference(elements[3].data());
                machinenew.setcommentaire(elements[4].data());
                machinenew.setliendoc1(elements[5].data());
                machinenew.setlienplan1(elements[6].data());
                machinenew.setlienphoto1(elements[7].data());
                machinenew.setliendoc2(elements[8].data());
                machinenew.setlienplan2(elements[9].data());
                machinenew.setlienphoto2(elements[10].data());
                machinenew.setliendoc3(elements[11].data());
                machinenew.setlienplan3(elements[12].data());
                machinenew.setlienphoto3(elements[13].data());
                machinenew.setliendoc4(elements[14].data());
                machinenew.setlienplan4(elements[15].data());
                machinenew.setlienphoto4(elements[16].data());
                for(uint j=21; j < elements.size() ; j++)
                {
                    machinenew.addpiece(std::atoi(elements[j].data())) ;
                }
                machines.push_back(machinenew);
            }
            else
            {
                corrompue = 12;
            }
          }
//////////////////////////////////////////////////////////////////////
           //////////////////////////////////// table categories  ////////
           else if(tableactuelle==11)
           {
                ss.clear();
                ss << ligne;
                elements.clear();
             while (getline(ss, sousChaine,';'))
             {
             elements.push_back(sousChaine);
             }
             if(elements.size() == 1)
             {
                 m_categorie.push_back(elements[0].data());
             }
             else
             {
                 corrompue = 15;
             }
           }
        }
        }
        modif = false;
    }
    else
    {
        corrompue = 13;
    }


    if(corrompue ==0)
    {
        corrompue = 2;
    }
}

void base::savebase()
{

    std::string temp="";
        temp = m_path;
        temp += m_name;
        temp += ".ggm";

    std::ofstream flux(temp.c_str(), std::ios::out|std::ios::trunc);
    std::vector <int> tableau;
    if (flux)
    {
        flux << "/* base de données du logiciel GGMAO develloppé par Jerome Humbert logiciel libre " << std::endl;
        flux << "/* creation de la base annee ; mois; jour ; clef prim table pieces ; clef prim table bt ; cle prim table machine ; clef prim commandes ;" << std::endl;
        flux << age.annee() << ";" << age.mois() << ";" << age.jour() << ";" << indexpieces << ";" << indexbt << ";" << indexmachine << ";" << indexcommandes << ";" << std::endl;
        flux << "// fin init variables generales base ////////" << std::endl;
        flux << "/* clef prim ; prix ; qty ; fabricant ;    nom   ;  reference ; commentaire ; date annee ; date mois ; date jour ; fournisseur 1 ; fournisseur 2 ; fournisseur 3 ; lien doc ; lien plan ; lien photo" << std::endl;
        // export table pieces //
        for(uint i=0;i < basep.size(); i++)
        {
            flux << basep[i].key() << ";" << basep[i].prix() << ";" << basep[i].qty() << ";" << basep[i].fabricant() << ";" << basep[i].name() << ";" << basep[i].reference() << ";" << basep[i].commentaire() << ";" << basep[i].date().annee() << ";" << basep[i].date().mois() << ";" << basep[i].date().jour() << ";" << basep[i].fournisseur1() << ";" << basep[i].fournisseur2() << ";" << basep[i].fournisseur3() << ";" << basep[i].emplacement() << ";" << basep[i].adresse() << ";" << basep[i].categorie() << ";" << basep[i].liendoc() << ";" << basep[i].lienplan() << ";" << basep[i].lienphoto() << ";" << std::endl;
        }
        flux << "// fin table pieces  ///////////" << std::endl;

        flux << "/* table techniciens" << std::endl;
        // export table techs //
        for(uint i=0;i < m_tech.size(); i++)
        {
            flux << m_tech[i].data() << ";" << std::endl;
        }
        flux << "// fin table techs  ///////////" << std::endl;

        flux << "/* table fournisseurs" << std::endl;
        // export table fournisseurs //
        for(uint i=0;i < m_fournisseurs.size(); i++)
        {
            flux << m_fournisseurs[i].name() << ";"<< m_fournisseurs[i].name_commercial() << ";"<< m_fournisseurs[i].num_bureau() << ";"<< m_fournisseurs[i].num_client() << ";"<< m_fournisseurs[i].num_contrat() << ";"<< m_fournisseurs[i].num_portable() << ";"<< m_fournisseurs[i].adresse_postale() << ";"<< m_fournisseurs[i].mail_1() << ";"<< m_fournisseurs[i].mail_2() << ";" << m_fournisseurs[i].commentaire() << ";"<< std::endl;
        }
        flux << "// fin table fournisseurs  ///////////" << std::endl;

        flux << "/* table fabricants" << std::endl;
        // export table fabricants //
        for(uint i=0;i < m_fabricants.size(); i++)
        {
            flux << m_fabricants[i].data() << ";" << std::endl;
        }
        flux << "// fin table fabricants  ///////////" << std::endl;

        flux << "/* table type de travail" << std::endl;
        // export table type travail //
        for(uint i=0;i < m_typetaf.size(); i++)
        {
            flux << m_typetaf[i].data() << ";" << std::endl;
        }
        flux << "// fin table type travail  ///////////" << std::endl;

        flux << "/* table ateliers" << std::endl;
        // export table ateliers //
        for(uint i=0;i < m_atelier.size(); i++)
        {
            flux << m_atelier[i].data() << ";" << std::endl;
        }
        flux << "// fin table ateliers  ///////////" << std::endl;

        flux << "/* table destinataires" << std::endl;
        // export table destinataires //
        for(uint i=0;i < m_destinataires.size(); i++)
        {
            flux << m_destinataires[i].data() << ";" << std::endl;
        }
        flux << "// fin table destinataires  ///////////" << std::endl;

        flux << "/* table bt's" << std::endl;
        // export table bt's //
        for(uint i=0;i < bts.size(); i++)
        {
            flux << bts[i].key() << ";" << bts[i].tech() << ";"  ;
            flux << bts[i].machine() << ";" << bts[i].type() << ";"  ;
            flux << bts[i].atelier() << ";" << bts[i].commentaire() << ";"  ;
            flux << bts[i].zone() << ";" << bts[i].groupe() << ";"  ;
            flux << bts[i].lu() << ";" << bts[i].time() << ";"  ;
            flux << bts[i].date().annee() << ";" << bts[i].date().mois() << ";"  ;
            flux << bts[i].date().jour() << ";" ;
            flux << bts[i].photo1() << ";" << bts[i].photo2() << ";";
            flux << bts[i].photo3() << ";" << bts[i].photo4() << ";";
             bts[i].getpieces(tableau);
            for(uint j=0; j < tableau.size() ; j++)
            {
              //  flux << tableau[j] << ";" ;
            }
            flux << std::endl  ;

        }
        flux << "// fin table bt's  ///////////" << std::endl;

        flux << "/* table commandes" << std::endl;
        // export table commandes //
        for(uint i=0;i < m_commandes.size(); i++)
        {
            flux << m_commandes[i].key() << ";" << m_commandes[i].fournisseur() << ";"  ;
            flux << m_commandes[i].reference() << ";" << m_commandes[i].prix() << ";"  ;
            flux << m_commandes[i].destinataire() << ";" << m_commandes[i].commentaire() << ";"  ;
            flux << m_commandes[i].date().annee() << ";" << m_commandes[i].date().mois() << ";"  ;
            flux << m_commandes[i].date().jour() << ";" << std::endl  ;
        }
        flux << "// fin table commandes  ///////////" << std::endl;

        flux << "/* table machines" << std::endl;
        // export table machines //
        for(uint i=0;i < machines.size(); i++)
        {
            flux << machines[i].key() << ";" << machines[i].fabricant() << ";" << machines[i].name() << ";";
            flux << machines[i].reference() << ";" << machines[i].commentaire() << ";" << machines[i].liendoc1() << ";" << machines[i].lienplan1() ;
            flux << ";" << machines[i].lienphoto1() << ";" << machines[i].liendoc2() << ";" << machines[i].lienplan2() << ";";
            flux << machines[i].lienphoto2() << ";" << machines[i].liendoc3() << ";" << machines[i].lienplan3() << ";" << machines[i].lienphoto3();
            flux << ";" << machines[i].liendoc4() << ";" << machines[i].lienplan4() << ";" << machines[i].lienphoto4() << ";";
            flux << machines[i].atelier() << ";" << machines[i].date().annee() << ";" << machines[i].date().mois() << ";" << machines[i].date().jour() << ";";
            tableau.clear();
            machines[i].getpieces(tableau);
           for(uint j=0; j < tableau.size() ; j++)
           {
               flux << tableau[j] << ";" ;
           }
           flux << std::endl  ;
        }
        flux << "// fin table machines  ///////////" << std::endl;
        flux << "/* table categories" << std::endl;
        // export table categories //
        for(uint i=0;i < m_categorie.size(); i++)
        {
            flux << m_categorie[i].data() << ";" << std::endl;
        }
        flux << "// fin table categories  ///////////" << std::endl;

        modif = false;
    }

    else
    {
        corrompue = 1;
    }

flux.close();

}

void base::saveressources()
{
    std::string adresse="";
    std::string temp="";

    QString path = m_path.c_str();
    path += "/ressources/";
    QStringList filters;
      filters << "*.pdf" << "*.png" << "*.jpg";
    QStringList files = QDir( path ).entryList(filters);
    path = m_path.c_str();
    path += "/ressources.txt";

    std::ofstream flux(path.toStdString().c_str(), std::ios::out|std::ios::trunc);
    if(flux)
    {
       for(int i=0; i < files.size(); i++)
       {
           flux << files[i].toStdString() << std::endl;
       }
    }
    flux.close();
     path = m_path.c_str();
     path += "/sync.txt";
    std::ofstream flux2(path.toStdString().c_str(), std::ios::out|std::ios::trunc);
    if(flux2)
    {
       adresse += "file://";
       adresse += QHostInfo::localHostName().toStdString();
       temp = m_path;
       temp.erase(0,2);
       adresse += temp;
       adresse += "ressources.txt";
           flux2 << adresse << std::endl;

    }
flux2.close();

}

void base::ajouterdocument(std::string format, std::string &adresse)
{

}

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



void base::modified(bool m)
{
    modif = m;
}

void base::chargee(bool c)
{
    charg = c;
}

bool base::ismodified()
{
    return modif;
}

bool base::ischargee()
{
    return charg;
}



int base::nbpieces()
{
  return basep.size();
}

int base::nbmachines()
{
  return machines.size();
}

int base::nbbts()
{
  return bts.size();
}

int base::nbcommandes()
{
  return m_commandes.size();
}

int base::nbtech()
{
  return m_tech.size();
}

int base::nbfournisseurs()
{
  return m_fournisseurs.size();
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


int base::bts_annee(int num) const
{
    return bts[num].date().annee();
}

int base::bts_mois(int num) const
{
    return bts[num].date().mois();
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



void base::getlisttech(std::vector<std::string> &tech)
{
   tech = m_tech;
}

void base::getlistdestinataires(std::vector<std::string> &dest)
{
   dest = m_destinataires;
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

void base::getlistcategories(std::vector<std::string> &cat)
{
   cat = m_categorie;
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


void base::getlistfournisseurs(std::vector<std::string> &four)
{

    four.clear();
    for(int b=0; b < m_fournisseurs.size(); b++)
    {
        four.push_back(m_fournisseurs[b].name());

    }

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

int base::findmachine(std::string mach)
{
    for(uint i=0;i < machines.size(); i++)
    {
      if(machines[i].name() == mach) return i;
    }
    return -1;
}

int base::commande_check_date(int num,std::string a,std::string b)
{
    return m_commandes[num].date().comparedate(a,b);
}

int base::pieces_check_date(int num,std::string a,std::string b)
{
    return basep[num].date().comparedate(a,b);
}

int base::bt_check_date(int num,std::string a,std::string b)
{
    return bts[num].date().comparedate(a,b);
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


void base::setdate_bt_param(std::string f)
{
    date_bt = f;
}

std::string base::getdate_bt_param()
{
    return date_bt;
}

void base::setdate_commande_param(std::string f)
{
    date_commande = f;
}

std::string base::getdate_commande_param()
{
    return date_commande;
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
