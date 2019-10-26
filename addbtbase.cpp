#include "addbtbase.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iostream>
#include "base.h"

addbtbase::addbtbase(base &b1,QWidget *parent) : QDialog(parent)
{
     date = new QLineEdit;
     commentaire = new QTextEdit;
     temps = new QLineEdit;
     machine = new QComboBox;
     tech = new QComboBox;
     type = new QComboBox;
     atelier = new QComboBox;
     m_lienphoto1 = new QLineEdit;
     m_lienphoto2 = new QLineEdit;
     m_lienphoto3 = new QLineEdit;
     m_lienphoto4 = new QLineEdit;

    b = &b1;
         ///////////////////////

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
             atelier->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
         }
         tab.clear();
         b->getlisttech(tab);
         std::sort(tab.begin(),tab.end());
         tech->clear();
         tech->addItem(QString::fromStdString(""));
         for(uint i=0 ; i < tab.size(); i++ )
         {
             tech->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
         }
         tab.clear();
         b->getlisttypetaf(tab);
         std::sort(tab.begin(),tab.end());
         type->clear();
         type->addItem(QString::fromStdString(""));
         for(uint i=0 ; i < tab.size(); i++ )
         {
             type->addItem(QString::fromStdString(tab[i].data()), QVariant(i));
         }

         QPushButton *importButtonphoto1 = new QPushButton("ajouter");
         QPushButton *importButtonphoto2 = new QPushButton("ajouter");
         QPushButton *importButtonphoto3 = new QPushButton("ajouter");
         QPushButton *importButtonphoto4 = new QPushButton("ajouter");


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
        grille->addWidget(m_lienphoto1,7,0);
        grille->addWidget(importButtonphoto1,7,1);
        grille->addWidget(m_lienphoto2,8,0);
        grille->addWidget(importButtonphoto2,8,1);
        grille->addWidget(m_lienphoto3,9,0);
        grille->addWidget(importButtonphoto3,9,1);
        grille->addWidget(m_lienphoto4,10,0);
        grille->addWidget(importButtonphoto4,10,1);
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");
        okButton->setVisible(false);
        grille->addWidget(okButton,11,0);
        grille->addWidget(cancelButton,11,1);
        this->setLayout(grille);
        this->show();

        connect(atelier,SIGNAL(currentTextChanged(QString)), this,SLOT(majcomboboxmachine()));
        connect(date,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(tech,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));
        connect(type,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));
        connect(commentaire,SIGNAL(textChanged()), this,SLOT(formulaireok()));
        connect(machine,SIGNAL(currentTextChanged(QString)), this,SLOT(formulaireok()));
        connect(importButtonphoto1,SIGNAL(clicked()), this,SLOT(importer_photo1()));
        connect(importButtonphoto2,SIGNAL(clicked()), this,SLOT(importer_photo2()));
        connect(importButtonphoto3,SIGNAL(clicked()), this,SLOT(importer_photo3()));
        connect(importButtonphoto4,SIGNAL(clicked()), this,SLOT(importer_photo4()));
        connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
        connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void addbtbase::formulaireok()
{
    okButton->setVisible(false);

    if(atelier->currentText()!= ""  && tech->currentText()!= "" && type->currentText()!= "" && commentaire->toPlainText()!= ""&& machine->currentText()!= "")
    {
        if(this->dateok())
        okButton->setVisible(true);

    }
}

bool addbtbase::dateok()
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

void addbtbase::majcomboboxmachine()
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

void addbtbase::importer_photo1()
{
    std::string poubelle="";
    QString path_in = QFileDialog::getOpenFileName(this, "fichier jpg a importer", QDir::homePath(), "jpg (*.jpg)");
    bool ok = false;
    if(path_in.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
    }
    else
    {
        QFileInfo source(path_in);
        QString temp = b->path().c_str();
        temp += "album/";

        QDir dir(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }
        temp += machine->currentText();
        dir.setPath(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }

        QString destination = "";
        if(source.path() != temp)
        {
        destination = source.fileName();
        }
            if(destination !="")
            {
                temp += "/";
                temp += destination;
                if(QFileInfo(temp).exists())
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car il existe deja");

                else if(temp.toStdString().find(".jpg") == std::string::npos && temp.toStdString().find(".JPG") == std::string::npos)
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car l'extension n'est pas bonne");

                else if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n pour une raison inconnue");
                else {
                    m_lienphoto1->setText(destination);
                     }
            }



    }
}


void addbtbase::importer_photo2()
{
    std::string poubelle="";
    QString path_in = QFileDialog::getOpenFileName(this, "fichier jpg a importer", QDir::homePath(), "jpg (*.jpg)");
    bool ok = false;
    if(path_in.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
    }
    else
    {
        QFileInfo source(path_in);
        QString temp = b->path().c_str();
        temp += "album/";

        QDir dir(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }
        temp += machine->currentText();
        dir.setPath(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }

        QString destination = "";
        if(source.path() != temp)
        {
        destination = source.fileName();
        }
            if(destination !="")
            {
                temp += "/";
                temp += destination;
                if(QFileInfo(temp).exists())
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car il existe deja");

                else if(temp.toStdString().find(".jpg") == std::string::npos && temp.toStdString().find(".JPG") == std::string::npos)
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car l'extension n'est pas bonne");

                else if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n pour une raison inconnue");
                else {
                    m_lienphoto2->setText(destination);
                     }
            }



    }
}

void addbtbase::importer_photo3()
{
    std::string poubelle="";
    QString path_in = QFileDialog::getOpenFileName(this, "fichier jpg a importer", QDir::homePath(), "jpg (*.jpg)");
    bool ok = false;
    if(path_in.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
    }
    else
    {
        QFileInfo source(path_in);
        QString temp = b->path().c_str();
        temp += "album/";

        QDir dir(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }
        temp += machine->currentText();
        dir.setPath(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }

        QString destination = "";
        if(source.path() != temp)
        {
        destination = source.fileName();
        }
            if(destination !="")
            {
                temp += "/";
                temp += destination;
                if(QFileInfo(temp).exists())
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car il existe deja");

                else if(temp.toStdString().find(".jpg") == std::string::npos && temp.toStdString().find(".JPG") == std::string::npos)
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car l'extension n'est pas bonne");

                else if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n pour une raison inconnue");
                else {
                    m_lienphoto3->setText(destination);
                     }
            }



    }
}

void addbtbase::importer_photo4()
{
    std::string poubelle="";
    QString path_in = QFileDialog::getOpenFileName(this, "fichier jpg a importer", QDir::homePath(), "jpg (*.jpg)");
    bool ok = false;
    if(path_in.isEmpty())
    {
        QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
    }
    else
    {
        QFileInfo source(path_in);
        QString temp = b->path().c_str();
        temp += "album/";

        QDir dir(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }
        temp += machine->currentText();
        dir.setPath(temp);
        if (!dir.exists())
        {
            dir.mkpath(".");
        }

        QString destination = "";
        if(source.path() != temp)
        {
        destination = source.fileName();
        }
            if(destination !="")
            {
                temp += "/";
                temp += destination;
                if(QFileInfo(temp).exists())
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car il existe deja");

                else if(temp.toStdString().find(".jpg") == std::string::npos && temp.toStdString().find(".JPG") == std::string::npos)
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n car l'extension n'est pas bonne");

                else if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier \n pour une raison inconnue");
                else {
                    m_lienphoto4->setText(destination);
                     }
            }



    }
}

