#include "addtablebase.h"
#include "base.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>

addtablebase::addtablebase(base &b1,QWidget *parent) : QDialog(parent)
{

      choix_table = new QComboBox;
      choix_table->addItem("atelier");
      choix_table->addItem("fournisseur");
      choix_table->addItem("fabricant");
      choix_table->addItem("type de travail");
      choix_table->addItem("destinataire");
      choix_table->addItem("technicien");
      choix_table->addItem("categorie");




    f = new QLineEdit;
    warning = new QLabel;
    b = &b1;
        ///////////////////////

        warning->setText("cet element existe deja !!!");
        warning->setVisible(false);
        warning->setStyleSheet("font-weight: bold; color: red");

       QGridLayout *grille = new QGridLayout;
       grille->addWidget(choix_table,0,0,1,2);
       grille->addWidget(f,1,0,1,2);
       grille->addWidget(warning,2,0,1,2);


       okButton = new QPushButton("OK");
       cancelButton = new QPushButton("Cancel");
       okButton->setVisible(false);
       grille->addWidget(okButton,3,0);
       grille->addWidget(cancelButton,3,1);
       this->setLayout(grille);
       this->show();

       connect(f,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
       connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
       connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);
       connect(choix_table,SIGNAL(currentTextChanged(QString)), this,SLOT(loadtable()));


}

void addtablebase::formulaireok()
{
   okButton->setVisible(false);
   warning->setVisible(this->elementexist(f->text().toStdString()));

   if( f->text()!= "" && !this->elementexist(f->text().toStdString()))
   {
       okButton->setVisible(true);

   }
   else
   {
       okButton->setVisible(false);

   }


}

bool addtablebase::elementexist(std::string f)
{
    std::vector<std::string> tab;
    if(choix_table->currentText() == "atelier")
    {
        b->getlistatelier(tab);
    }
    if(choix_table->currentText() == "fournisseur")
    {
        b->getlistfournisseurs(tab);
    }
    if(choix_table->currentText() == "fabricant")
    {
        b->getlistfabricants(tab);
    }
    if(choix_table->currentText() == "type de travail")
    {
        b->getlisttypetaf(tab);
    }
    if(choix_table->currentText() == "destinataire")
    {
        b->getlistdestinataires(tab);
    }
    if(choix_table->currentText() == "technicien")
    {
        b->getlisttech(tab);
    }
       for(uint i=0 ; i < tab.size(); i++ )
    {
       if(tab[i] == f)
       {
           return true;
       }
    }
    return false;
}

void addtablebase::loadtable()
{
    f->setText("");
}
