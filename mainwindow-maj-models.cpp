#include "mainwindow.h"
#include <QtWidgets>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include "pieces.h"
#include "fichiers.h"
#include "base.h"
#include "addpiecesbase.h"
#include "setbtbase.h"
#include "addpiecesmachine.h"
#include "addbtbase.h"
#include "addmachinebase.h"
#include "addcommandebase.h"
#include "addtablebase.h"
#include "setmachine.h"
#include "setcommande.h"
#include "parametres.h"
#include "setpiecesbase.h"


void MainWindow::majmodelpieces()
{
    std::cout << "majpieces" << std::endl;
    tablopiecesint.clear();
    modelepieces->clear();
    int x=0;
    std::string::size_type n;
    QStringList titre;
    titre <<  "nom" << "fabricant" << "reference" << "commentaires" << "fournisseur 1" << "fournisseur 2" << "fournisseur 3" << "emplacement" << "adresse" << "categorie"<< "doc" << "plan" << "photo"  << "prix" << "quantité" << "controlée le :" << "n°";
    modelepieces->setHorizontalHeaderLabels(titre);
             for(int i =0 ; i < b.nbpieces(); i++)
              {
                 if(!ptri->isChecked() || (b.pieces_nom(i).find(ptrinom->text().toStdString())!= std::string::npos && b.pieces_reference(i).find(ptrireference->text().toStdString())!= std::string::npos && b.pieces_commentaire(i).find(ptricommentaire->text().toStdString())!= std::string::npos && b.pieces_emplacement(i).find(ptriemplacement->text().toStdString())!= std::string::npos && b.pieces_adresse(i).find(ptriadresse->text().toStdString())!= std::string::npos && b.pieces_categorie(i).find(ptricategorie->currentText().toStdString())!= std::string::npos && ( b.pieces_four1(i).find(ptrifournisseur->currentText().toStdString())!= std::string::npos || b.pieces_four2(i).find(ptrifournisseur->currentText().toStdString())!= std::string::npos || b.pieces_four3(i).find(ptrifournisseur->currentText().toStdString())!= std::string::npos ) && b.pieces_fabricant(i).find(ptrifabricant->currentText().toStdString())!= std::string::npos && b.pieces_check_date(i,ptridatea->text().toStdString(),ptridateb->text().toStdString()) ==0 ))
                 {
                 modelepieces->setItem(x, 0, new QStandardItem(QString::fromStdString(b.pieces_nom(i))));
                 modelepieces->setItem(x, 1, new QStandardItem(QString::fromStdString(b.pieces_fabricant(i))));
                 modelepieces->setItem(x, 2,new QStandardItem(QString::fromStdString(b.pieces_reference(i))));
                 modelepieces->setItem(x, 3,new QStandardItem(QString::fromStdString(b.pieces_commentaire(i))));
                 modelepieces->setItem(x, 4,new QStandardItem(QString::fromStdString(b.pieces_four1(i))));
                 modelepieces->setItem(x, 5,new QStandardItem(QString::fromStdString(b.pieces_four2(i))));
                 modelepieces->setItem(x, 6,new QStandardItem(QString::fromStdString(b.pieces_four3(i))));
                 modelepieces->setItem(x, 7,new QStandardItem(QString::fromStdString(b.pieces_emplacement(i))));
                 modelepieces->setItem(x, 8,new QStandardItem(QString::fromStdString(b.pieces_adresse(i))));
                 modelepieces->setItem(x, 9,new QStandardItem(QString::fromStdString(b.pieces_categorie(i))));
                 modelepieces->setItem(x, 10,new QStandardItem(QString::fromStdString(b.pieces_liendoc(i))));
                 modelepieces->setItem(x, 11,new QStandardItem(QString::fromStdString(b.pieces_lienplan(i))));
                 modelepieces->setItem(x, 12,new QStandardItem(QString::fromStdString(b.pieces_lienphoto(i))));
                 modelepieces->setItem(x, 13,new QStandardItem(QString::fromStdString(b.pieces_prix(i))));
                 modelepieces->setItem(x, 14,new QStandardItem(QString::fromStdString(b.pieces_qty(i))));
                 modelepieces->setItem(x, 15,new QStandardItem(QString::fromStdString(b.pieces_date(i))));
                 modelepieces->setItem(x, 16,new QStandardItem(QString::fromStdString(b.pieces_key(i))));
                 tablopiecesint.push_back(std::atoi(b.pieces_key(i).c_str()));
                 x++;
                  }
             }

             menuinfbt5->setText("trop de pieces");

             if(tablopiecesint.size() <26 && tablopiecesint.size() > 0)
             {
                 menuinfbt5->setText("ajouter selection a machine");
             }
             else if(tablopiecesint.size() == 0)
             {
                 menuinfbt5->setText("...");
             }



}

