#ifndef PARAMETRES_H
#define PARAMETRES_H
#include <QApplication>
#include <QtWidgets>
#include <QDialog>
#include "base.h"

class parametres : public QDialog
{
    Q_OBJECT

public:
    parametres(base &b1,QWidget *parent = 0);
public slots:
    void sauvegardes();
    void affecterpath();

    private:
    base *b;
    QPushButton *okButton;
    QPushButton *definepathButton;
    QLineEdit *path;
    QLineEdit *name;

};

#endif // PARAMETRES_H
