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
#include "unthread.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QPrinter>

QT_CHARTS_USE_NAMESPACE


MainWindow::MainWindow()
    : QMainWindow()
{

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QMenu *menuparametres = menuBar()->addMenu("&Parametres");
    QMenu *menuabout = menuBar()->addMenu("&A propos");
    QAction *ouvrir = new QAction("&Ouvrir",this);
    QAction *enregistrer = new QAction("&Enregistrer",this);
    QAction *quitter = new QAction("Quitter",this);
    QAction *options = new QAction("options",this);
    QAction *exporter = new QAction("exporter",this);
    QAction *importer = new QAction("importer",this);
    QAction *about = new QAction("Licence",this);
    menuFichier->addAction(ouvrir);
    menuFichier->addAction(enregistrer);
    menuFichier->addAction(quitter);
    menuparametres->addAction(options);
    menuparametres->addAction(exporter);
    menuparametres->addAction(importer);
    menuabout->addAction(about);
    modelepieces = new QStandardItemModel(10, 17);
    modelemachinespieces = new QStandardItemModel(10,17);
    modelemachinesbt = new QStandardItemModel(10,9);
    modelebt = new QStandardItemModel(10, 9);
    modelecommandes = new QStandardItemModel(10, 7);
    modeletables = new QStandardItemModel(10, 7);
    modelestats = new QStandardItemModel(2, 2);
    UnThread *t1;




    // 2 : Créer les pages, en utilisant un widget parent pour contenir chacune des pages

    QWidget *page1 = new QWidget;
    QWidget *page2 = new QWidget;
    QWidget *page3 = new QWidget;
    QWidget *page4 = new QWidget;
    QWidget *page5 = new QWidget;
    QWidget *page6 = new QWidget;
    QWidget *page7 = new QWidget;

    // 3 : Créer le contenu des pages de widgets


    // Page 1    ///// pieces  ///////////////
     ptri = new QCheckBox;
     ptri->setText("tri");
     ptrinom = new QLineEdit;
     ptrireference = new QLineEdit;
     ptricommentaire = new QLineEdit;
     ptrifournisseur = new QComboBox;
     ptrifabricant = new QComboBox;
     ptricategorie = new QComboBox;
     ptriemplacement = new QLineEdit;
     ptriadresse = new QLineEdit;
     ptridatea = new QLineEdit;
     ptridatea->setMaxLength(10);
     ptridatea->setInputMask("00-00-0000");
     ptridateb = new QLineEdit;
     ptridateb->setMaxLength(10);
     ptridateb->setInputMask("00-00-0000");
      pttrireference = new QLabel;
      pttrinom = new QLabel;
      pttricommentaire = new QLabel;
      pttrifournisseur = new QLabel;
      pttrifabricant = new QLabel;
      pttricategorie = new QLabel;
      pttriemplacement = new QLabel;
      pttriadresse = new QLabel;
      pttridate = new QLabel;
      pttrireference->setText("reference");
      pttrinom->setText("nom");
      pttricommentaire->setText("com");
      pttrifournisseur->setText("fournisseur");
      pttrifabricant->setText("fabricant");
      pttricategorie->setText("categorie");
      pttriemplacement->setText("emplacement");
      pttriadresse->setText("adresse");
      pttridate->setText("controlé entre le");
    QVBoxLayout *vboxp1 = new QVBoxLayout;
    vue = new QTableView;
    vue->setSelectionBehavior(QAbstractItemView::SelectRows);
    vue->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList titre;
    titre <<  "nom" << "fabricant" << "reference" << "commentaires" << "fournisseur 1" << "fournisseur 2" << "fournisseur 3" << "emplacement" << "adresse" << "categorie"<< "doc" << "plan" << "photo"  << "prix" << "quantité" << "controlée le :" << "n°";
    modelepieces->setHorizontalHeaderLabels(titre);
    vue->setModel(modelepieces);
    vboxp1->addWidget(vue);
    page1->setLayout(vboxp1);
    ptri->setChecked(false);
    tablopiecesint.clear();
    ///////////////////////////////////////////



    // Page 2    //////// machines  ///////

    QGridLayout *vboxp2 = new QGridLayout;
    QVBoxLayout *p2ss1 = new QVBoxLayout;
    QVBoxLayout *p2ss2 = new QVBoxLayout;
     listeatelier = new QComboBox;
     listemachine = new QComboBox;
     listedoc = new QComboBox;
     reference = new QLabel;
     date = new QLabel;
     commentaire = new QLabel;
     commentaire->setStyleSheet("border: 1px solid black");
     fabricant = new QLabel;
    QPushButton *bp_doc = new QPushButton("visualiser", this);

    QWidget *p2ong1 = new QWidget;
    QWidget *p2ong2 = new QWidget;

    v2pieces = new QTableView;
    QTableView *v2bt = new QTableView;

    QStringList titrelistebt;
    QStringList titrelistepieces;

    titrelistebt << "tech" << "type de bt" << "date"  << "atelier" << "machine" << "temps d'inter" << "commentaires" << "controlée le :"  << "clef";
    titrelistepieces << "n°" << "prix" << "quantité" << "nom" << "fabricant" << "reference" << "commentaires" << "controlée le :" << "fournisseur 1" << "fournisseur 2" << "fournisseur 3" << "emplacement" << "adresse" << "categorie"<< "doc" << "plan" << "photo";

    modelemachinespieces->setHorizontalHeaderLabels(titrelistepieces);
    v2pieces->setModel(modelemachinespieces);
    v2pieces->setSelectionBehavior(QAbstractItemView::SelectRows);
    v2pieces->setSelectionMode(QAbstractItemView::SingleSelection);
    modelemachinesbt->setHorizontalHeaderLabels(titrelistebt);
    v2bt->setModel(modelemachinesbt);
    p2ss2->addWidget(v2bt);
    p2ong2->setLayout(p2ss2);
    p2ss1->addWidget(v2pieces);
    p2ong1->setLayout(p2ss1);
    ongletsp2 = new QTabWidget;
    ongletsp2->addTab(p2ong1, "pieces");
    ongletsp2->addTab(p2ong2, "BT's");
vboxp2->addWidget(listeatelier, 0, 0,1,4);
vboxp2->addWidget(listemachine, 0, 4,1,4);
vboxp2->addWidget(new QLabel("fabricant :"),0,8,1,2);
vboxp2->addWidget(fabricant,0,10,1,2);
vboxp2->addWidget(new QLabel("n° de serie :"),0,12,1,2);
vboxp2->addWidget(reference,0,14,1,2);
vboxp2->addWidget(new QLabel("date d'achat :"),0,16,1,2);
vboxp2->addWidget(date,0,18,1,2);
vboxp2->addWidget(new QLabel("informations :"),2,0,1,4);
vboxp2->addWidget(commentaire,3,0,2,11);
vboxp2->addWidget(new QLabel("docs :"),3,11,1,3);
vboxp2->addWidget(ongletsp2,5,0,16,20);
vboxp2->addWidget(listedoc, 3,13,1, 5);
vboxp2->addWidget(bp_doc, 3,18,1, 2);

    page2->setLayout(vboxp2);
    ///////////////////////////////////////////



    // Page 3   ///////////  BT's  //////////////
    btri = new QCheckBox;
    btri->setText("tri");
    btri->setChecked(false);
     btrilu = new QComboBox;
     btrilu->addItem(QString::fromStdString("oui"));
     btrilu->addItem(QString::fromStdString("non"));
     btrilu->addItem(QString::fromStdString(""));
     btricommentaire = new QLineEdit;
     btridatea = new QLineEdit;
     btridatea->setMaxLength(10);
     btridatea->setInputMask("00-00-0000");
     btridateb = new QLineEdit;
     btridateb->setMaxLength(10);
     btridateb->setInputMask("00-00-0000");
     btritech = new QComboBox;
     btriatelier = new QComboBox;
     btritype = new QComboBox;
     btrimachine = new QComboBox;
     bttricommentaire = new QLabel;
     bttrilu = new QLabel;
     bttridate = new QLabel;
     bttritech = new QLabel;
     bttriatelier = new QLabel;
     bttritype = new QLabel;
     bttrimachine = new QLabel;
     bttricommentaire->setText("commentaire");
     bttrilu->setText("verifié");
     bttridate->setText("entre");
     bttritech->setText("tech");
     bttriatelier->setText("atelier");
     bttritype->setText("type");
     bttrimachine->setText("machine");
    QVBoxLayout *vboxp3 = new QVBoxLayout;
     vue3 = new QTableView;
     vue3->setSelectionBehavior(QAbstractItemView::SelectRows);
     vue3->setSelectionMode(QAbstractItemView::SingleSelection);
    QStringList titre3;
    titre3 << "tech" << "type de bt" << "date" << "atelier" << "machine" << "temps d'inter" << "commentaires" << "visé :"  << "clef";
    modelebt->setHorizontalHeaderLabels(titre3);
    vue3->setModel(modelebt);
    vboxp3->addWidget(vue3);
    page3->setLayout(vboxp3);
    ///////////////////////////////////////////



    // Page 4   ///////////  commandes  /////////
     ctrireference = new QLineEdit;
     ctricommentaire = new QLineEdit;
     ctrifournisseur = new QComboBox;
     ctridestinataire = new QComboBox;
     ctridatea = new QLineEdit;
     ctridatea->setMaxLength(10);
     ctridatea->setInputMask("00-00-0000");
     ctridateb = new QLineEdit;
     ctridateb->setMaxLength(10);
     ctridateb->setInputMask("00-00-0000");
     cttrireference = new QLabel;
     cttricommentaire = new QLabel;
     cttrifournisseur = new QLabel;
     cttridestinataire = new QLabel;
     cttridate = new QLabel;
     cttrireference->setText("n° commande");
     cttricommentaire->setText("commentaire");
     cttrifournisseur->setText("fournisseur");
     cttridestinataire->setText("destinataire");
     cttridate->setText("entre");
     ctri = new QCheckBox;
     ctri->setText("tri");
     ctri->setChecked(false);
    QVBoxLayout *vboxp4 = new QVBoxLayout;
    vue4 = new QTableView;
    QStringList titre4;
    titre4 << "fournisseur" << "n°de commande" << "montant ht" << "date" << "destinataire" << "commentaires" << "clef" ;
    modelecommandes->setHorizontalHeaderLabels(titre4);
    vue4->setSelectionBehavior(QAbstractItemView::SelectRows);
    vue4->setSelectionMode(QAbstractItemView::SingleSelection);
    vue4->setModel(modelecommandes);
    vboxp4->addWidget(vue4);
    page4->setLayout(vboxp4);
    ///////////////////////////////////////////



    // Page 5  ///////  tables  ////////////////////////

    QVBoxLayout *vboxp5 = new QVBoxLayout;
    vue5 = new QTableView;
    QStringList titre5;
    titre5 << "tech's" << "atelier" << "type de bt" << "fournisseurs" << "fabricants" << "destinataires" << "categories"  ;
    modeletables->setHorizontalHeaderLabels(titre5);
    vue5->setModel(modeletables);
    vue5->setSelectionBehavior(QAbstractItemView::SelectItems);
    vue5->setSelectionMode(QAbstractItemView::SingleSelection);
    vboxp5->addWidget(vue5);
    page5->setLayout(vboxp5);
    ///////////////////////////////////////////

    // Page 6  ///////  statistiques  ////////////////////////

    namesstats.clear();
    valeursstats.clear();
    type_stat = 0;  // cf ligne 708
    QHBoxLayout *vboxp6 = new QHBoxLayout;
    vue6 = new QTableView;
    QStringList titre6;
    titre6 <<  "fournisseur" << "montant"  ;
    modelestats->setHorizontalHeaderLabels(titre6);
    vue6->setModel(modelestats);
    vboxp6->addWidget(vue6,1);
    strimoisdebut = new QComboBox;
    strimoisfin = new QComboBox;
    strianneedebut = new QComboBox;
    strianneefin = new QComboBox;
    for (int mois = 1;mois <13;mois++)
    {
        switch (mois)
        {
        case 1 :
          strimoisdebut->addItem(QString::fromStdString("janvier"));
          strimoisfin->addItem(QString::fromStdString("janvier"));
        break;
        case 2 :
            strimoisdebut->addItem(QString::fromStdString("fevrier"));
            strimoisfin->addItem(QString::fromStdString("fevrier"));
        break;
        case 3 :
            strimoisdebut->addItem(QString::fromStdString("mars"));
            strimoisfin->addItem(QString::fromStdString("mars"));
        break;
        case 4 :
            strimoisdebut->addItem(QString::fromStdString("avril"));
            strimoisfin->addItem(QString::fromStdString("avril"));
        break;
        case 5 :
            strimoisdebut->addItem(QString::fromStdString("mai"));
            strimoisfin->addItem(QString::fromStdString("mai"));
        break;
        case 6 :
            strimoisdebut->addItem(QString::fromStdString("juin"));
            strimoisfin->addItem(QString::fromStdString("juin"));
        break;
        case 7 :
            strimoisdebut->addItem(QString::fromStdString("juillet"));
            strimoisfin->addItem(QString::fromStdString("juillet"));
        break;
        case 8 :
            strimoisdebut->addItem(QString::fromStdString("aout"));
            strimoisfin->addItem(QString::fromStdString("aout"));
        break;
        case 9 :
            strimoisdebut->addItem(QString::fromStdString("septembre"));
            strimoisfin->addItem(QString::fromStdString("septembre"));
        break;
        case 10 :
            strimoisdebut->addItem(QString::fromStdString("octobre"));
            strimoisfin->addItem(QString::fromStdString("octobre"));
        break;
        case 11 :
            strimoisdebut->addItem(QString::fromStdString("novembre"));
            strimoisfin->addItem(QString::fromStdString("novembre"));
        break;
        case 12 :
            strimoisdebut->addItem(QString::fromStdString("decembre"));
            strimoisfin->addItem(QString::fromStdString("decembre"));
        break;
        default :
            strimoisdebut->addItem(QString::fromStdString(""));
            strimoisfin->addItem(QString::fromStdString(""));
        ;
        }
    }
    for(int annee=2000;annee < 2048 ; annee++)
    {
        strianneedebut->addItem(QString::fromStdString(std::to_string(annee)));
        strianneefin->addItem(QString::fromStdString(std::to_string(annee)));
    }

     stridivers = new QComboBox;
     stri_de = new QLabel(" de ");
     stri_jusqua = new QLabel(" jusqu'a ");



    /////////////pie serie //////////
    series = new QPieSeries();
    ///////////////////////////////

    ////////////bar serie 2  /////////
     series2 = new QBarSeries();
     bar_cout_annee = new QBarSet("cout mensuel");
     bar_nb_bt_annee = new QBarSet("nb bt's mensuel");
     bar_temps_bt_annee = new QBarSet("temps total bt's");
     series2->append(bar_cout_annee);
     series2->append(bar_nb_bt_annee);
     series2->append(bar_temps_bt_annee);
     /////////////////////////////////

     //////////// bar stacked serie 3 /////
      series3 = new QStackedBarSeries();
     bar_stacked.clear();


     ///////////chart //////////////
     chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->legend()->hide();
    ////////////////////////////////

    ///////////chart2 bar chart //////////////
    chart2 = new QChart();
   chart2->addSeries(series2);
   chart2->setTitle("cout_mensuel");

   chart2->legend()->hide();
   categories.clear();
   categories << "Jan" << "Fev" << "Mars" << "Avril" << "Mai" << "Juin" << "jui" << "aout" << "sept" << "oct" << "nov" << "dec" ;
   axisX = new QBarCategoryAxis();
   axisX->append(categories);
   chart2->addAxis(axisX, Qt::AlignBottom);
   series2->attachAxis(axisX);

   axisY = new QValueAxis();
   axisY->setRange(0,300);
   chart2->addAxis(axisY, Qt::AlignLeft);
   series2->attachAxis(axisY);
   ////////////////////////////////

   ///////////chart3 bar stacked //////////////
   chart3 = new QChart();
  chart3->addSeries(series3);
  chart3->setTitle("suivi par destinataire");

  chart3->legend()->setVisible(true);

  axisX2 = new QBarCategoryAxis();
  axisX2->append(categories);
  chart3->addAxis(axisX2, Qt::AlignBottom);
  series3->attachAxis(axisX2);

  axisY2 = new QValueAxis();
  axisY2->setRange(0,300);
  chart3->addAxis(axisY2, Qt::AlignLeft);
  series3->attachAxis(axisY2);
  ////////////////////////////////

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    vboxp6->addWidget(chartView,2);
  ////////////////////////////////




    page6->setLayout(vboxp6);
    ///////////////////////////////////////////

    // Page 7    //////// fournisseurs  ///////

    QGridLayout *vboxp7 = new QGridLayout;
     p7_fournisseur = new QComboBox;
      p7_num_portable = new QLineEdit("");
      p7_num_bureau = new QLineEdit("");
      p7_name_commercial = new QLineEdit("");
      p7_num_client = new QLineEdit("");
      p7_num_contrat = new QLineEdit("");
      p7_adresse_postale = new QLineEdit("");
      p7_mail1 = new QLineEdit("");
      p7_mail2 = new QLineEdit("");
      p7_commentaires = new QTextEdit("");

vboxp7->addWidget(p7_fournisseur, 0, 0);
vboxp7->addWidget(new QLabel("numero bureau :"),1,0);
vboxp7->addWidget(new QLabel("numero portable :"),1,2);
vboxp7->addWidget(p7_num_bureau, 2, 0);
vboxp7->addWidget(p7_num_portable, 2, 2);
vboxp7->addWidget(new QLabel("nom commercial :"),3,0);
vboxp7->addWidget(new QLabel("numero de contrat :"),3,2);
vboxp7->addWidget(new QLabel("numero de client :"),3,3);
vboxp7->addWidget(p7_name_commercial, 4,0);
vboxp7->addWidget(p7_num_contrat, 4, 2);
vboxp7->addWidget(p7_num_client, 4, 3);
vboxp7->addWidget(new QLabel("e-mail n°1 :"),5,0);
vboxp7->addWidget(new QLabel("e-mail n°2 :"),5,2);
vboxp7->addWidget(p7_mail1, 6, 0);
vboxp7->addWidget(p7_mail2, 6, 2);
vboxp7->addWidget(new QLabel("informations diverses :"),7,0);
vboxp7->addWidget(p7_commentaires, 8, 0,4,4);



    page7->setLayout(vboxp7);
    ///////////////////////////////////////////


    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent

    onglets = new QTabWidget;
    onglets->setGeometry(10, 10, 780, 480);
    onglets->addTab(page1, "pieces");
    onglets->addTab(page2, "machines");
    onglets->addTab(page3, "BT's");
    onglets->addTab(page4, "commandes");
    onglets->addTab(page5, "tables");
    onglets->addTab(page6, "statistiques");
    onglets->addTab(page7, "fournisseurs");
    /////////////////////////////////////////////////////////////////////////////////////////////////



    //   menu inferieur /////////onglet /////// pieces     ///////// machines ////  bt's ///////////  commandes  //////   tables  //////


    menuinfbt1 = new QPushButton("....."); //////  grisé //////  rechercher   //// rechercher   /////  ajouter tech  ///
    menuinfbt2 = new QPushButton("ajouter");    //////  ajouter ////  ajouter      ////  ajouter    //////  ajouter atelier //
    menuinfbt3 = new QPushButton("modifier");  //////  modifier ///  modifier   /////   modifier   ///////  ajouter type de bt //
    menuinfbt4 = new QPushButton("supprimer");  /////  supprimer ///  supprimer /////   supprimer   //////  ajouter fournisseur //
    menuinfbt5 = new QPushButton("ajouter a machine");  //////  exporter  ///  exporter  /////   exporter     /////  ajouter fabricant  //
    menuinfbt6 = new QPushButton("imprimer");  ///////  grisé  /////  gerer   ///////   gerer      ///////  ajouter destinataire ///
    QHBoxLayout *hboxinf = new QHBoxLayout;
        hboxinf->addWidget(menuinfbt1);
        hboxinf->addWidget(menuinfbt2);
        hboxinf->addWidget(menuinfbt3);
        hboxinf->addWidget(menuinfbt4);
        hboxinf->addWidget(menuinfbt5);
        hboxinf->addWidget(menuinfbt6);
////////////////////////////////////////
        ///////// tri pieces  //////
        hboxtri1 = new QHBoxLayout;
        hboxtri2 = new QHBoxLayout;
        hboxtri1->addWidget(ptri);
        hboxtri1->addWidget(pttrinom);
        hboxtri1->addWidget(ptrinom);
        hboxtri1->addWidget(pttrireference);
        hboxtri1->addWidget(ptrireference);
        hboxtri1->addWidget(pttricommentaire);
        hboxtri1->addWidget(ptricommentaire);
        hboxtri1->addWidget(pttriemplacement);
        hboxtri1->addWidget(ptriemplacement);
        hboxtri1->addWidget(ptridatea);
        hboxtri1->addWidget(pttridate);
        hboxtri1->addWidget(ptridateb);
        hboxtri2->addWidget(pttrifournisseur,1);
        hboxtri2->addWidget(ptrifournisseur,3);
        hboxtri2->addWidget(pttrifabricant,1);
        hboxtri2->addWidget(ptrifabricant,3);
        hboxtri2->addWidget(pttricategorie,1);
        hboxtri2->addWidget(ptricategorie,3);
        hboxtri2->addWidget(pttriadresse,1);
        hboxtri2->addWidget(ptriadresse,1);

        ///////// tri bt  //////
        hboxtri3 = new QHBoxLayout;
        hboxtri4 = new QHBoxLayout;
        hboxtri3->addWidget(btri);
        hboxtri3->addWidget(bttricommentaire);
        hboxtri3->addWidget(btricommentaire);
        hboxtri3->addWidget(bttrilu);
        hboxtri3->addWidget(btrilu);
        hboxtri3->addWidget(btridatea);
        hboxtri3->addWidget(bttridate);
        hboxtri3->addWidget(btridateb);
        hboxtri4->addWidget(bttritech);
        hboxtri4->addWidget(btritech);
        hboxtri3->addWidget(bttritype);
        hboxtri3->addWidget(btritype);
        hboxtri4->addWidget(bttriatelier);
        hboxtri4->addWidget(btriatelier);
        hboxtri4->addWidget(bttrimachine);
        hboxtri4->addWidget(btrimachine);

        ///////// tri commandes  //////
        hboxtri5 = new QHBoxLayout;
        hboxtri6 = new QHBoxLayout;
        hboxtri5->addWidget(ctri);
        hboxtri5->addWidget(cttricommentaire);
        hboxtri5->addWidget(ctricommentaire);
        hboxtri5->addWidget(cttrireference);
        hboxtri5->addWidget(ctrireference);
        hboxtri6->addWidget(cttrifournisseur,2);
        hboxtri6->addWidget(ctrifournisseur,3);
        hboxtri6->addWidget(cttridestinataire,2);
        hboxtri6->addWidget(ctridestinataire,3);
        hboxtri6->addWidget(ctridatea,2);
        hboxtri6->addWidget(cttridate,1);
        hboxtri6->addWidget(ctridateb,2);

        ///////////  tri stats ////
        hboxtri7 = new QHBoxLayout;
        hboxtri8 = new QHBoxLayout;
        hboxtri7->addWidget(stri_de);
        hboxtri7->addWidget(strimoisdebut);
        hboxtri7->addWidget(strianneedebut);
        hboxtri7->addWidget(stri_jusqua);
        hboxtri7->addWidget(strimoisfin);
        hboxtri7->addWidget(strianneefin);
        hboxtri7->addWidget(stridivers);

    //////////////////////////////////////////////

this->tripiecesvisible(true);
this->tribtvisible(false);
this->tricommandevisible(false);
this->tristatsvisible(false);
//this->setFixedWidth(QApplication::desktop()->availableGeometry().width()/2);
//this->setFixedHeight(QApplication::desktop()->availableGeometry().height()/2);
  this->setBaseSize(QApplication::desktop()->availableGeometry().width()/2, QApplication::desktop()->availableGeometry().height()/2);
QGridLayout *vboxgen = new QGridLayout;
    vboxgen->addWidget(onglets,0,1,9,1);
    vboxgen->addLayout(hboxinf,10,1,1,1); // menu inf
    vboxgen->addLayout(hboxtri1,11,1,1,1); //tri pieces
    vboxgen->addLayout(hboxtri2,12,1,1,1); //tri pieces
    vboxgen->addLayout(hboxtri3,11,1,1,1); //tri bt
    vboxgen->addLayout(hboxtri4,12,1,1,1); //tri bt
    vboxgen->addLayout(hboxtri5,11,1,1,1); //tri commandes
    vboxgen->addLayout(hboxtri6,12,1,1,1); //tri commandes
    vboxgen->addLayout(hboxtri7,11,1,1,2); //tri stats
    vboxgen->addLayout(hboxtri8,12,1,1,1); //tri stats
QWidget *fenetre = new QWidget;
    fenetre->setLayout(vboxgen);
    setCentralWidget(fenetre);




//   gestion des connections  ///////

connect(quitter, SIGNAL(triggered()), this, SLOT(fermerapp()));
connect(ouvrir, SIGNAL(triggered()), this, SLOT(ouvrirfichier()));
connect(enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerfichier()));
connect(about, SIGNAL(triggered()), this, SLOT(afficherlicence()));
connect(options, SIGNAL(triggered()), this, SLOT(gestionparam()));
connect(menuinfbt1,SIGNAL(clicked()), this, SLOT(infbt1clicked()));
connect(menuinfbt2,SIGNAL(clicked()), this, SLOT(infbt2clicked()));
connect(menuinfbt3,SIGNAL(clicked()), this, SLOT(infbt3clicked()));
connect(menuinfbt4,SIGNAL(clicked()), this, SLOT(infbt4clicked()));
connect(menuinfbt5,SIGNAL(clicked()), this, SLOT(infbt5clicked()));
connect(menuinfbt6,SIGNAL(clicked()), this, SLOT(infbt6clicked()));
connect(onglets,SIGNAL(currentChanged(int)), this, SLOT(majonglets(int)));
connect(listeatelier,SIGNAL(currentTextChanged(QString)), this,SLOT(majmodelmach2()));
connect(listemachine,SIGNAL(currentTextChanged(QString)), this,SLOT(majmodelmach3()));
connect(bp_doc,SIGNAL(clicked()), this, SLOT(ouvrirdocmachine()));
connect(ptri,SIGNAL(stateChanged(int)), this, SLOT(tripiecesactivated()));
connect(ptrinom,SIGNAL(textChanged(const QString &)), this, SLOT(tripieceschanged()));
connect(ptrireference,SIGNAL(textChanged(const QString &)), this, SLOT(tripieceschanged()));
connect(ptricommentaire,SIGNAL(textChanged(const QString &)), this, SLOT(tripieceschanged()));
connect(ptriemplacement,SIGNAL(textChanged(const QString &)), this, SLOT(tripieceschanged()));
connect(ptriadresse,SIGNAL(textChanged(const QString &)), this, SLOT(tripieceschanged()));
connect(ptridatea,SIGNAL(textChanged(const QString &)), this, SLOT(tripieceschanged()));
connect(ptridateb,SIGNAL(textChanged(const QString &)), this, SLOT(tripieceschanged()));
connect(ptrifournisseur,SIGNAL(currentTextChanged(QString)), this,SLOT(tripieceschanged()));
connect(ptrifabricant,SIGNAL(currentTextChanged(QString)), this,SLOT(tripieceschanged()));
connect(ptricategorie,SIGNAL(currentTextChanged(QString)), this,SLOT(tripieceschanged()));
connect(btri,SIGNAL(stateChanged(int)), this, SLOT(tribtchanged()));
connect(btricommentaire,SIGNAL(textChanged(const QString &)), this, SLOT(tribtchanged()));
connect(btrilu,SIGNAL(currentTextChanged(QString)), this, SLOT(tribtchanged()));
connect(btridatea,SIGNAL(textChanged(const QString &)), this, SLOT(tribtchanged()));
connect(btridateb,SIGNAL(textChanged(const QString &)), this, SLOT(tribtchanged()));
connect(btrimachine,SIGNAL(currentTextChanged(QString)), this,SLOT(tribtchanged()));
connect(btriatelier,SIGNAL(currentTextChanged(QString)), this,SLOT(btriatelierchanged()));
connect(btritech,SIGNAL(currentTextChanged(QString)), this,SLOT(tribtchanged()));
connect(btritype,SIGNAL(currentTextChanged(QString)), this,SLOT(tribtchanged()));
connect(ctri,SIGNAL(stateChanged(int)), this, SLOT(tricommandeschanged()));
connect(ctricommentaire,SIGNAL(textChanged(const QString &)), this, SLOT(tricommandeschanged()));
connect(ctrifournisseur,SIGNAL(currentTextChanged(QString)), this, SLOT(tricommandeschanged()));
connect(ctridatea,SIGNAL(textChanged(const QString &)), this, SLOT(tricommandeschanged()));
connect(ctridateb,SIGNAL(textChanged(const QString &)), this, SLOT(tricommandeschanged()));
connect(ctridestinataire,SIGNAL(currentTextChanged(QString)), this,SLOT(tricommandeschanged()));
connect(ctrireference,SIGNAL(textChanged(const QString &)), this,SLOT(tricommandeschanged()));
connect(strimoisdebut,SIGNAL(currentTextChanged(QString)), this,SLOT(tri_stat_changed()));
connect(strimoisfin,SIGNAL(currentTextChanged(QString)), this,SLOT(tri_stat_changed()));
connect(strianneedebut,SIGNAL(currentTextChanged(QString)), this,SLOT(tri_stat_changed()));
connect(strianneefin,SIGNAL(currentTextChanged(QString)), this,SLOT(tri_stat_changed()));
connect(stridivers,SIGNAL(currentTextChanged(QString)), this,SLOT(tri_stat_changed()));
connect(p7_fournisseur,SIGNAL(currentTextChanged(QString)), this,SLOT(fournisseur_selected_changed()));
connect(p7_name_commercial,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_num_bureau,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_num_client,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_num_contrat,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_num_portable,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_adresse_postale,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_mail1,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_mail2,SIGNAL(textEdited(const QString &)), this, SLOT(modif_fournisseurs()));
connect(p7_commentaires,SIGNAL(textChanged()), this, SLOT(modif_fournisseurs()));

