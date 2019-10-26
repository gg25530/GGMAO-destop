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
#include "fournisseurs.h"
#include "setcommande.h"
#include "parametres.h"
#include "setpiecesbase.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPrinter>



void MainWindow::tripieceschanged()
{
    if(onglets->currentIndex() == 0)menuinfbt5->setText("trop de pieces");
    if(!ptri->isChecked())
    {
      ptrinom->setText("");
      ptrireference->setText("");
      ptricommentaire->setText("");
      ptriemplacement->setText("");
      ptriadresse->setText("");
      ptridatea->setText("01-01-2000");
      ptridateb->setText("01-01-2040");
      ptrifournisseur->setCurrentText("");
      ptrifabricant->setCurrentText("");
      ptricategorie->setCurrentText("");
    }
    else
    {
        this->majmodelpieces();
    }
}


void MainWindow::tripiecesactivated()
{
    if(onglets->currentIndex() == 0)menuinfbt5->setText("trop de pieces");

    if(!ptri->isChecked())
    {
      ptrinom->setText("");
      ptrireference->setText("");
      ptricommentaire->setText("");
      ptriemplacement->setText("");
      ptriadresse->setText("");
      ptridatea->setText("01-01-2000");
      ptridateb->setText("01-01-2040");
      ptrifournisseur->setCurrentText("");
      ptrifabricant->setCurrentText("");
      ptricategorie->setCurrentText("");
    }
    else
    {
    }
    this->majmodelpieces();

}



void MainWindow::tribtchanged()
{
    if(onglets->currentIndex() == 2)
{
    if(!btri->isChecked())
    {
      btricommentaire->setText("");
      btridatea->setText("01-01-2000");
      btridateb->setText("01-01-2040");
      btritech->setCurrentText("");
      btriatelier->setCurrentText("");
      btritype->setCurrentText("");
      btrimachine->setCurrentText("");
      btrilu->setCurrentText("");
    }
            this->majmodelbt();
}
}

void MainWindow::tricommandeschanged()
{
    if(onglets->currentIndex() == 3)
    {
    if(!ctri->isChecked())
    {
     ctrireference->setText("");
     ctricommentaire->setText("");
     ctrifournisseur->setCurrentText("");
     ctridestinataire->setCurrentText("");
     ctridatea->setText("01-01-2000");
     ctridateb->setText("01-01-2040");
    }
        this->majmodelcommandes();
    }
}

void MainWindow::tripiecesvisible(bool state)
{
   if(state)
   {
       pttrireference->setVisible(true);
       pttrinom->setVisible(true);
       pttricommentaire->setVisible(true);
       pttrifournisseur->setVisible(true);
       pttrifabricant->setVisible(true);
       pttricategorie->setVisible(true);
       pttriemplacement->setVisible(true);
       pttriadresse->setVisible(true);
       pttridate->setVisible(true);
       ptrireference->setVisible(true);
       ptrinom->setVisible(true);
       ptricommentaire->setVisible(true);
       ptrifournisseur->setVisible(true);
       ptrifabricant->setVisible(true);
       ptricategorie->setVisible(true);
       ptriemplacement->setVisible(true);
       ptriadresse->setVisible(true);
       ptridatea->setVisible(true);
       ptridateb->setVisible(true);
       ptri->setVisible(true);
   }
   else
   {
       pttrireference->setVisible(false);
       pttrinom->setVisible(false);
       pttricommentaire->setVisible(false);
       pttrifournisseur->setVisible(false);
       pttrifabricant->setVisible(false);
       pttricategorie->setVisible(false);
       pttriemplacement->setVisible(false);
       pttriadresse->setVisible(false);
       pttridate->setVisible(false);
       ptrireference->setVisible(false);
       ptrinom->setVisible(false);
       ptricommentaire->setVisible(false);
       ptrifournisseur->setVisible(false);
       ptrifabricant->setVisible(false);
       ptricategorie->setVisible(false);
       ptriemplacement->setVisible(false);
       ptriadresse->setVisible(false);
       ptridatea->setVisible(false);
       ptridateb->setVisible(false);
       ptri->setVisible(false);
   }
}

void MainWindow::tribtvisible(bool state)
{
    if(state)
    {
        btri->setVisible(true);
         btrilu->setVisible(true);
         btricommentaire->setVisible(true);
         btridatea->setVisible(true);
         btridateb->setVisible(true);
         btritech->setVisible(true);
         btriatelier->setVisible(true);
         btritype->setVisible(true);
         btrimachine->setVisible(true);
         bttricommentaire->setVisible(true);
         bttrilu->setVisible(true);
         bttridate->setVisible(true);
         bttritech->setVisible(true);
         bttriatelier->setVisible(true);
         bttritype->setVisible(true);
         bttrimachine->setVisible(true);
    }
    else
    {
         btri->setVisible(false);
         btrilu->setVisible(false);
         btricommentaire->setVisible(false);
         btridatea->setVisible(false);
         btridateb->setVisible(false);
         btritech->setVisible(false);
         btriatelier->setVisible(false);
         btritype->setVisible(false);
         btrimachine->setVisible(false);
         bttricommentaire->setVisible(false);
         bttrilu->setVisible(false);
         bttridate->setVisible(false);
         bttritech->setVisible(false);
         bttriatelier->setVisible(false);
         bttritype->setVisible(false);
         bttrimachine->setVisible(false);
    }
}

