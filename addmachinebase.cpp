#include "addmachinebase.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "base.h"

addmachinebase::addmachinebase(base &b1,QWidget *parent) : QDialog(parent)
{


    date = new QLineEdit;
    commentaire = new QLineEdit;
    reference = new QLineEdit;
    fabricant = new QComboBox;
    atelier = new QComboBox;
    nom = new QLineEdit;
    warning = new QLabel;
   b = &b1;
        ///////////////////////


        date->setMaxLength(10);
        date->setInputMask("00-00-0000");
        date->setText("01-01-2018");


        std::vector<std::string> tab;
        b->getlistatelier(tab);
        std::sort(tab.begin(),tab.end());
        atelier->clear();
        atelier->addItem(QString::fromStdString(""));
        for(uint i=0 ; i < tab.size(); i++ )
        {
            atelier->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
        }

        tab.clear();
        b->getlistfabricants(tab);
        std::sort(tab.begin(),tab.end());
        fabricant->clear();
        fabricant->addItem(QString::fromStdString(""));
        for(uint i=0 ; i < tab.size(); i++ )
        {
            fabricant->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
        }

        warning->setText("cette machine existe deja !!!");
        warning->setVisible(false);
        warning->setStyleSheet("font-weight: bold; color: red");

       QGridLayout *grille = new QGridLayout;

       grille->addWidget(new QLabel("nom :"),0,0);
       grille->addWidget(new QLabel("fabricant :"),0,1);
       grille->addWidget(nom,1,0);
       grille->addWidget(fabricant,1,1);
       grille->addWidget(warning,2,0,1,2);
       grille->addWidget(new QLabel("lieu d'utilisation' :"),3,0);
       grille->addWidget(new QLabel("n° de serie :"),3,1);
       grille->addWidget(atelier,4,0);
       grille->addWidget(reference,4,1);
       grille->addWidget(new QLabel("informations :"),5,0);
       grille->addWidget(commentaire,6,0,4,2);
       grille->addWidget(new QLabel("date d'achat :"),11,0);
       grille->addWidget(date,11,1);

       okButton = new QPushButton("OK");
       cancelButton = new QPushButton("Cancel");
       okButton->setVisible(false);
       grille->addWidget(okButton,11,0);
       grille->addWidget(cancelButton,11,1);
       this->setLayout(grille);
       this->show();

       connect(nom,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
       connect(atelier,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));
       connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
       connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void addmachinebase::formulaireok()
{
   okButton->setVisible(false);

   if(atelier->currentText()!= ""  && nom->text()!= "" )
   {
       okButton->setVisible(true);

   }
       warning->setVisible(this->machineexist(nom->text().toStdString()));


}

bool addmachinebase::machineexist(std::string f)
{
    std::vector<std::string> tab;
    b->getlistmachine(tab);
       for(uint i=0 ; i < tab.size(); i++ )
    {
       if(tab[i] == f)
       {
           return true;
       }
    }
    return false;
}