/////////////////////////////////////////

std::ifstream flux("parametres.ini");
     if(flux)
     {
      std::string t="";
      std::getline(flux,t);

      time_t now = time(0);
      tm *ltm = localtime(&now);
      std::string temp="";
      std::stringstream convert;
      convert.clear();
      if ((ltm->tm_mday)<10)
      {
          convert << "0";
      }
      convert << (ltm->tm_mday);
      if ((1 + ltm->tm_mon)<10)
      {
          convert << "0";
      }
      convert << (1 + ltm->tm_mon);
      convert <<  (1900 + ltm->tm_year);
      temp = convert.str();

      b.setdate_bt_param(temp);
      b.setdate_commande_param(temp);

        if(t != "")
        {
         b.setpath(t);
         t ="";
         std::getline(flux,t);

         b.setname(t);
         t ="";
         std::cout << b.path() << "et : " << b.name() << std::endl;
         b.majbase();
         if(b.iscorrompue() !=2)
         {
         QMessageBox::critical(this, "erreur", "impossible d'ouvrir la base");
         }
         else {


     t = "la base contient : ";
     t +=  std::to_string(b.nbpieces());
     t += " pieces \n";
     t +=  std::to_string(b.nbbts());
     t += " bt's \n";
     t +=  std::to_string(b.nbmachines());
     t += " machines \n";
     t +=  std::to_string(b.nbcommandes());
     t += " commandes \n";

     if (QMessageBox::information (this, "ouverture reussi",t.c_str()) == QMessageBox::Ok)
     {
        // t1 = new UnThread(this);
         this->majtables();
         this->majmodelpieces();
         this->maj_fournisseurs();
     }
         }
        }
     }

}