void MainWindow::tricommandevisible(bool state)
{
    if(state)
    {
        ctrireference->setVisible(true);
        ctricommentaire->setVisible(true);
        ctrifournisseur->setVisible(true);
        ctridestinataire->setVisible(true);
        ctridatea->setVisible(true);
        ctridateb->setVisible(true);
        cttrireference->setVisible(true);
        cttricommentaire->setVisible(true);
        cttrifournisseur->setVisible(true);
        cttridestinataire->setVisible(true);
        cttridate->setVisible(true);
        ctri->setVisible(true);
    }
    else
    {
        ctrireference->setVisible(false);
        ctricommentaire->setVisible(false);
        ctrifournisseur->setVisible(false);
        ctridestinataire->setVisible(false);
        ctridatea->setVisible(false);
        ctridateb->setVisible(false);
        cttrireference->setVisible(false);
        cttricommentaire->setVisible(false);
        cttrifournisseur->setVisible(false);
        cttridestinataire->setVisible(false);
        cttridate->setVisible(false);
        ctri->setVisible(false);
    }
}

void MainWindow::tristatsvisible(bool state)
{
    if(state)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string temp="";
        std::stringstream convert;
        convert.clear();
        convert <<  (1900 + ltm->tm_year);
        strimoisdebut->setCurrentIndex( ltm->tm_mon);
        strianneedebut->setCurrentText(convert.str().c_str());

        if(type_stat ==0)  // commande du mois
        {
            strimoisdebut->setCurrentIndex( ltm->tm_mon);
            strianneedebut->setCurrentText(convert.str().c_str());
               strimoisdebut->setVisible(true);
               strimoisfin->setVisible(false);
               strianneedebut->setVisible(true);
               strianneefin->setVisible(false);
               stri_de->setVisible(false);
               stri_jusqua->setVisible(false);
               stridivers->setVisible(false);
               menuinfbt1->setDown(true);
               menuinfbt2->setDown(false);
               menuinfbt3->setDown(false);
               menuinfbt4->setDown(false);
               menuinfbt5->setDown(false);
        }
        else if(type_stat ==1) //  suivi ateliers
        {
           // strimoisdebut->setCurrentIndex( 1);
            strianneedebut->setCurrentText(convert.str().c_str());
            //strimoisfin->setCurrentIndex(1);
         //   strianneefin->setCurrentText(convert.str().c_str());
            strimoisdebut->setVisible(false);
               strimoisfin->setVisible(false);
               strianneedebut->setVisible(true);
               strianneefin->setVisible(false);
               stri_de->setVisible(false);
               stri_jusqua->setVisible(false);
               stridivers->clear();
               for(uint i=0; i < btriatelier->count();i++)
               {
                   stridivers->addItem(btriatelier->itemText(i));
               }
               stridivers->setVisible(true);
               menuinfbt1->setDown(false);
               menuinfbt2->setDown(true);
               menuinfbt3->setDown(false);
               menuinfbt4->setDown(false);
               menuinfbt5->setDown(false);
        }
        else if(type_stat ==2) // suivi bt's
        {
            // strimoisdebut->setCurrentIndex( 1);
             strianneedebut->setCurrentText(convert.str().c_str());
             //strimoisfin->setCurrentIndex(1);
          //   strianneefin->setCurrentText(convert.str().c_str());
             stridivers->clear();
             stridivers->addItem(QString::fromStdString("ateliers"));
             stridivers->addItem(QString::fromStdString("techniciens"));
             stridivers->addItem(QString::fromStdString("type"));
             strimoisdebut->setVisible(false);
                strimoisfin->setVisible(false);
                strianneedebut->setVisible(true);
                strianneefin->setVisible(false);
                stri_de->setVisible(false);
                stri_jusqua->setVisible(false);
                stridivers->setVisible(true);
                menuinfbt1->setDown(false);
                menuinfbt2->setDown(false);
                menuinfbt3->setDown(true);
                menuinfbt4->setDown(false);
                menuinfbt5->setDown(false);
        }
        else if(type_stat ==3)  // commandes annee
        {
            strianneedebut->setCurrentText(convert.str().c_str());
            strimoisdebut->setVisible(false);
               strimoisfin->setVisible(false);
               strianneedebut->setVisible(true);
               strianneefin->setVisible(false);
               stri_de->setVisible(false);
               stri_jusqua->setVisible(false);
               stridivers->clear();
               stridivers->addItem("budget-mensuel");
               for(uint i=0; i < ctrifournisseur->count();i++)
               {
                   stridivers->addItem(ctrifournisseur->itemText(i));
               }
               stridivers->setVisible(true);
               menuinfbt1->setDown(false);
               menuinfbt2->setDown(false);
               menuinfbt3->setDown(false);
               menuinfbt4->setDown(true);
               menuinfbt5->setDown(false);
        }
        else if(type_stat ==4) // suivi annuel
        {
            strianneedebut->setCurrentText(convert.str().c_str());
            stridivers->clear();
            stridivers->addItem(QString::fromStdString("fournisseurs"));
            stridivers->addItem(QString::fromStdString("destinataires"));
            strimoisdebut->setVisible(false);
               strimoisfin->setVisible(false);
               strianneedebut->setVisible(true);
               strianneefin->setVisible(false);
               stri_de->setVisible(false);
               stri_jusqua->setVisible(false);
               stridivers->setVisible(true);
               menuinfbt1->setDown(false);
               menuinfbt2->setDown(false);
               menuinfbt3->setDown(false);
               menuinfbt4->setDown(false);
               menuinfbt5->setDown(true);
        }
    }
    else
    {
        strimoisdebut->setVisible(false);
         strimoisfin->setVisible(false);
         strianneedebut->setVisible(false);
         strianneefin->setVisible(false);
         stri_de->setVisible(false);
         stri_jusqua->setVisible(false);
         stridivers->setVisible(false);
         menuinfbt1->setDown(false);
         menuinfbt2->setDown(false);
         menuinfbt3->setDown(false);
         menuinfbt4->setDown(false);
         menuinfbt5->setDown(false);
    }
}



