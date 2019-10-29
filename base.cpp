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
      m_largeur = 800;
      m_hauteur = 600;
      m_nbsaves = 25;
      m_fullscreen = false;
      m_openauto = false;
      m_saveauto = false;
      m_memodatebt = false;
      m_memodatecommande = false;
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

bool base::fullscreen() const
{
    return m_fullscreen;
}

void base::setfullscreen(bool b)
{
    m_fullscreen = b;
}

bool base::openauto() const
{
    return m_openauto;
}

void base::setopenauto(bool b)
{
    m_openauto = b;
}

bool base::saveauto() const
{
    return m_saveauto;
}

void base::setsaveauto(bool b)
{
    m_saveauto = b;
}

bool base::memobt() const
{
    return m_memodatebt;
}

void base::setmemobt(bool b)

{
    m_memodatebt= b;
}

bool base::memocommande() const
{
    return m_memodatecommande;
}

void base::setmemocommande(bool b)
{
    m_memodatecommande = b;
}

int base::largeur() const
{
    return m_largeur;
}

void base::setlargeur(int i)
{
    if(i > 799 && i < 2000) m_largeur = i;
}

int base::hauteur() const
{
    return m_hauteur;
}

void base::sethauteur(int i)
{
    if(i > 479 && i < 1800) m_hauteur = i;
}

int base::nbsaves() const
{
    return m_nbsaves;
}

void base::setnbsaves(int i)
{
    if(i < 0 || i > 500)
    {}
    else
    {
     m_nbsaves = i;
    }
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













