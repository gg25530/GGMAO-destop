#include "setcommande.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "base.h"

setcommande::setcommande(base &b1,int numero, QWidget *parent) : QDialog(parent)
{
     reference = new QLineEdit;
     destinataire = new QComboBox;
     fournisseur = new QComboBox;
     prix = new QLineEdit;
     date = new QLineEdit;
     commentaire = new QLineEdit;
     b= &b1;
         ///////////////////////
         date->setMaxLength(10);
         reference->setMaxLength(20);
         prix->setMaxLength(4);
         commentaire->setMaxLength(150);
         prix->setValidator(new QIntValidator(0,9999,prix));
         date->setInputMask("00-00-0000");

         num = b->findcommande(numero);
        if(num >-1)
           b->get_commande(comm,num);
        else {
            this->close();
        }

         std::vector<std::string> tab;
         b->getlistfournisseurs(tab);
         std::sort(tab.begin(),tab.end());
         fournisseur->clear();
         for(uint i=0 ; i < tab.size(); i++ )
         {
             fournisseur->addItem(QString::fromStdString(tab[i].data()));
         }
           tab.clear();
         b->getlistdestinataires(tab);
         destinataire->clear();
         std::sort(tab.begin(),tab.end());
         for(uint i=0 ; i < tab.size(); i++ )
         {
             destinataire->addItem(QString::fromStdString(tab[i].data()));
         }


         date->setText(comm.date().text().c_str());
         reference->setText(comm.reference().c_str());
         destinataire->setCurrentText(comm.destinataire().c_str());
         fournisseur->setCurrentText(comm.fournisseur().c_str());
         commentaire->setText(comm.commentaire().c_str());
         prix->setText(comm.prix().c_str());

        QGridLayout *grille = new QGridLayout;
        grille->addWidget(new QLabel("fournisseur :"),0,0);
        grille->addWidget(fournisseur,0,1);
        grille->addWidget(new QLabel("reference :"),1,0);
        grille->addWidget(reference,1,1);
        grille->addWidget(new QLabel("destinataire :"),2,0);
        grille->addWidget(destinataire,2,1);
        grille->addWidget(new QLabel("prix HT :"),3,0);
        grille->addWidget(prix,3,1);
        grille->addWidget(new QLabel("date de commande :"),4,0);
        grille->addWidget(date,4,1);
        grille->addWidget(new QLabel("explications :"),5,0);
        grille->addWidget(commentaire,5,1);
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");
        okButton->setVisible(false);
        grille->addWidget(okButton,6,0);
        grille->addWidget(cancelButton,6,1);
        this->setLayout(grille);
        this->setBaseSize(QApplication::desktop()->availableGeometry().width()/4, QApplication::desktop()->availableGeometry().height()/4);
        this->formulaireok();
        this->show();

        connect(fournisseur,SIGNAL(currentTextChanged( QString)), this,SLOT(formulaireok()));
        connect(reference,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(destinataire,SIGNAL(currentTextChanged( QString)), this,SLOT(formulaireok()));
        connect(prix,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(commentaire,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));

        connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
        connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void setcommande::formulaireok()
{
    okButton->setVisible(false);

    if(fournisseur->currentText()!= ""  && reference->text()!= "" && destinataire->currentText()!= "" && prix->text()!= "" && commentaire->text()!="")
    {
        okButton->setVisible(true);

    }
}
