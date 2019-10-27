#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <vector>
#include "pieces.h"
#include "base.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

/*
QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QAbstractItemView;
class QItemSelectionModel;
QT_END_NAMESPACE
*/

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();


public slots:
    void afficherlicence();
    void ouvrirfichier();
    void ouvrirdocmachine();
    void enregistrerfichier();
    void addpieces();
    void addbt();
    void addcommande();
    void addmachine();
    void addelementtable();
    void fermerapp();
    void infbt1clicked();
    void infbt2clicked();
    void infbt3clicked();
    void infbt4clicked();
    void infbt5clicked();
    void infbt6clicked();
    void majonglets(int vue);
    void btriatelierchanged();
    void modifier_piece();
    void modifier_machine();
    void suppr_piece_machine();
    void modifier_bt();
    void modifier_commande();
    void suppr_element_table();
    void gestionparam();
    void ajouterselectionmachine();
    void fournisseur_selected_changed();
    void modif_fournisseurs();
    void closeEvent(QCloseEvent *event);

    ///code dans tri.cpp
    void tri_stat_changed();
    void tripieceschanged();
    void tripiecesactivated();
    void tribtchanged();
    void tricommandeschanged();
    void tripiecesvisible(bool state);
    void tribtvisible(bool state);
    void tricommandevisible(bool state);
    void tristatsvisible(bool state);

    ///code dans stats.cpp
    void stat_commandes_mois_maj();
    void stat_commandes_annee_maj();
    void stat_suivi_annee_maj();
    void stat_suivi_tech_maj();
    void stat_suivi_ateliers_maj();
    void stat_commandes_mois();
    void stat_commandes_annee();
    void stat_suivi_annuel();
    void stat_suivi_tech();
    void stat_suivi_ateliers();


    /// code dans maj-model.cpp
    void majmodelpieces();
    void majmodelmach1();
    void majmodelmach2();
    void majmodelmach3();
    void majmodelbt();
    void majmodelcommandes();
    void majtables();
    void maj_fournisseurs();

    /// code dans exportpdf.cpp
    void topdf();
    void commandesmoistopdf();
    void commandesanneetopdf();
    void suivitechtopdf();
    void suiviatelierstopdf();
    void suivianneetopdf();
    void inventairetopdf();
    void inventairetocsv();



private:

//// general    ////
base b;
QTabWidget *onglets;

//// page1      ////
QStandardItemModel *modelepieces;
QTableView *vue;
QLineEdit *ptrireference;
QLineEdit *ptrinom;
QLineEdit *ptricommentaire;
QComboBox *ptrifournisseur;
QComboBox *ptrifabricant;
QComboBox *ptricategorie;
QLineEdit *ptriemplacement;
QLineEdit *ptriadresse;
QLineEdit *ptridatea;
QLineEdit *ptridateb;
QLabel *pttrireference;
QLabel *pttrinom;
QLabel *pttricommentaire;
QLabel *pttrifournisseur;
QLabel *pttrifabricant;
QLabel *pttricategorie;
QLabel *pttriemplacement;
QLabel *pttriadresse;
QLabel *pttridate;
QCheckBox *ptri;
std::vector <int> tablopiecesint;
//// page2      ////
QTabWidget *ongletsp2;
QStandardItemModel *modelemachinesbt;
QStandardItemModel *modelemachinespieces;
QTableView *v2pieces;
QComboBox *listeatelier;
QComboBox *listemachine;
QComboBox *listedoc;
QLabel *reference;
QLabel *date;
QLabel *commentaire;
QLabel *fabricant;


//// page3      ////
QStandardItemModel *modelebt;
QTableView *vue3;
QComboBox *btrilu;
QLineEdit *btricommentaire;
QLineEdit *btridatea;
QLineEdit *btridateb;
QComboBox *btritech;
QComboBox *btriatelier;
QComboBox *btritype;
QComboBox *btrimachine;
QLabel *bttricommentaire;
QLabel *bttrilu;
QLabel *bttridate;
QLabel *bttritech;
QLabel *bttriatelier;
QLabel *bttritype;
QLabel *bttrimachine;
QCheckBox *btri;

//// page4      ////
QStandardItemModel *modelecommandes;
QTableView *vue4;
QLineEdit *ctrireference;
QLineEdit *ctricommentaire;
QComboBox *ctrifournisseur;
QComboBox *ctridestinataire;
QLineEdit *ctridatea;
QLineEdit *ctridateb;
QLabel *cttrireference;
QLabel *cttricommentaire;
QLabel *cttrifournisseur;
QLabel *cttridestinataire;
QLabel *cttridate;
QCheckBox *ctri;
//// page5      ////
QStandardItemModel *modeletables;
QTableView *vue5;

//// page6      ////
int type_stat=0;
std::vector <std::string> liste_elements_stats;
std::vector <int> nb_commandes_four_stats;
QStandardItemModel *modelestats;
QTableView *vue6;
QPieSeries *series;
QBarSeries *series2;
QStackedBarSeries *series3;
std::vector <QBarSet *> bar_stacked;
QBarSet *bar_cout_annee;
QBarSet *bar_nb_bt_annee;
QBarSet *bar_temps_bt_annee;
QChart *chart;
QChart *chart2;
QChart *chart3;
QValueAxis *axisY;
QValueAxis *axisY2;
QStringList categories;
QBarCategoryAxis *axisX ;
QBarCategoryAxis *axisX2 ;
QChartView *chartView;
std::vector <std::string> namesstats;
std::vector <int> valeursstats;
QComboBox *strimoisdebut;
QComboBox *strimoisfin;
QComboBox *strianneedebut;
QComboBox *strianneefin;
QComboBox *stridivers;
QLabel *stri_de;
QLabel *stri_jusqua;


//// page7      ////
QLineEdit *p7_num_portable;
QLineEdit *p7_num_bureau;
QComboBox *p7_fournisseur;
QLineEdit *p7_name_commercial;
QLineEdit *p7_adresse_postale;
QLineEdit *p7_mail1;
QLineEdit *p7_mail2;
QLineEdit *p7_num_contrat;
QLineEdit *p7_num_client;
QTextEdit *p7_commentaires;


////  menu inferieur  ///
QPushButton *menuinfbt1; //////  grisé //////  rechercher   //// rechercher   /////  ajouter tech  ///
QPushButton *menuinfbt2 ;    //////  ajouter ////  ajouter      ////  ajouter    //////  ajouter atelier //
QPushButton *menuinfbt3;  //////  modifier ///  modifier   /////   modifier   ///////  ajouter type de bt //
QPushButton *menuinfbt4;  /////  supprimer ///  supprimer /////   supprimer   //////  ajouter fournisseur //
QPushButton *menuinfbt5;  //////  exporter  ///  exporter  /////   exporter     /////  ajouter fabricant  //
QPushButton *menuinfbt6;  ///////  grisé  /////  gerer   ///////   gerer      ///////  grisé ///
//// tri pieces
QHBoxLayout *hboxtri1;
QHBoxLayout *hboxtri2;
//// tri bt's
QHBoxLayout *hboxtri3;
QHBoxLayout *hboxtri4;
//// tri commandes
QHBoxLayout *hboxtri5;
QHBoxLayout *hboxtri6;
//// tri stats
QHBoxLayout *hboxtri7;
QHBoxLayout *hboxtri8;
};

#endif // MAINWINDOW_H