void MainWindow::majmodelmach1()
{
    std::cout << "majmach1" << std::endl;

    std::vector<std::string> tab;
    b.getlistatelier(tab);
    std::sort(tab.begin(),tab.end());
    listeatelier->clear();
    for(uint i=0 ; i < tab.size(); i++ )
    {
        listeatelier->addItem(QString::fromStdString(tab[i].data()));
    }
    tab.clear();
    b.getlistmachineatelier(tab,listeatelier->currentText().toStdString());
    std::sort(tab.begin(),tab.end());
    listemachine->clear();
    for(uint i=0 ; i < tab.size(); i++ )
    {
        listemachine->addItem(QString::fromStdString(tab[i].data()));
    }

}

void MainWindow::majmodelmach2()
{
    std::cout << "majmach2" << std::endl;

    std::vector<std::string> tab;
    tab.clear();
    b.getlistmachineatelier(tab,listeatelier->currentText().toStdString());
    std::sort(tab.begin(),tab.end());
    listemachine->clear();
    for(uint i=0 ; i < tab.size(); i++ )
    {
        listemachine->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
    }


}

void MainWindow::majmodelmach3()
{
    std::cout << "majmach3" << std::endl;

    QStringList titrelistebt ,titrelistepieces;
    int num_mach=0;
    int indexmodel=0;
    bool fichier_existe =false;
    std::vector <std::string> fichiers;
    num_mach = b.findmachine(listemachine->currentText().toStdString());
    if(num_mach > -1)
    {
    b.getlistmachinefabricant(fabricant,num_mach);
    b.getlistmachinedate(date,num_mach);
    b.getlistmachinereference(reference,num_mach);
    b.getlistmachinecommentaire(commentaire,num_mach);

    fichiers.clear();
    b.getlistmachinedoc(fichiers,num_mach);
    listedoc->clear();
    for(uint i =0 ; i < fichiers.size(); i++)
     {
        listedoc->addItem(QString::fromStdString(fichiers[i].data()), QVariant(i));

    }
    fichiers.clear();

    b.getlistmachineplan(fichiers,num_mach);
    for(uint i =0 ; i < fichiers.size(); i++)
     {
        listedoc->addItem(QString::fromStdString(fichiers[i].data()), QVariant(i));

    }
    fichiers.clear();
    b.getlistmachinephoto(fichiers,num_mach);
    for(uint i =0 ; i < fichiers.size(); i++)
     {
        listedoc->addItem(QString::fromStdString(fichiers[i].data()), QVariant(i));

     }
    ////////////////////////////

    modelemachinesbt->clear();
    titrelistebt << "tech" << "type de bt" << "date"  << "commentaires" << "temps d'inter" << "visé :"  << "clef" << "atelier" << "machine" ;
    modelemachinesbt->setHorizontalHeaderLabels(titrelistebt);
    for(int i = (b.nbbts() -1) ; i > -1; i--)
     {
        if(b.bt_machine(i) == listemachine->currentText().toStdString())
        {
        modelemachinesbt->setItem(indexmodel, 0,new QStandardItem(QString::fromStdString(b.bt_tech(i))));
        modelemachinesbt->setItem(indexmodel, 1,new QStandardItem(QString::fromStdString(b.bt_type(i))));
        modelemachinesbt->setItem(indexmodel, 2, new QStandardItem(QString::fromStdString(b.bt_date(i))));
        modelemachinesbt->setItem(indexmodel, 3,new QStandardItem(QString::fromStdString(b.bt_commentaire(i))));
        modelemachinesbt->setItem(indexmodel, 4,new QStandardItem(QString::fromStdString(b.bt_temps(i))));
        modelemachinesbt->setItem(indexmodel, 5,new QStandardItem(QString::fromStdString(b.bt_slu(i))));
        modelemachinesbt->setItem(indexmodel, 6,new QStandardItem(QString::fromStdString(b.bt_skey(i))));
        modelemachinesbt->setItem(indexmodel, 7, new QStandardItem(QString::fromStdString(b.bt_atelier(i))));
        modelemachinesbt->setItem(indexmodel, 8,new QStandardItem(QString::fromStdString(b.bt_machine(i))));
        indexmodel++;
        }
     }
    indexmodel=0;
    modelemachinespieces->clear();
    titrelistepieces <<  "nom" << "fabricant" << "reference" << "commentaires" << "fournisseur 1" << "fournisseur 2" << "fournisseur 3" << "emplacement" << "adresse" << "categorie"<< "doc" << "plan" << "photo"  << "prix" << "quantité" << "controlée le :" << "n°";
    modelemachinespieces->setHorizontalHeaderLabels(titrelistepieces);
    std::vector <int> pieces;
    pieces.clear();
    b.getlistmachinespieces(pieces,num_mach);
    for(int i =0 ; i < b.nbpieces(); i++)
     {
        for(uint j =0; j < pieces.size() ; j++)
        {
        if(std::atoi(b.pieces_key(i).c_str()) == pieces[j] )
        {
        modelemachinespieces->setItem(indexmodel, 0, new QStandardItem(QString::fromStdString(b.pieces_nom(i))));
        modelemachinespieces->setItem(indexmodel, 1, new QStandardItem(QString::fromStdString(b.pieces_fabricant(i))));
        modelemachinespieces->setItem(indexmodel, 2,new QStandardItem(QString::fromStdString(b.pieces_reference(i))));
        modelemachinespieces->setItem(indexmodel, 3,new QStandardItem(QString::fromStdString(b.pieces_commentaire(i))));
        modelemachinespieces->setItem(indexmodel, 4,new QStandardItem(QString::fromStdString(b.pieces_four1(i))));
        modelemachinespieces->setItem(indexmodel, 5,new QStandardItem(QString::fromStdString(b.pieces_four2(i))));
        modelemachinespieces->setItem(indexmodel, 6,new QStandardItem(QString::fromStdString(b.pieces_four3(i))));
        modelemachinespieces->setItem(indexmodel, 7,new QStandardItem(QString::fromStdString(b.pieces_emplacement(i))));
        modelemachinespieces->setItem(indexmodel, 8,new QStandardItem(QString::fromStdString(b.pieces_adresse(i))));
        modelemachinespieces->setItem(indexmodel, 9,new QStandardItem(QString::fromStdString(b.pieces_categorie(i))));
        modelemachinespieces->setItem(indexmodel, 10,new QStandardItem(QString::fromStdString(b.pieces_liendoc(i))));
        modelemachinespieces->setItem(indexmodel, 11,new QStandardItem(QString::fromStdString(b.pieces_lienplan(i))));
        modelemachinespieces->setItem(indexmodel, 12,new QStandardItem(QString::fromStdString(b.pieces_lienphoto(i))));
        modelemachinespieces->setItem(indexmodel, 13,new QStandardItem(QString::fromStdString(b.pieces_prix(i))));
        modelemachinespieces->setItem(indexmodel, 14,new QStandardItem(QString::fromStdString(b.pieces_qty(i))));
        modelemachinespieces->setItem(indexmodel, 15,new QStandardItem(QString::fromStdString(b.pieces_date(i))));
        modelemachinespieces->setItem(indexmodel, 16,new QStandardItem(QString::fromStdString(b.pieces_key(i))));
        fichier_existe = false;
        if(b.pieces_lienphoto(i) != "")
        {
            for (int y =0;y < listedoc->count();y++)
            {
                if(b.pieces_lienphoto(i) == listedoc->itemText(y).toStdString()) fichier_existe = true;

            }
            if(!fichier_existe) listedoc->addItem(QString::fromStdString(b.pieces_lienphoto(i)), QVariant(i));
        }
        fichier_existe = false;
        if(b.pieces_lienplan(i) != "")
        {
            for (int y =0;y < listedoc->count();y++)
            {
                if(b.pieces_lienplan(i) == listedoc->itemText(y).toStdString()) fichier_existe = true;

            }
            if(!fichier_existe)  listedoc->addItem(QString::fromStdString(b.pieces_lienplan(i)), QVariant(i));
        }
        fichier_existe = false;
        if(b.pieces_liendoc(i) != "")
        {
            for (int y =0;y < listedoc->count();y++)
            {
                if(b.pieces_liendoc(i) == listedoc->itemText(y).toStdString()) fichier_existe = true;

            }
            if(!fichier_existe)  listedoc->addItem(QString::fromStdString(b.pieces_liendoc(i)), QVariant(i));
        }
        indexmodel++;
        }
        }
     }


    }
}

