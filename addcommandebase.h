#ifndef ADDCOMMANDEBASE_H
#define ADDCOMMANDEBASE_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "base.h"

class addcommandebase : public QDialog
{
    Q_OBJECT
public:
     addcommandebase(base &b1,QWidget *parent = 0);

     QLineEdit *reference;
     QComboBox *destinataire;
     QComboBox *fournisseur;
     QLineEdit *prix;
     QLineEdit *date;
     QLineEdit *commentaire;

   public slots:

     void formulaireok();

                 private:
                 base *b;
                 QPushButton *okButton;
                 QPushButton *cancelButton;

};

#endif // ADDCOMMANDEBASE_H
