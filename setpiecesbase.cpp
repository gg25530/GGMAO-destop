#include "setpiecesbase.h"
#include "listutilisationpieces.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "date.h"
#include "base.h"

setpiecesbase::setpiecesbase(base &b1,int numero,QWidget *parent) : QDialog(parent)
{
         nom = new QLineEdit;
         reference = new QLineEdit;
         fabricant = new QComboBox;
         prix = new QLineEdit;
         commentaire = new QLineEdit;
          m_qty = new QLineEdit;
          d = new QLineEdit;
          m_emplacement = new QLineEdit;
          m_adresse = new QLineEdit;
          m_categorie = new QComboBox;
          m_liendoc = new QLineEdit;
          m_lienplan = new QLineEdit;
          m_lienphoto = new QLineEdit;
          m_fournisseur1 = new QComboBox;
          m_fournisseur2 = new QComboBox;
          m_fournisseur3 = new QComboBox;
    b = &b1;
         ///////////////////////
         nom->setMaxLength(100);
         reference->setMaxLength(20);
         prix->setMaxLength(4);
         commentaire->setMaxLength(100);
         prix->setValidator(new QIntValidator(0,9999,prix));
         m_qty->setMaxLength(4);
         m_qty->setValidator(new QIntValidator(0,9999,m_qty));
         d->setMaxLength(10);
         d->setInputMask("00-00-0000");

        ////////////////////////////
         numero = b->getpiece(numero);
         Lkey = new QLabel;
         Lkey->setText(b->pieces_key(numero).c_str());
            std::cout << numero << std::endl;
         nom->setText(b->pieces_nom(numero).c_str());
         reference->setText(b->pieces_reference(numero).c_str());
         prix->setText(b->pieces_prix(numero).c_str());
         commentaire->setText(b->pieces_commentaire(numero).c_str());
          m_qty->setText(b->pieces_qty(numero).c_str());
          d->setText(b->pieces_date(numero).c_str());
          m_emplacement->setText(b->pieces_emplacement(numero).c_str());
          m_adresse->setText(b->pieces_adresse(numero).c_str());
          m_liendoc->setText(b->pieces_liendoc(numero).c_str());
          m_lienplan->setText(b->pieces_lienplan(numero).c_str());
          m_lienphoto->setText(b->pieces_lienphoto(numero).c_str());

          std::vector<std::string> tab;
          tab.clear();
          b->getlistfournisseurs(tab);
          std::sort(tab.begin(),tab.end());
          m_fournisseur1->clear();
          m_fournisseur1->addItem(QString::fromStdString(""));
          for(uint i=0 ; i < tab.size(); i++ )
          {

              m_fournisseur1->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
          }

          tab.clear();
          b->getlistfournisseurs(tab);
          std::sort(tab.begin(),tab.end());
          m_fournisseur2->clear();
          m_fournisseur2->addItem(QString::fromStdString(""));
          for(uint i=0 ; i < tab.size(); i++ )
          {
              m_fournisseur2->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
          }

          tab.clear();
          b->getlistfournisseurs(tab);
          std::sort(tab.begin(),tab.end());
          m_fournisseur3->clear();
          m_fournisseur3->addItem(QString::fromStdString(""));
          for(uint i=0 ; i < tab.size(); i++ )
          {
              m_fournisseur3->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
          }

          tab.clear();
          b->getlistfabricants(tab);
          std::sort(tab.begin(),tab.end());
          fabricant->clear();
          for(uint i=0 ; i < tab.size(); i++ )
          {
              fabricant->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
          }

          tab.clear();
          b->getlistcategories(tab);
          std::sort(tab.begin(),tab.end());
          m_categorie->clear();
          for(uint i=0 ; i < tab.size(); i++ )
          {
              m_categorie->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
          }

          fabricant->setCurrentText(b->pieces_fabricant(numero).c_str());
          m_categorie->setCurrentText(b->pieces_categorie(numero).c_str());
          m_fournisseur1->setCurrentText(b->pieces_four1(numero).c_str());
          m_fournisseur2->setCurrentText(b->pieces_four2(numero).c_str());
          m_fournisseur3->setCurrentText(b->pieces_four3(numero).c_str());

        QPushButton *importButtondoc = new QPushButton("ajouter");
        QPushButton *importButtonplan = new QPushButton("ajouter");
        QPushButton *importButtonphoto = new QPushButton("ajouter");

        QGridLayout *layout = new QGridLayout;
        layout->addWidget(new QLabel("nom :"),0,0,1,1);
        layout->addWidget(nom,0,1,1,2);
        layout->addWidget(nom,0,1,1,2);
        layout->addWidget(new QLabel("reference :"),0,3,1,1);
        layout->addWidget(reference,0,4,1,2);
        layout->addWidget(new QLabel("fabricant :"),1,0,1,1);
        layout->addWidget(fabricant,1,1,1,2);
        layout->addWidget(new QLabel("prix :"),1,3,1,1);
        layout->addWidget(prix,1,4,1,2);
        layout->addWidget(new QLabel("commentaire :"),2,0,1,1);
        layout->addWidget(commentaire,2,1,1,3);
        layout->addWidget(new QLabel("quantité :"),2,4,1,1);
        layout->addWidget(m_qty,2,5,1,2);
        layout->addWidget(new QLabel("dernier controle :"),3,0,1,2);
        layout->addWidget(d,3,2,1,2);
        layout->addWidget(new QLabel("emplacement :"),3,4,1,1);
        layout->addWidget(m_emplacement,3,5,1,2);
        layout->addWidget(new QLabel("adresse :"),4,0,1,1);
        layout->addWidget(m_adresse,4,1,1,1);
        layout->addWidget(new QLabel("categorie :"),4,2,1,1);
        layout->addWidget(m_categorie,4,3,1,2);
        layout->addWidget(new QLabel("fournisseur :"),5,0,1,1);
        layout->addWidget(m_fournisseur1,5,1,1,2);
        layout->addWidget(m_fournisseur2,5,3,1,2);
        layout->addWidget(m_fournisseur3,5,5,1,2);
        layout->addWidget(new QLabel("doc :"),6,0,1,1);
        layout->addWidget(m_liendoc,6,1,1,4);
        layout->addWidget(importButtondoc,6,5,1,2);
        layout->addWidget(new QLabel("plan :"),7,0,1,1);
        layout->addWidget(m_lienplan,7,1,1,4);
        layout->addWidget(importButtonplan,7,5,1,2);
        layout->addWidget(new QLabel("photo :"),8,0,1,1);
        layout->addWidget(m_lienphoto,8,1,1,4);
        layout->addWidget(importButtonphoto,8,5,1,2);


        okButton = new QPushButton("OK");
        useButton = new QPushButton("utilisation ...");
        cancelButton = new QPushButton("Cancel");
        okButton->setVisible(false);
        layout->addWidget(okButton,9,0,1,3);
        layout->addWidget(useButton,4,5,1,2);
        layout->addWidget(cancelButton,9,3,1,3);
        this->setLayout(layout);
        this->formulaireok();
        this->show();

        connect(nom,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(reference,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(fabricant,SIGNAL(currentTextChanged( QString )), this,SLOT(formulaireok()));
        connect(prix,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(m_qty,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(m_categorie,SIGNAL(currentTextChanged( QString )), this,SLOT(formulaireok()));
        connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
        connect(importButtondoc,SIGNAL(clicked()), this,SLOT(importer_fichierdoc()));
        connect(importButtonplan,SIGNAL(clicked()), this,SLOT(importer_fichierplan()));
        connect(importButtonphoto,SIGNAL(clicked()), this,SLOT(importer_fichierphoto()));
        connect(useButton,SIGNAL(clicked()), this,SLOT(infosusepiece()));
        connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void setpiecesbase::formulaireok()
{
    okButton->setVisible(false);

    if(nom->text()!= ""  && reference->text()!= "" && fabricant->currentText()!= ""  && m_categorie->currentText()!= "" && prix->text()!= "" && m_qty->text()!= "")
    {
        okButton->setVisible(true);

    }
}

void setpiecesbase::importer_fichierdoc()
{
    std::string poubelle="";
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    if(path_in.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
    }
    else
    {
        QFileInfo source(path_in);
        QString temp = b->path().c_str();
        temp += "ressources";
        QString destination = "";
        if(source.path() != temp)
        {
        destination = QInputDialog::getText(this,"titre du document","Si vous le souhaitez \n vous pouvez modifier \n le nom du fichier",QLineEdit::Normal,source.fileName(),&ok);
        poubelle = destination.toStdString();
        poubelle.erase(std::remove(poubelle.begin(),poubelle.end(),' '),poubelle.end());
        destination = poubelle.c_str();
        }
        if((ok && destination !="") || source.path() == temp)
        {

            if(destination !="")
            {
                temp += "/";
                temp += destination;
                if(QFileInfo(temp).exists())
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car il existe deja");

                else if(temp.toStdString().find(".pdf") == std::string::npos)
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car l'extension n'est pas bonne");

                else if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n pour une raison inconnue");
                else {
                    m_liendoc->setText(destination);
                     }
            }
            else
            {
                m_liendoc->setText(source.fileName());
            }

        }
    }
}


void setpiecesbase::importer_fichierplan()
{
    std::string poubelle="";
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    if(path_in.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
    }
    else
    {
        QFileInfo source(path_in);
        QString temp = b->path().c_str();
        temp += "ressources";
        QString destination = "";
        if(source.path() != temp)
        {
        destination = QInputDialog::getText(this,"titre du document","Si vous le souhaitez \n vous pouvez modifier \n le nom du fichier",QLineEdit::Normal,source.fileName(),&ok);
        poubelle = destination.toStdString();
        poubelle.erase(std::remove(poubelle.begin(),poubelle.end(),' '),poubelle.end());
        destination = poubelle.c_str();
        }
        if((ok && destination !="") || source.path() == temp)
        {

            if(destination !="")
            {
                temp += "/";
                temp += destination;
                if(QFileInfo(temp).exists())
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car il existe deja");

                else if(temp.toStdString().find(".pdf") == std::string::npos)
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car l'extension n'est pas bonne");

                else if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n pour une raison inconnue");
                else {
                    m_lienplan->setText(destination);
                     }
            }
            else
            {
                m_lienplan->setText(source.fileName());
            }

        }
    }
}


void setpiecesbase::importer_fichierphoto()
{
    std::string poubelle="";
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    if(path_in.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
    }
    else
    {
        QFileInfo source(path_in);
        QString temp = b->path().c_str();
        temp += "ressources";
        QString destination = "";
        if(source.path() != temp)
        {
        destination = QInputDialog::getText(this,"titre du document","Si vous le souhaitez \n vous pouvez modifier \n le nom du fichier",QLineEdit::Normal,source.fileName(),&ok);
        poubelle = destination.toStdString();
        poubelle.erase(std::remove(poubelle.begin(),poubelle.end(),' '),poubelle.end());
        destination = poubelle.c_str();
        }
        if((ok && destination !="") || source.path() == temp)
        {

            if(destination !="")
            {
                temp += "/";
                temp += destination;
                if(QFileInfo(temp).exists())
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car il existe deja");

                else if(temp.toStdString().find(".pdf") == std::string::npos)
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car l'extension n'est pas bonne");

                else if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n pour une raison inconnue");
                else {
                    m_lienphoto->setText(destination);
                     }
            }
            else
            {
                m_lienphoto->setText(source.fileName());
            }

        }
    }
}


void setpiecesbase::fournisseurs_changed()
{


}

void setpiecesbase::infosusepiece()
{
    listutilisationpieces fenetre(*b,Lkey->text().toInt());
    if(fenetre.exec())
    {


    }
}