MainWindow::~MainWindow()  // destructeur
{

}

// gestion des slots //////////////////////////////


void MainWindow::majonglets(int vue)
{
    switch(vue)
    {
        case 0:
        ptri->setChecked(false);
        this->tripiecesvisible(true);
        this->tribtvisible(false);
        this->tricommandevisible(false);
        this->tristatsvisible(false);
        menuinfbt1->setText("exporter -> csv");
        menuinfbt2->setText("ajouter");
        menuinfbt3->setText("modifier");
        menuinfbt4->setText("supprimer");
        menuinfbt5->setText("ajouter a machine");
        menuinfbt6->setText("imprimer -> pdf");
        this->majmodelpieces();
        break;
        case 1:
        this->tripiecesvisible(false);
        this->tribtvisible(false);
        this->tricommandevisible(false);
        this->tristatsvisible(false);
        menuinfbt1->setText("suppr piece");
        menuinfbt2->setText("ajouter");
        menuinfbt3->setText("gerer");
        menuinfbt4->setText("supprimer");
        menuinfbt5->setText("exporter");
        menuinfbt6->setText("...");
        this->majmodelmach1();
        break;
        case 2:   // bt's
        this->tribtvisible(true);
        btri->setChecked(false);
        this->tripiecesvisible(false);
        this->tricommandevisible(false);
        this->tristatsvisible(false);
        menuinfbt1->setText("rechercher");
        menuinfbt2->setText("ajouter");
        menuinfbt3->setText("modifier");
        menuinfbt4->setText("supprimer");
        menuinfbt5->setText("exporter");
        menuinfbt6->setText("gerer");
        this->majmodelbt();
        break;
        case 3:  // commandes
        this->tripiecesvisible(false);
        this->tribtvisible(false);
        this->tricommandevisible(true);
        this->tristatsvisible(false);
        ctri->setChecked(false);
        menuinfbt1->setText("rechercher");
        menuinfbt2->setText("ajouter");
        menuinfbt3->setText("modifier");
        menuinfbt4->setText("supprimer");
        menuinfbt5->setText("exporter");
        menuinfbt6->setText("gerer");
        this->majmodelcommandes();
        break;
        case 4:  // tables
        this->tripiecesvisible(false);
        this->tribtvisible(false);
        this->tricommandevisible(false);
        this->tristatsvisible(false);
        menuinfbt1->setText("ajouter element");
        menuinfbt2->setText("supprimer element");
        menuinfbt3->setText("...");
        menuinfbt4->setText("...");
        menuinfbt5->setText("...");
        menuinfbt6->setText("...");
        break;
        case 5:  // statistiques
        this->tripiecesvisible(false);
        this->tribtvisible(false);
        this->tricommandevisible(false);
        this->tristatsvisible(true);
        type_stat=0;
        menuinfbt1->setText("commande du mois");  //  type_stat =0
        menuinfbt2->setText("suivi atelier"); //  type_stat =1
        menuinfbt3->setText("suivi bt's");   //  type_stat =2
        menuinfbt4->setText("commandes annee");  //  type_stat =3
        menuinfbt5->setText("suivi annuel"); //  type_stat =4
        menuinfbt6->setText("imprimer en pdf");
        this->stat_commandes_mois_maj();
        break;
        case 6:  // statistiques
        this->tripiecesvisible(false);
        this->tribtvisible(false);
        this->tricommandevisible(false);
        this->tristatsvisible(false);
        menuinfbt1->setText("...");
        menuinfbt2->setText("...");
        menuinfbt3->setText("...");
        menuinfbt4->setText("...");
        menuinfbt5->setText("...");
        menuinfbt6->setText("...");
        break;
        default:

        menuinfbt1->setText("rechercher");
        menuinfbt2->setText("ajouter");
        menuinfbt3->setText("modifier");
        menuinfbt4->setText("suffprimer");
        menuinfbt5->setText("exporter");
        menuinfbt6->setText("imprimer");
    }
}

