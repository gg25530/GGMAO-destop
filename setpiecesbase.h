#ifndef SETPIECESBASE_H
#define SETPIECESBASE_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "date.h"
#include "base.h"

class setpiecesbase : public QDialog
{
    Q_OBJECT
public:
     setpiecesbase(base &b1,int numero,QWidget *parent = 0);

     QLineEdit *nom ;
     QLineEdit *reference;
     QComboBox *fabricant;
     QLineEdit *prix;
     QLineEdit *commentaire;
     QLineEdit *m_qty;
     QLineEdit *d;
     QLineEdit *m_emplacement;
     QLineEdit *m_adresse;
     QComboBox *m_categorie;
     QLineEdit *m_liendoc;
     QLineEdit *m_lienplan;
     QLineEdit *m_lienphoto;
     QComboBox *m_fournisseur1;
     QComboBox *m_fournisseur2;
     QComboBox *m_fournisseur3;
     QLabel *Lkey;
   public slots:

     void formulaireok();
     void importer_fichierdoc();
     void importer_fichierplan();
     void importer_fichierphoto();
     void fournisseurs_changed();
     void infosusepiece();


                 private:
                 base *b;
                 QPushButton *okButton;
                 QPushButton *useButton;
                 QPushButton *cancelButton;

};

#endif // SETPIECESBASE_H
