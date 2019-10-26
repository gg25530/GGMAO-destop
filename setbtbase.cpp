#include "setbtbase.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iostream>
#include "base.h"

setbtbase::setbtbase(base &b1,int numero,QWidget *parent) : QDialog(parent)
{
     date = new QLineEdit;
     commentaire = new QTextEdit;
     temps = new QLineEdit;
     machine = new QComboBox;
     tech = new QComboBox;
     type = new QComboBox;
     atelier = new QComboBox;
    b = &b1;
         ///////////////////////
      num = b->findbt(numero);
     if(num >-1)
        b->get_bt(bont,num);
     else {
         this->close();
     }
         temps->setMaxLength(10);
         date->setMaxLength(10);
         date->setInputMask("00-00-0000");
         temps->setInputMask("00.0");

         date->setText(b->getdate_bt_param().c_str());


         std::vector<std::string> tab;
         b->getlistatelier(tab);
         std::sort(tab.begin(),tab.end());
         atelier->clear();
         atelier->addItem(QString::fromStdString(""));
         for(uint i=0 ; i < tab.size(); i++ )
         {
             atelier->addItem(QString::fromStdString(tab[i].data()));
         }
         tab.clear();
         b->getlisttech(tab);
         std::sort(tab.begin(),tab.end());
         tech->clear();
         tech->addItem(QString::fromStdString(""));
         for(uint i=0 ; i < tab.size(); i++ )
         {
             tech->addItem(QString::fromStdString(tab[i].data()));
         }
         tab.clear();
         b->getlisttypetaf(tab);
         std::sort(tab.begin(),tab.end());
         type->clear();
         type->addItem(QString::fromStdString(""));
         for(uint i=0 ; i < tab.size(); i++ )
         {
             type->addItem(QString::fromStdString(tab[i].data()));
         }

         atelier->setCurrentText(bont.atelier().c_str());
         tab.clear();
         b->getlistmachineatelier(tab,atelier->currentText().toStdString());
         std::sort(tab.begin(),tab.end());
         machine->clear();
         for(uint i=0 ; i < tab.size(); i++ )
         {
             machine->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
         }
         date->setText(bont.date().text().c_str());
         commentaire->setText(bont.commentaire().c_str());
         temps->setText(bont.time().c_str());
         machine->setCurrentText(bont.machine().c_str());
         tech->setCurrentText(bont.tech().c_str());
         type->setCurrentText(bont.type().c_str());

        QGridLayout *grille = new QGridLayout;
        grille->addWidget(atelier,0,0);
        grille->addWidget(machine,0,1);
        grille->addWidget(tech,1,0);
        grille->addWidget(type,1,1);
        grille->addWidget(new QLabel("tâche effectuée :"),2,0);
        grille->addWidget(commentaire,3,0,2,2);
        grille->addWidget(new QLabel("durée de la tache :"),5,0);
        grille->addWidget(temps,5,1);
        grille->addWidget(new QLabel("date d'execution :"),6,0);
        grille->addWidget(date,6,1);

        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");
        okButton->setVisible(false);
        grille->addWidget(okButton,7,0);
        grille->addWidget(cancelButton,7,1);
        this->setLayout(grille);
        this->formulaireok();
        this->show();

        connect(atelier,SIGNAL(currentTextChanged(QString)), this,SLOT(majcomboboxmachine()));
        connect(date,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(tech,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));
        connect(type,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));
        connect(commentaire,SIGNAL(textChanged()), this,SLOT(formulaireok()));
        connect(machine,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));

        connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
        connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void setbtbase::formulaireok()
{
    okButton->setVisible(false);

    if(atelier->currentText()!= ""  && tech->currentText()!= "" && type->currentText()!= "" && commentaire->toPlainText()!= ""&& machine->currentText()!= "")
    {
        if(this->dateok())
        {
            okButton->setVisible(true);
        }

    }
}

bool setbtbase::dateok()
{
    int ya=0,ma=0,ja=0;
    std::vector<std::string> elements;
    std::stringstream ss;
    std::string temp="";
    ss.clear();
    elements.clear();
    ss << date->text().toStdString();
 while (getline(ss, temp,'-'))
 {
 elements.push_back(temp);
 }
 if(elements.size() != 3 )
 {
     return false;
 }
 else if(elements[0] == "" || elements[1] == "" || elements[2] == "")
 {
     return false;
 }
 else
 {
     ya = std::atoi(elements[2].data());
     ma = std::atoi(elements[1].data());
     ja = std::atoi(elements[0].data());
     if(ya > 1980 && ya < 2049 && ma > -1 && ma < 13 && ja > -1 && ja < 32)
     {
         return true;
     }
     else
     {
         return false;
     }
 }
}

void setbtbase::majcomboboxmachine()
{
    std::vector<std::string> tab;
    tab.clear();
    b->getlistmachineatelier(tab,atelier->currentText().toStdString());
    std::sort(tab.begin(),tab.end());
    machine->clear();
    for(uint i=0 ; i < tab.size(); i++ )
    {
        machine->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
    }
    this->formulaireok();
}

