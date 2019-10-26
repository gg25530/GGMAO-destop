#ifndef ADDMACHINEBASE_H
#define ADDMACHINEBASE_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "base.h"

class addmachinebase : public QDialog
{
    Q_OBJECT
public:
     addmachinebase(base &b1,QWidget *parent = 0);

     QLineEdit *nom ;
     QLineEdit *reference;
     QComboBox *fabricant;
     QComboBox *atelier;
     QLineEdit *commentaire;
     QLineEdit *date;
     QLabel *warning;
   public slots:

     void formulaireok();
     bool machineexist(std::string f);
                 private:
                 base *b;
                 QPushButton *okButton;
                 QPushButton *cancelButton;

};

#endif // ADDMACHINEBASE_H
