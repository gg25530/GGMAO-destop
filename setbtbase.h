#ifndef SETBTBASE_H
#define SETBTBASE_H

#include "date.h"
#include "base.h"
#include "bt.h"
#include <QApplication>
#include <QtWidgets>
#include <QDialog>

class setbtbase : public QDialog
{
    Q_OBJECT

public:
     setbtbase(base &b1,int numero,QWidget *parent = 0);

     QLineEdit *date ;
     QTextEdit *commentaire;
     QLineEdit *temps;
     QComboBox *machine;
     QComboBox *tech;
     QComboBox *type;
     QComboBox *atelier;
     bt bont;
     int num;
   public slots:
     void majcomboboxmachine();
     void formulaireok();
     bool dateok();

                 private:
     base *b;
     datee calendrier;
                 QPushButton *okButton;
                 QPushButton *cancelButton;

};

#endif // SETBTBASE_H
