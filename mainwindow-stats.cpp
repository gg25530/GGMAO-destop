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




void MainWindow::stat_commandes_mois()
{
    type_stat = 0;
    this->tristatsvisible(true);
    this->tri_stat_changed();

}

void MainWindow::stat_commandes_annee()
{
    type_stat = 3;
    this->tristatsvisible(true);
    this->tri_stat_changed();

}


void MainWindow::stat_suivi_annuel()
{
    type_stat = 4;
    this->tristatsvisible(true);
    this->tri_stat_changed();

}


void MainWindow::stat_suivi_tech()
{
    type_stat = 2;
    this->tristatsvisible(true);
    this->tri_stat_changed();

}


void MainWindow::stat_suivi_ateliers()
{
    type_stat = 1;
    this->tristatsvisible(true);
    this->tri_stat_changed();
}


void MainWindow::stat_commandes_mois_maj()
{
    chartView->setChart(chart);
    QPieSlice *slice;
    namesstats.clear();
    valeursstats.clear();
    modelestats->clear();
    int temp=0,mois=1,annee=2018;
    int nb_commandes=0;
    QStringList titre6;
    std::string titre_chart="";
    titre6 <<  "fournisseur" << "montant"  ;
    modelestats->setColumnCount(2);
    modelestats->setHorizontalHeaderLabels(titre6);
    series->clear();
   // time_t now = time(0);
  //  tm *ltm = localtime(&now);
   // mois = (1 + ltm->tm_mon);
    mois = strimoisdebut->currentIndex();
    mois++;
    annee = std::atoi(strianneedebut->currentText().toStdString().c_str());        //(1900 + ltm->tm_year);
    std::vector <std::string> tab;
    b.getlistfournisseurs(tab);
    std::sort(tab.begin(),tab.end());
    liste_elements_stats.clear();
    for(uint j=0; j < tab.size(); j++)
    {
        temp =0;
       namesstats.push_back(tab[j]);
       for(int i =0 ; i < b.nbcommandes(); i++)
        {

           if(namesstats.back() == b.commande_fournisseur(i) && mois == b.commande_mois(i) && annee == b.commande_annee(i))
           {
               temp+= b.commande_prixint(i);
               nb_commandes++;
               liste_elements_stats.push_back(b.commande_skey(i));
           }

        }
       if(temp >0)
       {
           valeursstats.push_back(temp);
       }
       else
       {
           namesstats.pop_back();
       }

    }





    temp =0;
for(uint x=0; x < namesstats.size(); x++)
{
    modelestats->setItem(x, 0, new QStandardItem(QString::fromStdString(namesstats[x])));
    modelestats->setItem(x, 1, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << valeursstats[x]) )->str())));
    temp += valeursstats[x];
    series->append(static_cast<std::ostringstream*>( &(std::ostringstream() << (x+1)) )->str().c_str(),valeursstats[x]);
    slice = series->slices().at(x);
   //  slice->setExploded();
     slice->setLabelVisible();
    // slice->setPen(QPen(Qt::darkGreen, 1));
    // slice->setBrush(/*Qt::green*/);
}
valeursstats.push_back(temp);
namesstats.push_back("total");
modelestats->setItem((namesstats.size()-1), 0, new QStandardItem(QString::fromStdString("total")));
modelestats->setItem((namesstats.size()-1), 1, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << temp) )->str())));
titre_chart = "Commandes de ";
titre_chart += strimoisdebut->currentText().toStdString();
titre_chart+= " ";
titre_chart+= strianneedebut->currentText().toStdString();
titre_chart+= ", montant total : ";
titre_chart+= std::to_string(temp);
titre_chart+= " €";

chart->setTitle(titre_chart.c_str());
}


void MainWindow::stat_commandes_annee_maj()
{
    bar_cout_annee->remove(0,bar_cout_annee->count());
    bar_nb_bt_annee->remove(0,bar_nb_bt_annee->count());
    bar_temps_bt_annee->remove(0,bar_temps_bt_annee->count());
    chartView->setChart(chart2);

    int total_mois=0,nb_commandes=0;
    int mois_maxi=0;
    int total_annee=0;
    modelestats->clear();
    QStringList titre6;
    if(stridivers->currentText() == "budget-mensuel") chart2->setTitle("budget mensuel année " + strianneedebut->currentText());
    else chart2->setTitle("details budget " + stridivers->currentText() + " année " + strianneedebut->currentText());

    titre6 <<  "mois" << "montant"  ;
    modelestats->setColumnCount(2);
    modelestats->setHorizontalHeaderLabels(titre6);
    liste_elements_stats.clear();
    for (int mois=1;mois < 13;mois++)
    {
        total_mois=0;
        nb_commandes=0;
        for (int commande_num=0;commande_num < b.nbcommandes();commande_num++)
        {
            if(b.commande_mois(commande_num) == mois && b.commande_annee(commande_num) == strianneedebut->currentText().toInt())
            {
               if(stridivers->currentText() == "budget-mensuel")
               {
                total_mois += std::atoi(b.commande_prix(commande_num).c_str());
                nb_commandes++;
                liste_elements_stats.push_back(b.commande_skey(commande_num));
               }
               else if(stridivers->currentText().toStdString() == b.commande_fournisseur(commande_num))
               {
                   total_mois += std::atoi(b.commande_prix(commande_num).c_str());
                   nb_commandes++;
                   liste_elements_stats.push_back(b.commande_skey(commande_num));
               }
            }
        }

        modelestats->setItem(mois-1, 0, new QStandardItem(strimoisdebut->itemText(mois-1)));
        modelestats->setItem(mois-1, 1, new QStandardItem(QString::fromStdString(std::to_string(total_mois))));
        *bar_cout_annee << total_mois;
        if(total_mois > mois_maxi) mois_maxi = total_mois;
        total_annee += total_mois;
    }

    modelestats->setItem(12, 0, new QStandardItem("total"));
    modelestats->setItem(12, 1, new QStandardItem(QString::fromStdString(std::to_string(total_annee))));

    axisY->setRange(0,mois_maxi);
    axisX->setCategories(categories);


}

