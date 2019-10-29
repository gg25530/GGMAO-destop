#include "parametres.h"
#include <QApplication>
#include <QtWidgets>
#include <QHostInfo>
#include "base.h"
#include <fstream>


parametres::parametres(base &b1,QWidget *parent) : QDialog(parent)
{
    b = &b1;
    QLineEdit *nom = new QLineEdit;
    nom->setText(QHostInfo::localHostName());

     ouvertureauto = new QCheckBox;
     memodatenewbt = new QCheckBox;
     memodatenewcommande = new QCheckBox;
     saveauto = new QCheckBox;
     fullscreen = new QCheckBox;


      path = new QLineEdit;
      name = new QLineEdit;

      largeur = new QLineEdit;
      hauteur = new QLineEdit;
      nbsaves = new QLineEdit;
      largeur->setText("800");
      hauteur->setText("600");
      nbsaves->setText("25");
      bool openreussi = true;
      std::ifstream flux("parametres.ini");
      if(flux)
      {
          std::string t="";
          std::getline(flux,t);
            if(t == " // emplacement de l'application")
            {
             std::getline(flux,t);
             path->setText( t.c_str());
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // nom de l'ordinateur")
            {
             std::getline(flux,t);
             name->setText( t.c_str());
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // ouverture auto")
            {
             std::getline(flux,t);
                if(t == "oui") ouvertureauto->setChecked(true);
                else if(t == "non") ouvertureauto->setChecked(false);
                else openreussi=false;
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // memorisation date BT")
            {
             std::getline(flux,t);
             if(t == "oui") memodatenewbt->setChecked(true);
             else if(t == "non") memodatenewbt->setChecked(false);
             else openreussi=false;
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // memorisation date commande")
            {
             std::getline(flux,t);
             if(t == "oui") memodatenewcommande->setChecked(true);
             else if(t == "non") memodatenewcommande->setChecked(false);
             else openreussi=false;
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // plein ecran")
            {
             std::getline(flux,t);
             if(t == "oui") fullscreen->setChecked(true);
             else if(t == "non") fullscreen->setChecked(false);
             else openreussi=false;
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // largeur")
            {
             std::getline(flux,t);
             largeur->setText( t.c_str());
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // hauteur")
            {
             std::getline(flux,t);
             hauteur->setText( t.c_str());
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // nombre de sauvegarde")
            {
             std::getline(flux,t);
             nbsaves->setText( t.c_str());
             t ="";
            }
            else
            {
                openreussi = false;
            }
            std::getline(flux,t);
            if(t == " // sauvegarde auto")
            {
             std::getline(flux,t);
             if(t == "oui") saveauto->setChecked(true);
             else if(t == "non") saveauto->setChecked(false);
             else openreussi=false;
             t ="";
            }
            else
            {
                openreussi = false;
            }

       if(!openreussi) QMessageBox::critical(this, "Erreur","parametres.ini corrompu\n effacez le dans le\n dossier de l'application\n puis redemarrez l'application");

      }
      else
      {
        QMessageBox::information (this, "Information","parametres non initialisés \n sauvegardez après changement \n pour l'initialiser");
      }
     okButton = new QPushButton("OK");
     okButton->setVisible(false);
     QPushButton *sauvegarde = new QPushButton("sauvegarder");
     definepathButton = new QPushButton("definir emplacement base");
     QVBoxLayout *layoutgen = new QVBoxLayout;
     QFormLayout *layout = new QFormLayout;

     layout->addRow("nom du PC", nom);
     layout->addRow("ouverture automatique", ouvertureauto);
     layout->addRow("memorisation date nouveau BT", memodatenewbt);
     layout->addRow("sauvegarde auto", saveauto);
     layout->addRow("plein ecran", fullscreen);
    // layout->addRow("avec ouverture automatique", ouvertureauto);
  //   layout->addRow("avec ouverture automatique", ouvertureauto);

     layout->addRow("emplacement de la base", path);
     layoutgen->addLayout(layout);
     layoutgen->addWidget(definepathButton);
     layoutgen->addWidget(sauvegarde);
     this->setLayout(layoutgen);
     this->show();


     connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
     connect(sauvegarde,SIGNAL(clicked()), this,SLOT(sauvegardes()));
     connect(definepathButton,SIGNAL(clicked()), this,SLOT(affecterpath()));



}

void parametres::sauvegardes()
{
    if(name->text().toStdString() != "" && path->text().toStdString() != "")
    {
    std::ofstream flux("parametres.ini", std::ios::out|std::ios::trunc);
    if(flux)
    {

        flux << " // emplacement de l'application" << std::endl;
        flux << path->text().toStdString() << std::endl;
        flux << " // nom de l'ordinateur" << std::endl;
        flux << name->text().toStdString() << std::endl;
        flux << " // ouverture auto" << std::endl;
        if(ouvertureauto->isChecked()) flux << "oui" << std::endl;
        else flux << "non" << std::endl;
        flux << " // memorisation date BT" << std::endl;
        if(memodatenewbt->isChecked()) flux << "oui" << std::endl;
        else flux << "non" << std::endl;
        flux << " // memorisation date commande" << std::endl;
        if(memodatenewcommande->isChecked()) flux << "oui" << std::endl;
        else flux << "non" << std::endl;
        flux << " // plein ecran" << std::endl;
        if(fullscreen->isChecked()) flux << "oui" << std::endl;
        else flux << "non" << std::endl;
        flux << " // largeur" << std::endl;
        flux << largeur->text().toStdString() << std::endl;
        flux << " // hauteur" << std::endl;
        flux << hauteur->text().toStdString() << std::endl;
        flux << " // nombre de sauvegarde" << std::endl;
        flux << nbsaves->text().toStdString() << std::endl;
        flux << " // sauvegarde auto" << std::endl;
        if(saveauto->isChecked()) flux << "oui" << std::endl;
        else flux << "non" << std::endl;    }
else {

}
    flux.close();

    this->close();
    }
}

void parametres::affecterpath()
{
    path->setText(b->path().c_str());
    name->setText(b->name().c_str());

}
