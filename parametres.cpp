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
     QLineEdit *prenom = new QLineEdit;
    prenom->setText(b->path().c_str());
     QLineEdit *age = new QLineEdit;
     QCheckBox *ouvertureauto = new QCheckBox;
     QCheckBox *memodatenewbt = new QCheckBox;
     QCheckBox *saveauto = new QCheckBox;
     QCheckBox *fullscreen = new QCheckBox;
   //  QCheckBox *ouvertureauto = new QCheckBox;
    // QCheckBox *ouvertureauto = new QCheckBox;

      path = new QLineEdit;
      name = new QLineEdit;
      std::ifstream flux("parametres.ini");
      if(flux)
      {
          std::string t="";
          std::getline(flux,t);

            if(t != "")
            {
             path->setText( t.c_str());
             t ="";
             std::getline(flux,t);
             name->setText(t.c_str());
            }
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
    std::ofstream flux("parametres.ini", std::ios::out|std::ios::trunc);
    if(flux)
    {
        flux << path->text().toStdString() << std::endl;
        flux << name->text().toStdString() << std::endl;

    }
else {

}
    flux.close();
    this->close();
}

void parametres::affecterpath()
{
    path->setText(b->path().c_str());
    name->setText(b->name().c_str());

}
