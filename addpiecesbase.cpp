#include "addpiecesbase.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "base.h"

addpiecesbase::addpiecesbase(base &b1,QWidget *parent) : QDialog(parent)
{
         b = &b1;
         nom = new QLineEdit;
         reference = new QLineEdit;
         fabricant = new QComboBox;
         fournisseur = new QComboBox;
         prix = new QLineEdit;
         commentaire = new QLineEdit;
         ///////////////////////
         nom->setMaxLength(100);
         reference->setMaxLength(20);
         prix->setMaxLength(4);
         commentaire->setMaxLength(100);
         prix->setValidator(new QIntValidator(0,9999,prix));
        erreur = new QLabel("une piece similaire existe !!!");

         std::vector<std::string> tab;
         b->getlistfournisseurs(tab);
         std::sort(tab.begin(),tab.end());
         fournisseur->clear();
         fournisseur->addItem(QString::fromStdString(""));
         for(uint i=0 ; i < tab.size(); i++ )
         {
             fournisseur->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
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

        QVBoxLayout *layoutgeneral = new QVBoxLayout;

        QFormLayout *layout = new QFormLayout;

        layout->addRow("nom", nom);
        layout->addRow("reference", reference);
        layout->addRow("fabricant", fabricant);
        layout->addRow("fournisseur", fournisseur);
        layout->addRow("prix", prix);
        layout->addRow("commentaire", commentaire);

        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");
        okButton->setVisible(false);
        erreur->setVisible(false);
        layoutgeneral->addLayout(layout);
        layoutgeneral->addWidget(okButton);
        layoutgeneral->addWidget(cancelButton);
        layoutgeneral->addWidget(erreur);

        this->setLayout(layoutgeneral);
        this->show();

        connect(nom,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(reference,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(fabricant,SIGNAL(currentTextChanged( QString )), this,SLOT(formulaireok()));
        connect(fournisseur,SIGNAL(currentTextChanged( QString )), this,SLOT(formulaireok()));
        connect(prix,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));

        connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
        connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void addpiecesbase::formulaireok()
{
    okButton->setVisible(false);
    erreur->setVisible(false);
    if(nom->text()!= ""  && reference->text()!= "" && fabricant->currentText()!= "" && fournisseur->currentText()!= "" && prix->text()!= "")
    {
        okButton->setVisible(true);

    }
    for(int i=0; i < b->nbpieces(); i++)
    {
        if(b->pieces_nom(i).c_str() == nom->text() && nom->text() != "")
        {
            erreur->setVisible(true);
            okButton->setVisible(false);
        }
        if(b->pieces_reference(i).c_str() == reference->text() && reference->text() != "")
        {
            erreur->setVisible(true);
            okButton->setVisible(false);
        }

    }


}