void MainWindow::afficherlicence()
{

    QMessageBox::information(this, "Licence LGPL", "Bienvenue dans GGMAO \n Logiciel Libre \n basé sur la librairie Qt \n n'hesitez pas a partager \n Jerome Humbert \n @ : j.humbert@fcelevage.fr");

}

void MainWindow::ouvrirfichier()
{
    std::string t = "";
    QString fichier = QFileDialog::getExistingDirectory(this, "Choisissez le dossier de travail");


    if(fichier.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'ouvrir la base");
     }
    else
    {
        QDir dir(fichier);
        b.setname(dir.dirName().toStdString());
        t = dir.path().toStdString();
        t += "/";
        b.setpath(t);
        t ="";

        time_t now = time(0);
        tm *ltm = localtime(&now);
        std::string temp="";
        std::stringstream convert;
        convert.clear();
        if ((ltm->tm_mday)<10)
        {
            convert << "0";
        }
        convert << (ltm->tm_mday);
        if ((1 + ltm->tm_mon)<10)
        {
            convert << "0";
        }
        convert << (1 + ltm->tm_mon);
        convert <<  (1900 + ltm->tm_year);
        temp = convert.str();

        b.setdate_bt_param(temp);
        b.majbase();
        if(b.iscorrompue() !=2)
        {
        QMessageBox::critical(this, "erreur", "impossible d'ouvrir la base");
        }
     }
    t = "la base contient : ";
    t +=  std::to_string(b.nbpieces());
    t += " pieces \n";
    t +=  std::to_string(b.nbbts());
    t += " bt's \n";
    t +=  std::to_string(b.nbmachines());
    t += " machines \n";
    t +=  std::to_string(b.nbcommandes());
    t += " commandes \n";

    if (QMessageBox::information (this, "ouverture reussi",t.c_str()) == QMessageBox::Ok)
    {
        this->majmodelpieces();
        this->majtables();
        this->maj_fournisseurs();

    }


}



