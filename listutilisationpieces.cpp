#include "listutilisationpieces.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <ctime>
#include <sstream>
#include <iostream>
#include "base.h"

listutilisationpieces::listutilisationpieces(base &b1,int num , QWidget *parent) : QDialog(parent)
{

         b = &b1;
        std::vector <std::string> listmach;

        b->getlistmachinespiece(listmach,num);
        int x = listmach.size();
        Lnum = new QComboBox;
        for(int a=0; a < listmach.size() ; a++)
        {
            Lnum->addItem(listmach[a].c_str());
        }
       QVBoxLayout *grille = new QVBoxLayout;

      grille->addWidget(Lnum);


       okButton = new QPushButton("OK");
       grille->addWidget(okButton);
       this->setLayout(grille);
       this->show();


       connect(okButton,&QAbstractButton::clicked, this,&QDialog::accept);



}
