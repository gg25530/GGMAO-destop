#ifndef SETCOMMANDE_H
#define SETCOMMANDE_H


#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "base.h"

class setcommande : public QDialog
{
    Q_OBJECT
public:
     setcommande(base &b1,int numero , QWidget *parent = 0);

     QLineEdit *reference;
     QComboBox *destinataire;
     QComboBox *fournisseur;
     QLineEdit *prix;
     QLineEdit *date;
     QLineEdit *commentaire;
      int num;
      commandes comm;
   public slots:

     void formulaireok();

                 private:
                 base *b;
                 QPushButton *okButton;
                 QPushButton *cancelButton;

};

#endif // SETCOMMANDE_H
