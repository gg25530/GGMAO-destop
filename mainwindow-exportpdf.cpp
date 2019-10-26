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
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPrinter>

void MainWindow::topdf()
{

    QString filename=b.path().c_str();
        filename += "test.pdf";
    int nbColonnes = 10;
    int nbDonnees = b.nbpieces();
    int colonne_width=0;

    QPrinter printer; //The QPrinter class is a paint device that paints on a printer
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageSize(QPrinter::A4);

    //this can be also NativeFormat or PostScriptFormat
    //for details, read QPrinter class documentation
    printer.setOutputFileName(filename);
    QPainter painter; //The QPainter class performs painting on widgets and other paint devices (such as QPrinter)

    //here we start painting to the printer
    if (!painter.begin(&printer))
    {
        QMessageBox::critical(this, "truc", "Fichier pdf non crée");
         return;
    }

    int x = 0, yy=0;
    int y = printer.height()/16; // hauteur d'une ligne
    colonne_width = (printer.width()/nbColonnes);
    QRect r;
    for (int j=0; j<nbColonnes; j++)  // ecriture titre
    {
        QRect required = QRect(); //this represent the required rectangled size
        r = QRect(x, 0, colonne_width, y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
        QString text = "header.at(k)";
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += colonne_width;
    }

    for (int k=0; k<nbDonnees; k++)
    {
            x = 0;
            yy+= 60;
            if (yy > printer.height())
            {
                printer.newPage();

                for (int j=0; j<nbColonnes; j++)  // ecriture titre
                {
                    QRect required = QRect(); //this represent the required rectangled size
                    r = QRect(x, 0, colonne_width, y); //this represent our calculated rectangle size
                    painter.drawRect(r);
                    //now we insert each string of the list into the rectangle
                    QString text = "header.at(k)";
                    //now we draw the text into the given rectangle, using word wrap option.
                    //the last parameter indicates a rectangle in which the text should be enclosed
                    painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
                    //if the calculated height is not enought for drawing the text, we should redraw all rectangles
                     x += colonne_width;
                }
                std::cout << k << " : " << yy << std::endl;
                yy=60;
            }


        for(int l=0; l < nbColonnes; l++)
        {
            QRect required = QRect(); //this represent the required rectangled size
            r = QRect(l*colonne_width, yy, colonne_width, y); //this represent our calculated rectangle size
            painter.drawRect(r);
            //now we insert each string of the list into the rectangle
            QString txt = std::to_string(k).c_str();
            //now we draw the text into the given rectangle, using word wrap option.
            //the last parameter indicates a rectangle in which the text should be enclosed
            painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, txt/*, &required*/);

        }

    }
    std::cout << printer.width() << " : " << printer.height() << std::endl;

    painter.end();




}