void MainWindow::ouvrirdocmachine()
{
    if(listedoc->currentText().toStdString() !="")
    {
        std::string temp ="";
        temp = b.path();
        temp += "/ressources/";
        temp += listedoc->currentText().toStdString();
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(temp.c_str())))
           {
               QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le hiechier...."));
           }
    }
}



void MainWindow::enregistrerfichier()
{
    b.savebase();
    b.saveressources();
    if(b.iscorrompue() !=2)
    {
    QMessageBox::critical(this, "erreur", "impossible d'enregistrer la base");
    }
}

void MainWindow::btriatelierchanged()
{
    std::vector<std::string> tab;
    btrimachine->clear();
    btrimachine->addItem(QString::fromStdString(""));
    b.getlistmachineatelier(tab,btriatelier->currentText().toStdString());
    for(uint i=0 ; i < tab.size(); i++ )
    {
        btrimachine->addItem(QString::fromStdString(tab[i].data()));
    }
    this->tribtchanged();
}

 void MainWindow::addpieces()
 {
     addpiecesbase fenetre(b);
     if(fenetre.exec())
     {

         QString nom = fenetre.nom->text();
         QString reference= fenetre.reference->text();
         QString fabricant = fenetre.fabricant->currentText();
         QString fournisseur = fenetre.fournisseur->currentText();
         QString prix = fenetre.prix->text();
         QString commentaire = fenetre.commentaire->text();
        b.addpieces(prix.toStdString(),fabricant.toStdString(),fournisseur.toStdString(),nom.toStdString(),reference.toStdString(),commentaire.toStdString());
        this->majmodelpieces();
     }
 }

 void MainWindow::addbt()
 {
     addbtbase fenetre(b);
     if(fenetre.exec())
     {
           std::string comm ="";
         QString atelier = fenetre.atelier->currentText();
         QString machine = fenetre.machine->currentText();
         QString tech = fenetre.tech->currentText();
         QString type = fenetre.type->currentText();
         QString temps = fenetre.temps->text();
         QString date = fenetre.date->text();
         QString lien_photo_1 = fenetre.m_lienphoto1->text();
         QString lien_photo_2 = fenetre.m_lienphoto2->text();
         QString lien_photo_3 = fenetre.m_lienphoto3->text();
         QString lien_photo_4 = fenetre.m_lienphoto4->text();
         QString commentaire = fenetre.commentaire->toPlainText();
         comm = commentaire.toStdString();
         comm.erase(std::remove(comm.begin(), comm.end(), '\n'), comm.end());
         QString temp ="";
         temp = b.path().c_str();
         temp += "album/";
         temp += machine;
         temp += "/";

         if(lien_photo_1 != "")
         {
             lien_photo_1 = temp + lien_photo_1;
             QFile fichier(lien_photo_1);
             lien_photo_1 = temp;
             lien_photo_1 += std::to_string(b.index_bts()).c_str();
             lien_photo_1 += "-1.jpg";
             if(fichier.rename(lien_photo_1))
             {
                 lien_photo_1 = std::to_string(b.index_bts()).c_str();
                 lien_photo_1 += "-1.jpg";
             }
         }

         if(lien_photo_2 != "")
         {
             lien_photo_2 = temp + lien_photo_2;
             QFile fichier2(lien_photo_2);
             lien_photo_2 = temp;
             lien_photo_2 += std::to_string(b.index_bts()).c_str();
             lien_photo_2 += "-2.jpg";
             if(fichier2.rename(lien_photo_2))
             {
                 lien_photo_2 = std::to_string(b.index_bts()).c_str();
                 lien_photo_2 += "-2.jpg";
             }
         }

         if(lien_photo_3 != "")
         {
             lien_photo_3 = temp + lien_photo_3;
             QFile fichier3(lien_photo_3);
             lien_photo_3 = temp;
             lien_photo_3 += std::to_string(b.index_bts()).c_str();
             lien_photo_3 += "-3.jpg";
             if(fichier3.rename(lien_photo_3))
             {
                 lien_photo_3 = std::to_string(b.index_bts()).c_str();
                 lien_photo_3 += "-3.jpg";
             }
         }

         if(lien_photo_4 != "")
         {
             lien_photo_4 = temp + lien_photo_4;
             QFile fichier4(lien_photo_4);
             lien_photo_4 = temp;
             lien_photo_4 += std::to_string(b.index_bts()).c_str();
             lien_photo_4 += "-4.jpg";
             if(fichier4.rename(lien_photo_4))
             {
                 lien_photo_4 = std::to_string(b.index_bts()).c_str();
                 lien_photo_4 += "-4.jpg";
             }
         }
         b.setdate_bt_param(date.toStdString());
        b.addbt(atelier.toStdString(),machine.toStdString(),type.toStdString(),tech.toStdString(),date.toStdString(),temps.toStdString(),comm,lien_photo_1.toStdString(),lien_photo_2.toStdString(),lien_photo_3.toStdString(),lien_photo_4.toStdString());
        this->majmodelbt();
     }
 }

 void MainWindow::addcommande()
 {
     addcommandebase fenetre(b);
     if(fenetre.exec())
     {
         QString reference = fenetre.reference->text();
         QString destinataire = fenetre.destinataire->currentText();
         QString fournisseur = fenetre.fournisseur->currentText();
         QString prix = fenetre.prix->text();
         QString date = fenetre.date->text();
         QString commentaire = fenetre.commentaire->text();
         b.setdate_commande_param(date.toStdString());
         b.addcommande(fournisseur.toStdString(),reference.toStdString(),prix.toStdString(),destinataire.toStdString(),date.toStdString(),commentaire.toStdString());
        this->majmodelcommandes();
     }
 }

 void MainWindow::addmachine()
 {
     addmachinebase fenetre(b);
     if(fenetre.exec())
     {

         QString nom = fenetre.nom->text();
         QString reference= fenetre.reference->text();
         QString fabricant = fenetre.fabricant->currentText();
         QString atelier = fenetre.atelier->currentText();
         QString date = fenetre.date->text();
         QString commentaire = fenetre.commentaire->text();
       b.addmachine(atelier.toStdString(),"","",fabricant.toStdString(),nom.toStdString(),reference.toStdString(),commentaire.toStdString(),date.toStdString());
     this->majmodelmach1();
       this->majmodelmach2();

     }
 }

 void MainWindow::addelementtable()
 {
     addtablebase fenetre(b);
     if(fenetre.exec())
     {
         QString name = fenetre.f->text();

         if(fenetre.choix_table->currentText() == "atelier" )
         {
             b.addatelier(name.toStdString());
         }
         if(fenetre.choix_table->currentText() == "fournisseur" )
         {
             b.addfournisseur(name.toStdString());
         }
         if(fenetre.choix_table->currentText() == "fabricant" )
         {
             b.addfabricant(name.toStdString());
         }
         if(fenetre.choix_table->currentText() == "type de travail" )
         {
             b.addtypetaf(name.toStdString());
         }
         if(fenetre.choix_table->currentText() == "destinataire" )
         {
             b.adddestinataire(name.toStdString());
         }
         if(fenetre.choix_table->currentText() == "technicien" )
         {
             b.addtech(name.toStdString());
         }
         if(fenetre.choix_table->currentText() == "categorie" )
         {
             b.addcategorie(name.toStdString());
         }

         this->majtables();
         this->majonglets(4);

     }
 }