void MainWindow::stat_suivi_annee_maj()
{

    bar_cout_annee->remove(0,bar_cout_annee->count());
    bar_nb_bt_annee->remove(0,bar_nb_bt_annee->count());
    bar_temps_bt_annee->remove(0,bar_temps_bt_annee->count());
    int total_mois=0,nb_commandes=0;
    int total_mois2=0;
    modelestats->clear();
    QStringList titre6;

  if(stridivers->currentText().toStdString() == "fournisseurs")
    {
      chartView->setChart(chart2);
    chart2->setTitle("suivi annuel fournisseurs, année " + strianneedebut->currentText());
    int fournisseur_maxi=0;
    titre6.clear();
    titre6 <<  "fournisseur" << "cumul" << "commandes"  ;
    modelestats->setColumnCount(3);
    modelestats->setHorizontalHeaderLabels(titre6);
    titre6.clear();
    namesstats.clear();
    valeursstats.clear();
    modelestats->clear();
    nb_commandes_four_stats.clear();
    int temp=0,annee=2018;
    int nb_commandes=0;
    std::string titre_chart="";
    annee = std::atoi(strianneedebut->currentText().toStdString().c_str());        //(1900 + ltm->tm_year);
    std::vector <std::string> tab;
    b.getlistfournisseurs(tab);
    std::sort(tab.begin(),tab.end());

    for(uint j=0; j < tab.size(); j++)
    {
        temp =0;
        nb_commandes =0;
       namesstats.push_back(tab[j]);
       for(int i =0 ; i < b.nbcommandes(); i++)
        {

           if(namesstats.back() == b.commande_fournisseur(i)  && annee == b.commande_annee(i))
           {
               temp+= b.commande_prixint(i);
               nb_commandes++;
               liste_elements_stats.push_back(b.commande_skey(i));
           }

        }
       if(temp >0)
       {
           valeursstats.push_back(temp);
           nb_commandes_four_stats.push_back(nb_commandes);

       }
       else
       {
           namesstats.pop_back();
       }

    }

for(uint x=0; x < namesstats.size(); x++)
{
    titre6.push_back(namesstats[x].c_str());
    if(valeursstats[x] > fournisseur_maxi) fournisseur_maxi = valeursstats[x];
    modelestats->setItem(x, 0, new QStandardItem(namesstats[x].c_str()));
    modelestats->setItem(x, 1, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << valeursstats[x]) )->str())));
    modelestats->setItem(x, 2, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << nb_commandes_four_stats[x]) )->str())));
    *bar_cout_annee << valeursstats[x];

}
    axisY->setRange(0,fournisseur_maxi);
    axisX->setCategories(titre6);
    }
    else if(stridivers->currentText().toStdString() == "destinataires")
    {
    chartView->setChart(chart3);
    series3->clear();
    chart3->setTitle("suivi annuel commandes par destinataire, année " + strianneedebut->currentText());
    int fournisseur_maxi=0;
    titre6.clear();


    modelestats->clear();
    nb_commandes_four_stats.clear();
    int temp=0,annee=2018;
    int nb_commandes=0;
    std::string titre_chart="";
    annee = std::atoi(strianneedebut->currentText().toStdString().c_str());        //(1900 + ltm->tm_year);
    std::vector <std::string> tab;
    b.getlistdestinataires(tab);
    std::sort(tab.begin(),tab.end());
    bar_stacked.clear();
    titre6 <<"mois";

    for(int dest=0; dest < tab.size();dest++)
    {
        bar_stacked.push_back(new QBarSet(tab[dest].c_str()));
        titre6 << tab[dest].c_str();
        series3->append(bar_stacked.back());
    }
    std::cout << bar_stacked.size() << std::endl;

     titre6 << "cumul"  ;
    modelestats->setColumnCount(2+tab.size());
    modelestats->setHorizontalHeaderLabels(titre6);
    titre6.clear();
  for(int mois=1;mois < 13;mois++)
  {
      total_mois =0;
      valeursstats.clear();

    for(uint j=0; j < tab.size(); j++)
    {
        temp =0;
        nb_commandes =0;
       for(int i =0 ; i < b.nbcommandes(); i++)
        {

           if(tab[j] == b.commande_destinataire(i) && mois == b.commande_mois(i) && annee == b.commande_annee(i))
           {
               temp+= b.commande_prixint(i);
               nb_commandes++;
           }

        }

           valeursstats.push_back(temp);



    }

        for(uint x=0; x < tab.size(); x++)
{
    modelestats->setItem(mois-1, x+1, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << valeursstats[x]) )->str())));
    *bar_stacked[x] << valeursstats[x];
    total_mois += valeursstats[x];
}
        modelestats->setItem(mois-1, tab.size()+1, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << total_mois) )->str())));
        modelestats->setItem(mois-1, 0, new QStandardItem(strimoisdebut->itemText(mois-1)));
        if(total_mois2 < total_mois) total_mois2 = total_mois;
  }
    axisY2->setRange(0,total_mois2);
    axisX2->setCategories(categories);
        }

}


