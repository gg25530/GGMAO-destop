#ifndef ADDBTBASE_H
#define ADDBTBASE_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "date.h"
#include "base.h"

class addbtbase : public QDialog
{
    Q_OBJECT
public:
     addbtbase(base &b1,QWidget *parent = 0);

     QLineEdit *date ;
     QTextEdit *commentaire;
     QLineEdit *temps;
     QComboBox *machine;
     QComboBox *tech;
     QComboBox *type;
     QComboBox *atelier;
     QLineEdit *m_lienphoto1;
     QLineEdit *m_lienphoto2;
     QLineEdit *m_lienphoto3;
     QLineEdit *m_lienphoto4;


   public slots:
     void importer_photo1();
     void importer_photo2();
     void importer_photo3();
     void importer_photo4();
     void majcomboboxmachine();
     void formulaireok();
     bool dateok();

                 private:
     base *b;
     datee calendrier;
                 QPushButton *okButton;
                 QPushButton *cancelButton;

};

#endif // ADDBTBASE_H
