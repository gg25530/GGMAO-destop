#include "setmachine.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include "date.h"
#include "base.h"
#include "machine.h"

setmachine::setmachine(base &b1,int numero,QWidget *parent) : QDialog(parent)
{
         nom = new QLineEdit;
         reference = new QLineEdit;
         fabricant = new QComboBox;
         commentaire = new QLineEdit;
          d = new QLineEdit;
          atelier = new QComboBox;
          m_liendoc1 = new QLineEdit;
          m_lienplan1 = new QLineEdit;
          m_lienphoto1 = new QLineEdit;
          m_liendoc2 = new QLineEdit;
          m_lienplan2 = new QLineEdit;
          m_lienphoto2 = new QLineEdit;
          m_liendoc3 = new QLineEdit;
          m_lienplan3 = new QLineEdit;
          m_lienphoto3 = new QLineEdit;
          m_liendoc4 = new QLineEdit;
          m_lienplan4 = new QLineEdit;
          m_lienphoto4 = new QLineEdit;

    b = &b1;
    b->get_machine(mach,numero);
    num =numero;
         ///////////////////////
         commentaire->setMaxLength(100);
         d->setMaxLength(10);
         d->setInputMask("00-00-0000");

        ////////////////////////////
        // numero = b->getpiece(numero);
         nom->setText(mach.name().c_str());
         reference->setText(mach.reference().c_str());
         commentaire->setText(mach.commentaire().c_str());
          d->setText(mach.date().text().c_str());
          m_liendoc1->setText(mach.liendoc1().c_str());
          m_lienplan1->setText(mach.lienplan1().c_str());
          m_lienphoto1->setText(mach.lienphoto1().c_str());
          m_liendoc2->setText(mach.liendoc2().c_str());
          m_lienplan2->setText(mach.lienplan2().c_str());
          m_lienphoto2->setText(mach.lienphoto2().c_str());
          m_liendoc3->setText(mach.liendoc3().c_str());
          m_lienplan3->setText(mach.lienplan3().c_str());
          m_lienphoto3->setText(mach.lienphoto3().c_str());
          m_liendoc4->setText(mach.liendoc4().c_str());
          m_lienplan4->setText(mach.lienplan4().c_str());
          m_lienphoto4->setText(mach.lienphoto4().c_str());

          std::vector<std::string> tab;

          tab.clear();
          b->getlistfabricants(tab);
          std::sort(tab.begin(),tab.end());
          fabricant->clear();
          fabricant->addItem(QString::fromStdString(""));
          for(uint i=0 ; i < tab.size(); i++ )
          {
              fabricant->addItem(QString::fromStdString(tab[i].data()));
          }

          tab.clear();
          b->getlistatelier(tab);
          std::sort(tab.begin(),tab.end());
          atelier->clear();
          for(uint i=0 ; i < tab.size(); i++ )
          {
              atelier->addItem(QString::fromStdString(tab[i].data()));
          }

          fabricant->setCurrentText(mach.fabricant().c_str());
          atelier->setCurrentText(mach.atelier().c_str());

        QPushButton *importButtondoc1 = new QPushButton("ajouter");
        QPushButton *importButtonplan1 = new QPushButton("ajouter");
        QPushButton *importButtonphoto1 = new QPushButton("ajouter");
        QPushButton *importButtondoc2 = new QPushButton("ajouter");
        QPushButton *importButtonplan2 = new QPushButton("ajouter");
        QPushButton *importButtonphoto2 = new QPushButton("ajouter");
        QPushButton *importButtondoc3 = new QPushButton("ajouter");
        QPushButton *importButtonplan3 = new QPushButton("ajouter");
        QPushButton *importButtonphoto3 = new QPushButton("ajouter");
        QPushButton *importButtondoc4 = new QPushButton("ajouter");
        QPushButton *importButtonplan4 = new QPushButton("ajouter");
        QPushButton *importButtonphoto4 = new QPushButton("ajouter");

        QGridLayout *layout = new QGridLayout;
        layout->addWidget(new QLabel("nom :"),0,0,1,1);
        layout->addWidget(nom,0,1,1,2);
        layout->addWidget(new QLabel("reference :"),0,3,1,1);
        layout->addWidget(reference,0,4,1,2);
        layout->addWidget(new QLabel("fabricant :"),1,0,1,1);
        layout->addWidget(fabricant,1,1,1,2);
        layout->addWidget(new QLabel("commentaire :"),2,0,1,1);
        layout->addWidget(commentaire,2,1,1,3);
        layout->addWidget(new QLabel("date d'achat :"),3,0,1,2);
        layout->addWidget(d,3,2,1,2);
        layout->addWidget(new QLabel("atelier :"),4,2,1,1);
        layout->addWidget(atelier,4,3,1,2);
        layout->addWidget(new QLabel("doc 1:"),6,0,1,1);
        layout->addWidget(m_liendoc1,6,1,1,4);
        layout->addWidget(importButtondoc1,6,5,1,2);
        layout->addWidget(new QLabel("plan 1:"),7,0,1,1);
        layout->addWidget(m_lienplan1,7,1,1,4);
        layout->addWidget(importButtonplan1,7,5,1,2);
        layout->addWidget(new QLabel("photo 1:"),8,0,1,1);
        layout->addWidget(m_lienphoto1,8,1,1,4);
        layout->addWidget(importButtonphoto1,8,5,1,2);
        layout->addWidget(new QLabel("doc 2:"),9,0,1,1);
        layout->addWidget(m_liendoc2,9,1,1,4);
        layout->addWidget(importButtondoc2,9,5,1,2);
        layout->addWidget(new QLabel("plan 2:"),10,0,1,1);
        layout->addWidget(m_lienplan2,10,1,1,4);
        layout->addWidget(importButtonplan2,10,5,1,2);
        layout->addWidget(new QLabel("photo 2:"),11,0,1,1);
        layout->addWidget(m_lienphoto2,11,1,1,4);
        layout->addWidget(importButtonphoto2,11,5,1,2);
        layout->addWidget(new QLabel("doc 3:"),12,0,1,1);
        layout->addWidget(m_liendoc3,12,1,1,4);
        layout->addWidget(importButtondoc3,12,5,1,2);
        layout->addWidget(new QLabel("plan 3:"),13,0,1,1);
        layout->addWidget(m_lienplan3,13,1,1,4);
        layout->addWidget(importButtonplan3,13,5,1,2);
        layout->addWidget(new QLabel("photo 3:"),14,0,1,1);
        layout->addWidget(m_lienphoto3,14,1,1,4);
        layout->addWidget(importButtonphoto3,14,5,1,2);
        layout->addWidget(new QLabel("doc 4:"),15,0,1,1);
        layout->addWidget(m_liendoc4,15,1,1,4);
        layout->addWidget(importButtondoc4,15,5,1,2);
        layout->addWidget(new QLabel("plan 4:"),16,0,1,1);
        layout->addWidget(m_lienplan4,16,1,1,4);
        layout->addWidget(importButtonplan4,16,5,1,2);
        layout->addWidget(new QLabel("photo 4:"),17,0,1,1);
        layout->addWidget(m_lienphoto4,17,1,1,4);
        layout->addWidget(importButtonphoto4,17,5,1,2);

        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Annuler");
        okButton->setVisible(false);
        layout->addWidget(okButton,18,0,1,3);
        layout->addWidget(cancelButton,18,3,1,3);
        this->setLayout(layout);
        this->formulaireok();
        this->show();

        connect(nom,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(reference,SIGNAL(textChanged(const QString &)), this,SLOT(formulaireok()));
        connect(fabricant,SIGNAL(currentTextChanged( QString )), this,SLOT(formulaireok()));
        connect(atelier,SIGNAL(currentTextChanged( QString )), this,SLOT(formulaireok()));
        connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);
        connect(importButtondoc1,SIGNAL(clicked()), this,SLOT(importer_fichierdoc1()));
        connect(importButtonplan1,SIGNAL(clicked()), this,SLOT(importer_fichierplan1()));
        connect(importButtonphoto1,SIGNAL(clicked()), this,SLOT(importer_fichierphoto1()));
        connect(importButtondoc2,SIGNAL(clicked()), this,SLOT(importer_fichierdoc2()));
        connect(importButtonplan2,SIGNAL(clicked()), this,SLOT(importer_fichierplan2()));
        connect(importButtonphoto2,SIGNAL(clicked()), this,SLOT(importer_fichierphoto2()));
        connect(importButtondoc3,SIGNAL(clicked()), this,SLOT(importer_fichierdoc3()));
        connect(importButtonplan3,SIGNAL(clicked()), this,SLOT(importer_fichierplan3()));
        connect(importButtonphoto3,SIGNAL(clicked()), this,SLOT(importer_fichierphoto3()));
        connect(importButtondoc4,SIGNAL(clicked()), this,SLOT(importer_fichierdoc4()));
        connect(importButtonplan4,SIGNAL(clicked()), this,SLOT(importer_fichierplan4()));
        connect(importButtonphoto4,SIGNAL(clicked()), this,SLOT(importer_fichierphoto4()));
        connect(cancelButton,&QAbstractButton::clicked, this, &QDialog::reject);


}