void MainWindow::commandesmoistopdf()
{
    std::string filename = "";
    QPrinter printer; //The QPrinter class is a paint device that paints on a printer
    printer.setOutputFormat(QPrinter::PdfFormat);

    filename = b.path();
    filename += "statistiques/commandes-";
    filename += strimoisdebut->currentText().toStdString();
    filename += "-";
    filename += strianneedebut->currentText().toStdString();
    filename += ".pdf";

    printer.setOutputFileName(filename.c_str());
    QPainter painter(&printer); //The QPainter class performs painting on widgets and other paint devices (such as QPrinter)
      chartView->render(&painter);


    int nbDonnees = modelestats->rowCount();
    std::cout << nbDonnees << std::endl;
    int largeur = printer.width()/11;
    int x = 0, yy= chartView->height()+160;
    int y = printer.height()/30; // hauteur d'une ligne
    QRect r;
    for (int j=0; j<nbDonnees; j++)  // ecriture titre
    {
        if((j+1) == nbDonnees)
        {
            x=0;
            yy += y;
            yy+=10;
            y*=2;
            largeur*=2;
             if ((yy+y) > printer.height())
             {
                 printer.newPage();
                 yy=0;
             }
        }

        QRect required = QRect(); //this represent the required rectangled size
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
        QString text = modelestats->item(j,0)->text();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = modelestats->item(j,1)->text();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
          x += printer.width()/9;
          if((j+1)%5 ==0)
          {
             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

          }

    }

    ///////////////////////////////////////////
     nbDonnees = liste_elements_stats.size();
    std::cout << nbDonnees << std::endl;
     largeur = printer.width()/6;
     x = 0;
     yy+= y;
     yy+= 10;
     y = printer.height()/25; // hauteur d'une ligne
     if ((yy+(y*2)) > printer.height())
     {
         printer.newPage();
         yy=0;
     }

     /////////////////  entete details commandes //////
     r = QRect(x,yy,printer.width() , y); //this represent our calculated rectangle size
     painter.drawRect(r);
     //now we insert each string of the list into the rectangle
     QString text = "Detail des commandes";
     //now we draw the text into the given rectangle, using word wrap option.
     //the last parameter indicates a rectangle in which the text should be enclosed
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     //if the calculated height is not enought for drawing the text, we should redraw all rectangles
    yy += y;

  for (int k=0; k<b.nbcommandes(); k++)
  {
    for (int j=0; j<nbDonnees; j++)  // ecriture titre
    {
        if(b.commande_skey(k) == liste_elements_stats[j])
        {
        /////////////////  fournisseur //////
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
         text = b.commande_fournisseur(k).c_str();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// numero de commande /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = b.commande_reference(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// montant ht /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_prix(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// date /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_date(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// destinataire /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_destinataire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// commentaire /////
         r = QRect(x,yy, largeur*2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_commentaire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur*2;

             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

           }
          }


  }
}


void MainWindow::commandesanneetopdf()
{

    std::string filename = "";
    QPrinter printer; //The QPrinter class is a paint device that paints on a printer
    printer.setOutputFormat(QPrinter::PdfFormat);

    filename = b.path();
    filename += "statistiques/commandes-";
    filename += stridivers->currentText().toStdString();
    filename += "-";
    filename += strianneedebut->currentText().toStdString();
    filename += ".pdf";

    printer.setOutputFileName(filename.c_str());
    QPainter painter(&printer); //The QPainter class performs painting on widgets and other paint devices (such as QPrinter)
      chartView->render(&painter);


    int nbDonnees = modelestats->rowCount();
    std::cout << nbDonnees << std::endl;
    int largeur = printer.width()/11;
    int x = 0, yy= chartView->height()+160;
    int y = printer.height()/30; // hauteur d'une ligne
    QRect r;
    for (int j=0; j<nbDonnees; j++)  // ecriture titre
    {
        if((j+1) == nbDonnees)
        {
            x=0;
            yy += y;
            yy+=10;
            y*=2;
            largeur*=2;
             if ((yy+y) > printer.height())
             {
                 printer.newPage();
                 yy=0;
             }
        }

        QRect required = QRect(); //this represent the required rectangled size
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
        QString text = modelestats->item(j,0)->text();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = modelestats->item(j,1)->text();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
          x += printer.width()/9;
          if((j+1)%5 ==0)
          {
             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

          }

    }

    ///////////////////////////////////////////
     nbDonnees = liste_elements_stats.size();
    std::cout << nbDonnees << std::endl;
     largeur = printer.width()/6;
     x = 0;
     yy+= y;
     yy+= 10;
     y = printer.height()/25; // hauteur d'une ligne
     if ((yy+(y*2)) > printer.height())
     {
         printer.newPage();
         yy=0;
     }

     /////////////////  entete details commandes //////
     r = QRect(x,yy,printer.width() , y); //this represent our calculated rectangle size
     painter.drawRect(r);
     //now we insert each string of the list into the rectangle
     QString text = "Detail des commandes";
     //now we draw the text into the given rectangle, using word wrap option.
     //the last parameter indicates a rectangle in which the text should be enclosed
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     //if the calculated height is not enought for drawing the text, we should redraw all rectangles
    yy += y;

  for (int k=0; k<b.nbcommandes(); k++)
  {
    for (int j=0; j<nbDonnees; j++)  // ecriture titre
    {
        if(b.commande_skey(k) == liste_elements_stats[j])
        {
        /////////////////  fournisseur //////
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
         text = b.commande_fournisseur(k).c_str();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// numero de commande /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = b.commande_reference(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// montant ht /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_prix(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// date /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_date(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// destinataire /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_destinataire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// commentaire /////
         r = QRect(x,yy, largeur*2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_commentaire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur*2;

             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

           }
          }


  }

}


void MainWindow::suiviatelierstopdf()
{

}


void MainWindow::suivitechtopdf()
{

    for (uint a=0;a < bar_stacked.size();a++)
    {
        for (int b=0;b < bar_stacked[a]->count();b++)
        {
            std::cout << bar_stacked[a]->label().toStdString() << " , mois : " << b << " : " << bar_stacked[a]->at(b)  << std::endl;
        }
    }

    std::string filename = "";
    QPrinter printer; //The QPrinter class is a paint device that paints on a printer
    printer.setOutputFormat(QPrinter::PdfFormat);

    filename = b.path();
    filename += "statistiques/suivi-bt's-";
    filename += stridivers->currentText().toStdString();
    filename += "-";
    filename += strianneedebut->currentText().toStdString();
    filename += ".pdf";

    printer.setOutputFileName(filename.c_str());
    QPainter painter(&printer); //The QPainter class performs painting on widgets and other paint devices (such as QPrinter)
      chartView->render(&painter);

    uint nbDonnees = bar_stacked.size();
    int cumul=0;
    int largeur = printer.width()/14;
    int x = 0, yy= chartView->height()+160;
    int y = printer.height()/30; // hauteur d'une ligne
    QRect r;
     yy+= y;
     if ((yy+(y*2)) > printer.height())
     {
         printer.newPage();
         yy=0;
     }

     /////////////////  titre tableau //////
     r = QRect(x,yy,largeur*14 , y); //this represent our calculated rectangle size
     painter.drawRect(r);
     //now we insert each string of the list into the rectangle
     QString text = "Detail des bt's  en nombre de bt's";
     //now we draw the text into the given rectangle, using word wrap option.
     //the last parameter indicates a rectangle in which the text should be enclosed
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     //if the calculated height is not enought for drawing the text, we should redraw all rectangles
    yy += y;
    ///////////////////////////////////////////////

    //////////////  entete tableau  //////////
    /////////////////  technicien //////
    r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
    painter.drawRect(r);
     text = stridivers->currentText();
    painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;

     ////////////// janvier /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "janvier";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// fevrier /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "fevrier";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// mars /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "mars";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// avril /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "avril";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// mai /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "mai";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// juin /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "juin";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// juillet /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "juillet";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// aout /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "aout";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// septembre /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "septembre";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// octobre /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "octobre";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// novembre /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "novembre";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// decembre /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "decembre";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     x += largeur;
     /////////////////////////////////////////

     ////////////// total /////
     r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
     painter.drawRect(r);
      text = "Total";
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     /////////////////////////////////////////

     ///////////////////////////////////////////////////////////////////


     yy += y;
    x=0;


    for (uint j=0; j<nbDonnees; j++)  // ecriture titre
    {
        cumul=0;

        /////////////////  technicien //////
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
         text = bar_stacked[j]->label();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// janvier /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = std::to_string((int)bar_stacked[j]->at(0)).c_str();
          cumul += bar_stacked[j]->at(0);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// fevrier /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(1)).c_str();
          cumul += bar_stacked[j]->at(1);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// mars /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(2)).c_str();
          cumul += bar_stacked[j]->at(2);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// avril /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(3)).c_str();
          cumul += bar_stacked[j]->at(3);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// mai /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(4)).c_str();
          cumul += bar_stacked[j]->at(4);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// juin /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(5)).c_str();
          cumul += bar_stacked[j]->at(5);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// juillet /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(6)).c_str();
          cumul += bar_stacked[j]->at(6);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// aout /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(7)).c_str();
          cumul += bar_stacked[j]->at(7);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// septembre /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(8)).c_str();
          cumul += bar_stacked[j]->at(8);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// octobre /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(9)).c_str();
          cumul += bar_stacked[j]->at(9);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// novembre /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(10)).c_str();
          cumul += bar_stacked[j]->at(10);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// decembre /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = std::to_string((int)bar_stacked[j]->at(11)).c_str();
          cumul += bar_stacked[j]->at(11);
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// cumul /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = std::to_string(cumul).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles

             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }


          }



}


void MainWindow::suivianneetopdf()
{

    std::string filename = "";
    QPrinter printer; //The QPrinter class is a paint device that paints on a printer
    printer.setOutputFormat(QPrinter::PdfFormat);

    filename = b.path();
    filename += "statistiques/suivi-";
    filename += stridivers->currentText().toStdString();
    filename += "-";
    filename += strianneedebut->currentText().toStdString();
    filename += ".pdf";

    printer.setOutputFileName(filename.c_str());
    QPainter painter(&printer); //The QPainter class performs painting on widgets and other paint devices (such as QPrinter)
      chartView->render(&painter);


    int nbDonnees = modelestats->rowCount();
    std::cout << nbDonnees << std::endl;
    int largeur = printer.width()/11;
    int x = 0, yy= chartView->height()+160;
    int y = printer.height()/30; // hauteur d'une ligne
    QRect r;
    for (int j=0; j<nbDonnees; j++)  // ecriture titre
    {
        if((j+1) == nbDonnees)
        {
            x=0;
            yy += y;
            yy+=10;
            y*=2;
            largeur*=2;
             if ((yy+y) > printer.height())
             {
                 printer.newPage();
                 yy=0;
             }
        }

        QRect required = QRect(); //this represent the required rectangled size
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
        QString text = modelestats->item(j,0)->text();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = modelestats->item(j,1)->text();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
          x += printer.width()/9;
          if((j+1)%5 ==0)
          {
             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

          }

    }

    ///////////////////////////////////////////
     nbDonnees = liste_elements_stats.size();
    std::cout << nbDonnees << std::endl;
     largeur = printer.width()/6;
     x = 0;
     yy+= y;
     yy+= 10;
     y = printer.height()/25; // hauteur d'une ligne
     if ((yy+(y*2)) > printer.height())
     {
         printer.newPage();
         yy=0;
     }

     /////////////////  entete details commandes //////
     r = QRect(x,yy,printer.width() , y); //this represent our calculated rectangle size
     painter.drawRect(r);
     //now we insert each string of the list into the rectangle
     QString text = "Detail des commandes";
     //now we draw the text into the given rectangle, using word wrap option.
     //the last parameter indicates a rectangle in which the text should be enclosed
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
     //if the calculated height is not enought for drawing the text, we should redraw all rectangles
    yy += y;

  for (int k=0; k<b.nbcommandes(); k++)
  {
    for (int j=0; j<nbDonnees; j++)  // ecriture titre
    {
        if(b.commande_skey(k) == liste_elements_stats[j])
        {
        /////////////////  fournisseur //////
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
         text = b.commande_fournisseur(k).c_str();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// numero de commande /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = b.commande_reference(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// montant ht /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_prix(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// date /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_date(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// destinataire /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_destinataire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// commentaire /////
         r = QRect(x,yy, largeur*2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_commentaire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text/* &required*/);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur*2;

             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

           }
          }


  }

}


void MainWindow::inventairetopdf()

{
    std::string filename = "";
    QPrinter printer; //The QPrinter class is a paint device that paints on a printer
    printer.setOutputFormat(QPrinter::PdfFormat);
    QString aujourdui(QDate::currentDate().toString("dd-MM-yyyy") );
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string temp="";
    std::stringstream convert;
    convert.clear();
    if ((ltm->tm_mday)<10)
    {
        convert << "0";
    }
    convert << (ltm->tm_mday) << "-";

    if ((1 + ltm->tm_mon)<10)
    {
        convert << "0";
    }
    convert << (1 + ltm->tm_mon) << "-";
    convert <<  (1900 + ltm->tm_year);
    temp = convert.str();

    filename = b.path();
    filename += "statistiques/inventaire-";
    filename += temp;
    filename += ".pdf";

    temp = "Inventaire au : ";
    temp += aujourdui.toStdString();
    aujourdui.clear();
    aujourdui.append(temp.c_str());

    printer.setOutputFileName(filename.c_str());
    QPainter painter(&printer); //The QPainter class performs painting on widgets and other paint devices (such as QPrinter)
    std::vector<int> nbpieces;
    std::vector<int> nbreferences;
    std::vector<int> valeurtot_cat;
    nbpieces.clear();
    nbreferences.clear();
    valeurtot_cat.clear();
    int nbDonnees = ptricategorie->count();
    std::cout << nbDonnees << std::endl;
    int largeur = printer.width()/4;
    int x = 0, yy= 30;
    int y = printer.height()/30; // hauteur d'une ligne

    QRect required = QRect(); //this represent the required rectangled size
    painter.setPen(QPen(Qt::black,2));

    /////////////////////// ecriture titre //////
   QRect r = QRect(x,yy,printer.width() , y); //this represent our calculated rectangle size
    painter.drawRect(r);
    //now we insert each string of the list into the rectangle
    //now we draw the text into the given rectangle, using word wrap option.
    //the last parameter indicates a rectangle in which the text should be enclosed
    painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, aujourdui);
    //if the calculated height is not enought for drawing the text, we should redraw all rectangles
     yy += y;
    //////////////////////////////////////////////

    //////////////// ecriture titre tableau //////
     r = QRect(x,yy,printer.width()/4 , y); //this represent our calculated rectangle size
     painter.drawRect(r);
     //now we insert each string of the list into the rectangle
     temp = "categorie";
     aujourdui.clear();
     aujourdui.append(temp.c_str());
     //now we draw the text into the given rectangle, using word wrap option.
     //the last parameter indicates a rectangle in which the text should be enclosed
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, aujourdui);
     //if the calculated height is not enought for drawing the text, we should redraw all rectangles
      x += printer.width()/4;
      r = QRect(x,yy,printer.width()/4 , y); //this represent our calculated rectangle size
      painter.drawRect(r);
      //now we insert each string of the list into the rectangle
      temp = "references";
      aujourdui.clear();
      aujourdui.append(temp.c_str());
      //now we draw the text into the given rectangle, using word wrap option.
      //the last parameter indicates a rectangle in which the text should be enclosed
      painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, aujourdui);
      //if the calculated height is not enought for drawing the text, we should redraw all rectangles
      x += printer.width()/4;
       r = QRect(x,yy,printer.width()/4 , y); //this represent our calculated rectangle size
       painter.drawRect(r);
       //now we insert each string of the list into the rectangle
       temp = "pieces";
       aujourdui.clear();
       aujourdui.append(temp.c_str());
       //now we draw the text into the given rectangle, using word wrap option.
       //the last parameter indicates a rectangle in which the text should be enclosed
       painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, aujourdui);
       //if the calculated height is not enought for drawing the text, we should redraw all rectangles
       x += printer.width()/4;
        r = QRect(x,yy,printer.width()/4 , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
        temp = "valeur totale";
        aujourdui.clear();
        aujourdui.append(temp.c_str());
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, aujourdui);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
        x=0;
         yy += y;
    //////////////////////////////////////////////

    for (int j=0; j<nbDonnees; j++)  // pour chaque categorie boucle
    {
        nbpieces.push_back(0);
        valeurtot_cat.push_back(0);
        nbreferences.push_back(0);
        if(ptricategorie->itemText(j).toStdString()!="")
        {

            for(int pieces=0;pieces < b.nbpieces();pieces++)
            {
                if(ptricategorie->itemText(j).toStdString() == b.pieces_categorie(pieces))
                {
                    nbreferences.back() += 1;
                    nbpieces.back() += std::atoi(b.pieces_qty(pieces).c_str());
                    valeurtot_cat.back() += std::atoi(b.pieces_cout(pieces).c_str());
                }


            }

     //   QRect required = QRect(); //this represent the required rectangled size
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
        QString text = ptricategorie->itemText(j);
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = std::to_string(nbreferences[j]).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = std::to_string(nbpieces[j]).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = std::to_string(valeurtot_cat[j]).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles

             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

    }

    }