void MainWindow::majmodelbt()
{
    std::cout << "majbt" << std::endl;

    modelebt->clear();
    QStringList titre3;
    titre3 << "tech" << "type de bt" << "date" << "atelier" << "machine" << "temps d'inter" << "commentaires" << "visé :"  << "clef";
    modelebt->setHorizontalHeaderLabels(titre3);
    int x=0;
    std::string::size_type n;
    for(int i = (b.nbbts()-1) ; i > -1; i--)
     {
        if(!btri->isChecked() || (b.bt_tech(i).find(btritech->currentText().toStdString())!= std::string::npos && b.bt_type(i).find(btritype->currentText().toStdString())!= std::string::npos && b.bt_atelier(i).find(btriatelier->currentText().toStdString())!= std::string::npos && b.bt_machine(i).find(btrimachine->currentText().toStdString())!= std::string::npos && b.bt_commentaire(i).find(btricommentaire->text().toStdString())!= std::string::npos && b.bt_slu(i).find(btrilu->currentText().toStdString())!= std::string::npos && b.bt_check_date(i,btridatea->text().toStdString(),btridateb->text().toStdString()) == 0 ))
        {
        modelebt->setItem(x, 0,new QStandardItem(QString::fromStdString(b.bt_tech(i))));
        modelebt->setItem(x, 1,new QStandardItem(QString::fromStdString(b.bt_type(i))));
        modelebt->setItem(x, 2, new QStandardItem(QString::fromStdString(b.bt_date(i))));
        modelebt->setItem(x, 3, new QStandardItem(QString::fromStdString(b.bt_atelier(i))));
        modelebt->setItem(x, 4,new QStandardItem(QString::fromStdString(b.bt_machine(i))));
        modelebt->setItem(x, 5,new QStandardItem(QString::fromStdString(b.bt_temps(i))));
        modelebt->setItem(x, 6,new QStandardItem(QString::fromStdString(b.bt_commentaire(i))));
        modelebt->setItem(x, 7,new QStandardItem(QString::fromStdString(b.bt_slu(i))));
        modelebt->setItem(x, 8,new QStandardItem(QString::fromStdString(b.bt_skey(i))));
        x++;
        }
    }
}