void MainWindow::fermerapp()
{
    if(b.ismodified())
    {
        int reponse = QMessageBox::question(this, "enregistrer", "voulez-vous sauvegarder ?", QMessageBox ::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes)
          {
            b.savebase();
            if(b.iscorrompue() !=2)
            {
            QMessageBox::critical(this, "erreur", "impossible d'enregistrer la base");
            }
            else
            {
            this->close();
            }
          }
    }
    else
    {
        this->close();
    }


}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(b.ismodified())
    {
        int reponse = QMessageBox::question(this, "enregistrer", "voulez-vous sauvegarder ?", QMessageBox ::Yes | QMessageBox::No);
        if(reponse == QMessageBox::Yes)
          {
            b.savebase();
            b.saveressources();
            if(b.iscorrompue() !=2)
            {
            QMessageBox::critical(this, "erreur", "impossible d'enregistrer la base");
            }
            else
            {
            this->close();
            }
          }
    }
    else
    {
        this->close();
    }


}


void MainWindow::infbt1clicked()
{
    if(onglets->currentIndex() == 0)
    {
        this->inventairetocsv();
    }
    else if(onglets->currentIndex() == 1)
    {
        this->suppr_piece_machine();
    }
    else if(onglets->currentIndex() == 2)
    {

    }
    else if(onglets->currentIndex() == 3)
    {

    }
    else if(onglets->currentIndex() == 4)
    {
        this->addelementtable();
    }
    else if(onglets->currentIndex() == 5)
    {
        this->stat_commandes_mois();
    }
    else
    {

    }
}

