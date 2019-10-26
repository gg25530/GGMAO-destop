#ifndef ADDPIECESBASE_H
#define ADDPIECESBASE_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "base.h"

class addpiecesbase : public QDialog
{
    Q_OBJECT
public:
     addpiecesbase(base &b1,QWidget *parent = 0);

     QLineEdit *nom ;
     QLineEdit *reference;
     QComboBox *fabricant;
     QComboBox *fournisseur;
     QLineEdit *prix;
     QLineEdit *commentaire;
      QLabel * erreur;
   public slots:

     void formulaireok();

                 private:
     base *b;

                 QPushButton *okButton;
                 QPushButton *cancelButton;

};

#endif // ADDPIECESBASE_H