void MainWindow::majmodelcommandes()
{
    std::cout << "majcommandes" << std::endl;

    modelecommandes->clear();
    int x=0;
    std::string::size_type n;
    QStringList titre4;
    titre4 << "fournisseur" << "n°de commande" << "montant ht" << "date" << "destinataire" << "commentaires" << "clef" ;
    modelecommandes->setHorizontalHeaderLabels(titre4);
    vue4->setSelectionBehavior(QAbstractItemView::SelectRows);
    vue4->setSelectionMode(QAbstractItemView::SingleSelection);
    for(int i = (b.nbcommandes()-1) ; i > -1; i--)
     {
        if(!ctri->isChecked() || (b.commande_fournisseur(i).find(ctrifournisseur->currentText().toStdString())!= std::string::npos && b.commande_destinataire(i).find(ctridestinataire->currentText().toStdString())!= std::string::npos && b.commande_reference(i).find(ctrireference->text().toStdString())!= std::string::npos  && b.commande_commentaire(i).find(ctricommentaire->text().toStdString())!= std::string::npos && b.commande_check_date(i,ctridatea->text().toStdString(),ctridateb->text().toStdString()) ==0 ))
        {

        modelecommandes->setItem(x, 0,new QStandardItem(QString::fromStdString(b.commande_fournisseur(i))));
        modelecommandes->setItem(x, 1,new QStandardItem(QString::fromStdString(b.commande_reference(i))));
        modelecommandes->setItem(x, 2, new QStandardItem(QString::fromStdString(b.commande_prix(i))));
        modelecommandes->setItem(x, 3, new QStandardItem(QString::fromStdString(b.commande_date(i))));
        modelecommandes->setItem(x, 4,new QStandardItem(QString::fromStdString(b.commande_destinataire(i))));
        modelecommandes->setItem(x, 5,new QStandardItem(QString::fromStdString(b.commande_commentaire(i))));
        modelecommandes->setItem(x, 6,new QStandardItem(QString::fromStdString(b.commande_skey(i))));
        x++;
        }
    }
}