/*
    ///////////////////////////////////////////
     nbDonnees = liste_elements_stats.size();
    std::cout << nbDonnees << std::endl;
     largeur = printer.width()/6;
     x = 0;
     yy+= y;
     yy+= 10;
     y = printer.height()/25; // hauteur d'une ligne
     if ((yy+(y*2)) > printer.height())
     {
         printer.newPage();
         yy=0;
     }

     /////////////////  entete details commandes //////
     r = QRect(x,yy,printer.width() , y); //this represent our calculated rectangle size
     painter.drawRect(r);
     //now we insert each string of the list into the rectangle
     QString text = "Detail des commandes";
     //now we draw the text into the given rectangle, using word wrap option.
     //the last parameter indicates a rectangle in which the text should be enclosed
     painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
     //if the calculated height is not enought for drawing the text, we should redraw all rectangles
    yy += y;

  for (int k=0; k<b.nbcommandes(); k++)
  {
    for (int j=0; j<nbDonnees; j++)  // ecriture titre
    {
        if(b.commande_skey(k) == liste_elements_stats[j])
        {
        /////////////////  fournisseur //////
        r = QRect(x,yy,largeur , y); //this represent our calculated rectangle size
        painter.drawRect(r);
        //now we insert each string of the list into the rectangle
         text = b.commande_fournisseur(k).c_str();
        //now we draw the text into the given rectangle, using word wrap option.
        //the last parameter indicates a rectangle in which the text should be enclosed
        painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
        //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// numero de commande /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
          text = b.commande_reference(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// montant ht /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_prix(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// date /////
         r = QRect(x,yy, largeur/2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_date(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur/2;

         ////////////// destinataire /////
         r = QRect(x,yy, largeur, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_destinataire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur;

         ////////////// commentaire /////
         r = QRect(x,yy, largeur*2, y); //this represent our calculated rectangle size
         painter.drawRect(r);
         //now we insert each string of the list into the rectangle
         text = b.commande_commentaire(k).c_str();
         //now we draw the text into the given rectangle, using word wrap option.
         //the last parameter indicates a rectangle in which the text should be enclosed
         painter.drawText(r, Qt::AlignCenter|Qt::TextWordWrap, text);
         //if the calculated height is not enought for drawing the text, we should redraw all rectangles
         x += largeur*2;

             x=0;
             yy += y;
              if ((yy+y) > printer.height())
              {
                  printer.newPage();
                  yy=0;
              }

           }
          }


  }*/
}