void MainWindow::infbt2clicked()
{
    if(onglets->currentIndex() == 0)
    {
            this->addpieces();
    }
    else if(onglets->currentIndex() == 1)
    {
      this->addmachine();
    }
    else if(onglets->currentIndex() == 2)
    {
        this->addbt();
    }
    else if(onglets->currentIndex() == 3)
    {
        this->addcommande();
    }
    else if(onglets->currentIndex() == 4)
    {
        this->suppr_element_table();
    }
    else if(onglets->currentIndex() == 5)
    {
        this->stat_suivi_ateliers();
    }
    else
    {

    }
}

void MainWindow::infbt3clicked()
{
    if(onglets->currentIndex() == 0)
    {
            this->modifier_piece();
    }
    else if(onglets->currentIndex() == 1)
    {
            this->modifier_machine();
    }
    else if(onglets->currentIndex() == 2)
    {
        this->modifier_bt();
    }
    else if(onglets->currentIndex() == 3)
    {
        this->modifier_commande();
    }
    else if(onglets->currentIndex() == 4)
    {
    }
    else if(onglets->currentIndex() == 5)
    {
       this->stat_suivi_tech();
    }
    else
    {

    }
}

void MainWindow::infbt4clicked()
{
    if(onglets->currentIndex() == 0)
    {

    }
    else if(onglets->currentIndex() == 1)
    {

    }
    else if(onglets->currentIndex() == 2)
    {

    }
    else if(onglets->currentIndex() == 3)
    {

    }
    else if(onglets->currentIndex() == 4)
    {
    }
    else if(onglets->currentIndex() == 5)
    {
        this->stat_commandes_annee();
    }
    else
    {

    }
}

void MainWindow::infbt5clicked()
{
    if(onglets->currentIndex() == 0)
    {
        this->ajouterselectionmachine();
    }
    else if(onglets->currentIndex() == 1)
    {

    }
    else if(onglets->currentIndex() == 2)
    {

    }
    else if(onglets->currentIndex() == 3)
    {

    }
    else if(onglets->currentIndex() == 4)
    {
    }
    else if(onglets->currentIndex() == 5)
    {
        this->stat_suivi_annuel();
    }
    else
    {

    }
}

void MainWindow::infbt6clicked()
{
    if(onglets->currentIndex() == 0)
    {
        this->inventairetopdf();
    }
    else if(onglets->currentIndex() == 1)
    {

    }
    else if(onglets->currentIndex() == 2)
    {

    }
    else if(onglets->currentIndex() == 3)
    {

    }
    else if(onglets->currentIndex() == 4)
    {
    }
    else if(onglets->currentIndex() == 5)
    {
        if(type_stat == 0) this->commandesmoistopdf();
        else if(type_stat == 1) this->suiviatelierstopdf();
        else if(type_stat == 2) this->suivitechtopdf();
        else if(type_stat == 3) this->commandesanneetopdf();
        else if(type_stat == 4) this->suivianneetopdf();

    }
    else
    {

    }
}

void MainWindow::modifier_piece()
{

    if(vue->selectionModel()->currentIndex().isValid())
    {
    const QModelIndex index = vue->selectionModel()->currentIndex();

    setpiecesbase fenetre(b,modelepieces->item(index.row(),16)->text().toInt());
    if(fenetre.exec())
     {
        QString nom = fenetre.nom->text();
        QString reference= fenetre.reference->text();
        QString fabricant = fenetre.fabricant->currentText();
        QString four1 = fenetre.m_fournisseur1->currentText();
        QString four2 = fenetre.m_fournisseur2->currentText();
        QString four3 = fenetre.m_fournisseur3->currentText();
        QString categorie = fenetre.m_categorie->currentText();
        QString date = fenetre.d->text();
        QString plan = fenetre.m_lienplan->text();
        QString doc = fenetre.m_liendoc->text();
        QString photo = fenetre.m_lienphoto->text();
        QString prix = fenetre.prix->text();
        QString qty = fenetre.m_qty->text();
        QString emplacement = fenetre.m_emplacement->text();
        QString adresse = fenetre.m_adresse->text();
        QString key = fenetre.Lkey->text();
        QString commentaire = fenetre.commentaire->text();



       b.modifierpiece(std::atoi(key.toStdString().data()),modelepieces->item(index.row(),16)->text().toInt(),prix.toStdString(),fabricant.toStdString(),nom.toStdString(),reference.toStdString(),commentaire.toStdString(),four1.toStdString(),four2.toStdString(),four3.toStdString(),doc.toStdString(),plan.toStdString(),photo.toStdString(),emplacement.toStdString(),adresse.toStdString(),categorie.toStdString(),date.toStdString(),qty.toStdString());
       this->majmodelpieces();
     }
    }
}

void MainWindow::suppr_piece_machine()
{
    if(v2pieces->selectionModel()->currentIndex().isValid())
    {
    const QModelIndex index = v2pieces->selectionModel()->currentIndex();
    b.suppr_piece_machine(b.findmachine(listemachine->currentText().toStdString()), modelemachinespieces->item(index.row(),16)->text().toInt());
   this->majmodelmach3();

    }
}



