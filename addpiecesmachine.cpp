#include "addpiecesmachine.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iostream>
#include "base.h"

addpiecesmachine::addpiecesmachine(base &b1,QWidget *parent) : QDialog(parent)
{

     machine = new QComboBox;

     atelier = new QComboBox;
    b = &b1;
         ///////////////////////


         std::vector<std::string> tab;
         b->getlistatelier(tab);
         std::sort(tab.begin(),tab.end());
         atelier->clear();
         atelier->addItem(QString::fromStdString(""));
         for(uint i=0 ; i < tab.size(); i++ )
         {
             atelier->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
         }


        QGridLayout *grille = new QGridLayout;

        grille->addWidget(atelier,0,0,4,4);
        grille->addWidget(machine,4,0,4,4);

        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");
        okButton->setVisible(false);

        this->setFixedWidth(QApplication::desktop()->availableGeometry().width()/5);
        this->setFixedHeight(QApplication::desktop()->availableGeometry().height()/7);
        grille->addWidget(okButton,8,0);
        grille->addWidget(cancelButton,8,2);
        this->setLayout(grille);
        this->show();

        connect(atelier,SIGNAL(currentTextChanged(QString)), this,SLOT(majcomboboxmachine()));
        connect(machine,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));
        connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
        connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void addpiecesmachine::formulaireok()
{
    okButton->setVisible(false);

    if(atelier->currentText()!= ""  && machine->currentText()!= "")
    {
        okButton->setVisible(true);

    }
}


void addpiecesmachine::majcomboboxmachine()
{
    std::vector<std::string> tab;
    tab.clear();
    b->getlistmachineatelier(tab,atelier->currentText().toStdString());
    std::sort(tab.begin(),tab.end());
    machine->clear();
    machine->addItem(QString::fromStdString(""));

    for(uint i=0 ; i < tab.size(); i++ )
    {
        machine->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
    }
    this->formulaireok();
}

