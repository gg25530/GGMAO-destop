#ifndef ADDPIECESMACHINE_H
#define ADDPIECESMACHINE_H

#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "date.h"
#include "base.h"


        class addpiecesmachine : public QDialog
        {
            Q_OBJECT
        public:
             addpiecesmachine(base &b1,QWidget *parent = 0);


             QComboBox *machine;

             QComboBox *atelier;

           public slots:
             void majcomboboxmachine();
             void formulaireok();

                         private:
             base *b;
                         QPushButton *okButton;
                         QPushButton *cancelButton;

        };


#endif // ADDPIECESMACHINE_H