void MainWindow::stat_suivi_tech_maj()
{

    bar_cout_annee->remove(0,bar_cout_annee->count());
    bar_nb_bt_annee->remove(0,bar_nb_bt_annee->count());
    bar_temps_bt_annee->remove(0,bar_temps_bt_annee->count());
    int total_mois=0,nb_commandes=0;
    int total_mois2=0;
    modelestats->clear();
    QStringList titre6;


    chartView->setChart(chart3);
    series3->clear();
    if(stridivers->currentText()== "techniciens") chart3->setTitle("suivi annuel bt's par technicien, année " + strianneedebut->currentText());
    else if(stridivers->currentText()== "ateliers") chart3->setTitle("suivi annuel bt's par atelier, année " + strianneedebut->currentText());
    int fournisseur_maxi=0;
    titre6.clear();


    modelestats->clear();
    nb_commandes_four_stats.clear();
    int temp=0,annee=2018;
    std::string titre_chart="";
    annee = std::atoi(strianneedebut->currentText().toStdString().c_str());        //(1900 + ltm->tm_year);
    std::vector <std::string> tab;
    tab.clear();
    if(stridivers->currentText()== "techniciens")     b.getlisttech(tab);
    else if(stridivers->currentText()== "ateliers")     b.getlistatelier(tab);
    else if(stridivers->currentText()== "type")     b.getlisttypetaf(tab);
    std::sort(tab.begin(),tab.end());
    bar_stacked.clear();
    titre6 <<"mois";

    for(int dest=0; dest < tab.size();dest++)
    {
        bar_stacked.push_back(new QBarSet(tab[dest].c_str()));
        titre6 << tab[dest].c_str();
        series3->append(bar_stacked.back());
    }

     titre6 << "cumul"  ;
    modelestats->setColumnCount(2+tab.size());
    modelestats->setHorizontalHeaderLabels(titre6);
    titre6.clear();
  for(int mois=1;mois < 13;mois++)
  {
      total_mois =0;
      valeursstats.clear();

    for(uint j=0; j < tab.size(); j++)
    {
        temp =0;
        nb_commandes =0;

       for(int i =0 ; i < b.nbbts(); i++)
        {

           if( mois == b.bts_mois(i) && annee == b.bts_annee(i))
           {
               if(tab[j] == b.bt_tech(i) && stridivers->currentText()== "techniciens")
               {
                   temp++;
                   nb_commandes++;
               }
               else if(tab[j] == b.bt_atelier(i) && stridivers->currentText()== "ateliers")
               {
                   temp++;
                   nb_commandes++;
               }
               else if(tab[j] == b.bt_type(i) && stridivers->currentText()== "type")
               {
                   temp++;
                   nb_commandes++;
               }
           }

        }

           valeursstats.push_back(temp);



    }

        for(uint x=0; x < tab.size(); x++)
{
    modelestats->setItem(mois-1, x+1, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << valeursstats[x]) )->str())));
    *bar_stacked[x] << valeursstats[x];
    total_mois += valeursstats[x];
}
        modelestats->setItem(mois-1, tab.size()+1, new QStandardItem(QString::fromStdString(static_cast<std::ostringstream*>( &(std::ostringstream() << total_mois) )->str())));
        modelestats->setItem(mois-1, 0, new QStandardItem(strimoisdebut->itemText(mois-1)));
        if(total_mois2 < total_mois) total_mois2 = total_mois;
  }
    axisY2->setRange(0,total_mois2);
    axisX2->setCategories(categories);



}


void MainWindow::stat_suivi_ateliers_maj()
{

}