void setmachine::formulaireok()
{
    okButton->setVisible(false);

    if(nom->text()!= ""  && atelier->currentText()!= "" )
    {
        okButton->setVisible(true);

    }
}

void setmachine::importer_fichierdoc1()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_liendoc1->setText(destination);
                     }
            }
            else
            {
                m_liendoc1->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierplan1()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienplan1->setText(destination);
                     }
            }
            else
            {
                m_lienplan1->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierphoto1()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienphoto1->setText(destination);
                     }
            }
            else
            {
                m_lienphoto1->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierdoc2()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_liendoc2->setText(destination);
                     }
            }
            else
            {
                m_liendoc2->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierplan2()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienplan2->setText(destination);
                     }
            }
            else
            {
                m_lienplan2->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierphoto2()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienphoto2->setText(destination);
                     }
            }
            else
            {
                m_lienphoto2->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierdoc3()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_liendoc3->setText(destination);
                     }
            }
            else
            {
                m_liendoc3->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierplan3()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienplan3->setText(destination);
                     }
            }
            else
            {
                m_lienplan3->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierphoto3()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienphoto3->setText(destination);
                     }
            }
            else
            {
                m_lienphoto3->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierdoc4()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_liendoc4->setText(destination);
                     }
            }
            else
            {
                m_liendoc4->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierplan4()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienplan4->setText(destination);
                     }
            }
            else
            {
                m_lienplan4->setText(source.fileName());
            }

        }
    }
}

void setmachine::importer_fichierphoto4()
{
    QString path_in = QFileDialog::getOpenFileName(this, "fichier pdf a importer", QDir::homePath(), "pdf (*.pdf)");
    bool ok = false;
    std::string poubelle="";
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
                if(!QFile::copy(path_in,temp))
                    QMessageBox::critical(this, "erreur", "impossible d'importer le fichier");
                else {
                    m_lienphoto4->setText(destination);
                     }
            }
            else
            {
                m_lienphoto4->setText(source.fileName());
            }

        }
    }
}



void setmachine::sauvegarder()
{
    b->set_machine(mach,num);
}
