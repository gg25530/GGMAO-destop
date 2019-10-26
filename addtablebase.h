#ifndef ADDTABLEBASE_H
#define ADDTABLEBASE_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "base.h"

class addtablebase : public QDialog
{
    Q_OBJECT
public:
     addtablebase(base &b1,QWidget *parent = 0);
    QComboBox *choix_table;
     QLineEdit *f;
     QLabel *warning;
   public slots:

     void formulaireok();
     bool elementexist(std::string f);
     void loadtable();
                 private:
                 base *b;
                 QPushButton *okButton;
                 QPushButton *cancelButton;

};

#endif // ADDTABLEBASE_H