void MainWindow::modifier_bt()
{

    if(vue3->selectionModel()->currentIndex().isValid())
    {
    const QModelIndex index = vue3->selectionModel()->currentIndex();

    setbtbase fenetre(b,modelebt->item(index.row(),8)->text().toInt());
    if(fenetre.exec())
     {
        fenetre.bont.settech(fenetre.tech->currentText().toStdString());
        fenetre.bont.settime(fenetre.temps->text().toStdString());
        fenetre.bont.setatelier(fenetre.atelier->currentText().toStdString());
        fenetre.bont.setmachine(fenetre.machine->currentText().toStdString());
        fenetre.bont.settype(fenetre.type->currentText().toStdString());
        fenetre.bont.setcommentaire(fenetre.commentaire->toPlainText().toStdString());
        fenetre.bont.setdate(fenetre.date->text().toStdString());
        b.set_bt(fenetre.bont,fenetre.num);
       this->majmodelbt();
     }
    }
}

void MainWindow::modifier_commande()
{

    if(vue4->selectionModel()->currentIndex().isValid())
    {
    const QModelIndex index = vue4->selectionModel()->currentIndex();

    setcommande fenetre(b,modelecommandes->item(index.row(),6)->text().toInt());
    if(fenetre.exec())
     {
        fenetre.comm.setfournisseur(fenetre.fournisseur->currentText().toStdString());
        fenetre.comm.setprix(fenetre.prix->text().toStdString());
        fenetre.comm.setdestinataire(fenetre.destinataire->currentText().toStdString());
        fenetre.comm.setreference(fenetre.reference->text().toStdString());
        fenetre.comm.setcommentaire(fenetre.commentaire->text().toStdString());
        fenetre.comm.setdate(fenetre.date->text().toStdString());
        b.set_commmande(fenetre.comm,fenetre.num);
       this->majmodelcommandes();
     }
    }
}


void MainWindow::suppr_element_table()
{

    if(vue5->selectionModel()->currentIndex().isValid()  )
    {
    const QModelIndex index = vue5->selectionModel()->currentIndex();
      if(!modeletables->item(index.row(),index.column())->text().isNull())
      {
        if(index.column() ==0 && index.row() > -1 ) b.supprtech(modeletables->item(index.row(),index.column())->text().toStdString());
        else if(index.column() ==1 && index.row() > -1 ) b.suppratelier(modeletables->item(index.row(),index.column())->text().toStdString());
        else if(index.column() ==2 && index.row() > -1 ) b.supprtypetaf(modeletables->item(index.row(),index.column())->text().toStdString());
        else if(index.column() ==3 && index.row() > -1 ) b.supprfournisseur(modeletables->item(index.row(),index.column())->text().toStdString());
        else if(index.column() ==4 && index.row() > -1 ) b.supprfabricant(modeletables->item(index.row(),index.column())->text().toStdString());
        else if(index.column() ==5 && index.row() > -1 ) b.supprdestinataire(modeletables->item(index.row(),index.column())->text().toStdString());
        else if(index.column() ==6 && index.row() > -1 ) b.supprcategorie(modeletables->item(index.row(),index.column())->text().toStdString());
        this->majtables();
      this->majonglets(4);
      }
    }
}




void MainWindow::modifier_machine()
{

    if(b.findmachine(listemachine->currentText().toStdString()) > -1)
    {

    setmachine fenetre(b,b.findmachine(listemachine->currentText().toStdString()));
    if(fenetre.exec())
     {
        fenetre.mach.setfabricant(fenetre.fabricant->currentText().toStdString());
        fenetre.mach.setatelier(fenetre.atelier->currentText().toStdString());
        fenetre.mach.setliendoc1(fenetre.m_liendoc1->text().toStdString());
        fenetre.mach.setliendoc2(fenetre.m_liendoc2->text().toStdString());
        fenetre.mach.setliendoc3(fenetre.m_liendoc3->text().toStdString());
        fenetre.mach.setliendoc4(fenetre.m_liendoc4->text().toStdString());
        fenetre.mach.setlienplan1(fenetre.m_lienplan1->text().toStdString());
        fenetre.mach.setlienplan2(fenetre.m_lienplan2->text().toStdString());
        fenetre.mach.setlienplan3(fenetre.m_lienplan3->text().toStdString());
        fenetre.mach.setlienplan4(fenetre.m_lienplan4->text().toStdString());
        fenetre.mach.setlienphoto1(fenetre.m_lienphoto1->text().toStdString());
        fenetre.mach.setlienphoto2(fenetre.m_lienphoto2->text().toStdString());
        fenetre.mach.setlienphoto3(fenetre.m_lienphoto3->text().toStdString());
        fenetre.mach.setlienphoto4(fenetre.m_lienphoto4->text().toStdString());
        fenetre.mach.setcommentaire(fenetre.commentaire->text().toStdString());
        fenetre.mach.setdate(fenetre.d->text().toStdString());
        fenetre.mach.setreference(fenetre.reference->text().toStdString());
        b.set_machine(fenetre.mach,fenetre.num);
       this->majmodelmach3();
     }
    }
}



void MainWindow::ajouterselectionmachine()
{
    if(tablopiecesint.size() ==0)
    {

    }
    else if(tablopiecesint.size() > 25)
    {

    }
    else
    {

        addpiecesmachine fenetre(b);
        if(fenetre.exec())
        {

            int num_mach=0;
            num_mach = b.findmachine(fenetre.machine->currentText().toStdString());
            if(num_mach > -1)
            {
               b.machine_addpieces(tablopiecesint,num_mach);
            }
        }
    }

}


void MainWindow::gestionparam()
{

    parametres fenetre(b);
    if(fenetre.exec())
     {

     }

}


void MainWindow::fournisseur_selected_changed()
{
    fournisseurs four;
    b.getfournisseur(four,p7_fournisseur->currentText().toStdString());
    p7_num_portable->setText(four.num_portable().c_str());
    p7_num_bureau->setText(four.num_bureau().c_str());
    p7_name_commercial->setText(four.name_commercial().c_str());
    p7_num_client->setText(four.num_client().c_str());
    p7_num_contrat->setText(four.num_contrat().c_str());
    p7_adresse_postale->setText(four.adresse_postale().c_str());
    p7_mail1->setText(four.mail_1().c_str());
    p7_mail2->setText(four.mail_2().c_str());
    p7_commentaires->setText(four.commentaire().c_str());
    std::cout << "test" <<std::endl;
}




void MainWindow::modif_fournisseurs()
{
    fournisseurs four;
    four.setname(p7_fournisseur->currentText().toStdString());
    four.setname_commercial(p7_name_commercial->text().toStdString());
    four.setnum_bureau(p7_num_bureau->text().toStdString());
    four.setnum_client(p7_num_client->text().toStdString());
    four.setnum_contrat(p7_num_contrat->text().toStdString());
    four.setnum_portable(p7_num_portable->text().toStdString());
    four.setadresse_postale(p7_adresse_postale->text().toStdString());
    four.setmail_1(p7_mail1->text().toStdString());
    four.setmail_2(p7_mail2->text().toStdString());
    four.setcommentaire(p7_commentaires->toPlainText().toStdString());
   std::cout << four.commentaire() << std::endl;
    b.setfournisseur(four);
    std::cout << "truc" << std::endl;



}







