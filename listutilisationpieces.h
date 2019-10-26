#ifndef LISTUTILISATIONPIECES_H
#define LISTUTILISATIONPIECES_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "date.h"
#include "base.h"

class listutilisationpieces : public QDialog
{
public:
    listutilisationpieces(base &b1,int num, QWidget *parent = 0);


public slots:


              private:
    QComboBox *Lnum;

              base *b;
              QPushButton *okButton;


};

#endif // LISTUTILISATIONPIECES_H