void MainWindow::majtables()
{
    std::cout << "majtables" << std::endl;

    modeletables->clear();
    QStringList titre5;
    titre5 << "tech's" << "atelier" << "type de bt" << "fournisseurs" << "fabricants" << "destinataires" << "categories"  ;
    modeletables->setHorizontalHeaderLabels(titre5);
    std::vector<std::string> tab;
    btritech->clear();
    btritech->addItem(QString::fromStdString(""));
    b.getlisttech(tab);
    std::sort(tab.begin(),tab.end());
    for(uint i=0 ; i < tab.size(); i++ )
    {
        modeletables->setItem(i, 0,new QStandardItem(QString::fromStdString(tab[i].data())));
        btritech->addItem(QString::fromStdString(tab[i].data()));

    }

    b.getlistatelier(tab);
    std::sort(tab.begin(),tab.end());
    btriatelier->clear();
    btriatelier->addItem(QString::fromStdString(""));
    for(uint i=0 ; i < tab.size(); i++ )
    {
        modeletables->setItem(i, 1,new QStandardItem(QString::fromStdString(tab[i].data())));
        btriatelier->addItem(QString::fromStdString(tab[i].data()));
    }

    b.getlisttypetaf(tab);
    std::sort(tab.begin(),tab.end());
    btritype->clear();
    btritype->addItem(QString::fromStdString(""));
    for(uint i=0 ; i < tab.size(); i++ )
    {
        modeletables->setItem(i, 2,new QStandardItem(QString::fromStdString(tab[i].data())));
        btritype->addItem(QString::fromStdString(tab[i].data()));
    }

    b.getlistfournisseurs(tab);
    std::sort(tab.begin(),tab.end());
    ptrifournisseur->clear();
    ptrifournisseur->addItem(QString::fromStdString(""));
    ctrifournisseur->clear();
    ctrifournisseur->addItem(QString::fromStdString(""));
    for(uint i=0 ; i < tab.size(); i++ )
    {
        modeletables->setItem(i, 3,new QStandardItem(QString::fromStdString(tab[i].data())));
        ptrifournisseur->addItem(QString::fromStdString(tab[i].data()));
        ctrifournisseur->addItem(QString::fromStdString(tab[i].data()));
    }

    b.getlistfabricants(tab);
    std::sort(tab.begin(),tab.end());
    ptrifabricant->clear();
    ptrifabricant->addItem(QString::fromStdString(""));
    for(uint i=0 ; i < tab.size(); i++ )
    {
        modeletables->setItem(i, 4,new QStandardItem(QString::fromStdString(tab[i].data())));
        ptrifabricant->addItem(QString::fromStdString(tab[i].data()));
    }

    b.getlistdestinataires(tab);
    std::sort(tab.begin(),tab.end());
    ctridestinataire->clear();
    ctridestinataire->addItem(QString::fromStdString(""));
    for(uint i=0 ; i < tab.size(); i++ )
    {
        ctridestinataire->addItem(QString::fromStdString(tab[i].data()));
        modeletables->setItem(i, 5,new QStandardItem(QString::fromStdString(tab[i].data())));
    }
    ptricategorie->clear();
    ptricategorie->addItem(QString::fromStdString(""));
    b.getlistcategories(tab);
    std::sort(tab.begin(),tab.end());
    for(uint i=0 ; i < tab.size(); i++ )
    {
        modeletables->setItem(i, 6,new QStandardItem(QString::fromStdString(tab[i].data())));
        ptricategorie->addItem(QString::fromStdString(tab[i].data()));
    }
}

void MainWindow::maj_fournisseurs()
{
    std::cout << "majfournisseurs" << std::endl;

    std::vector<std::string> tab;
    b.getlistfournisseurs(tab);
    std::sort(tab.begin(),tab.end());

    p7_fournisseur->clear();
    p7_fournisseur->addItem(QString::fromStdString(""));
    for(uint i=0 ; i < tab.size(); i++ )
    {
        p7_fournisseur->addItem(QString::fromStdString(tab[i].data()));
    }

}
