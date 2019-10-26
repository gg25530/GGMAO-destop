#ifndef SETMACHINE_H
#define SETMACHINE_H


#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "date.h"
#include "base.h"
#include "machine.h"


class setmachine : public QDialog
{
    Q_OBJECT
public:
     setmachine(base &b1,int numero,QWidget *parent = 0);
     QLineEdit *nom ;
     QLineEdit *reference;
     QComboBox *fabricant;
     QLineEdit *commentaire;
     QLineEdit *d;
     QComboBox *atelier;
     QLineEdit *m_liendoc1;
     QLineEdit *m_lienplan1;
     QLineEdit *m_lienphoto1;
     QLineEdit *m_liendoc2;
     QLineEdit *m_lienplan2;
     QLineEdit *m_lienphoto2;
     QLineEdit *m_liendoc3;
     QLineEdit *m_lienplan3;
     QLineEdit *m_lienphoto3;
     QLineEdit *m_liendoc4;
     QLineEdit *m_lienplan4;
     QLineEdit *m_lienphoto4;
     machine mach;
     int num;
   public slots:
     void sauvegarder();
     void formulaireok();
     void importer_fichierdoc1();
     void importer_fichierdoc2();
     void importer_fichierdoc3();
     void importer_fichierdoc4();
     void importer_fichierplan1();
     void importer_fichierplan2();
     void importer_fichierplan3();
     void importer_fichierplan4();
     void importer_fichierphoto1();
     void importer_fichierphoto2();
     void importer_fichierphoto3();
     void importer_fichierphoto4();

                 private:
                 base *b;
                 QPushButton *okButton;
                 QPushButton *cancelButton;


};



#endif // SETMACHINE_H