void MainWindow::inventairetocsv()
{

    std::string filename = "";
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::string temp="";
    std::stringstream convert;
    convert.clear();
    if ((ltm->tm_mday)<10)
    {
        convert << "0";
    }
    convert << (ltm->tm_mday) << "-";

    if ((1 + ltm->tm_mon)<10)
    {
        convert << "0";
    }
    convert << (1 + ltm->tm_mon) << "-";
    convert <<  (1900 + ltm->tm_year);
    temp = convert.str();

    filename = b.path();
    filename += "statistiques/inventaire-";
    filename += temp;
    filename += ".csv";



    std::ofstream flux(filename.c_str(), std::ios::out|std::ios::trunc);
    if(flux)
    {
        flux << "nom" << ";" << "fabricant" << ";" << "reference" << ";" << "commentaires" << ";" << "fournisseur 1" << ";" << "fournisseur 2" << ";" << "fournisseur 3" << ";" << "lieu de stockage" << ";" << "adresse" << ";" << "categorie" << ";" << "prix" << ";" << "quantité" << ";"  << "montant total" << ";" << "date du dernier controle" <<  ";" << "cle primaire" << ";" << "lien document" << ";" << "lien plan" << ";" << "lien photo" << ";" << std::endl;

        for (int i=0;i < b.nbpieces();i++)
        {
            flux << b.pieces_nom(i) << ";" << b.pieces_fabricant(i) << ";" << b.pieces_reference(i) << ";" << b.pieces_commentaire(i) << ";" << b.pieces_four1(i) << ";" << b.pieces_four2(i) << ";" << b.pieces_four3(i) << ";" << b.pieces_emplacement(i) << ";" << b.pieces_adresse(i) << ";" << b.pieces_categorie(i) << ";" << b.pieces_prix(i) << ";" << b.pieces_qty(i) << ";"  << b.pieces_cout(i) << ";" << b.pieces_date(i) << ";" << b.pieces_key(i) << ";" << b.pieces_liendoc(i) << ";" << b.pieces_lienplan(i) << ";" << b.pieces_lienphoto(i) << ";" << std::endl;
        }

    }
    else
    {

    }
    flux.close();



}




