#include "mainwindow.h"
#include <QApplication>
#include "base.h"
#include "pieces.h"
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*
QFile fichier("poeme.txt");

if(!fichier.copy("copie.txt"))

    QMessageBox::critical(NULL,"Erreur","Impossible de copier poeme.txt");

*/

/*if(!QFile::exists("poeme.txt"))

    QMessageBox::critical(NULL,"Erreur","Le fichier spécifié n'existe pas !");

else QMessageBox::information(NULL,"Information","Le fichier spécifié existe !");


ou

if(!QFile::remove("poeme.txt"))

    QMessageBox::critical(NULL,"Erreur","Impossible de supprimer le fichier !");

*/

/*
QFile fichier("poeme.txt");

if(!fichier.rename("nouveau_nom.txt"))

    QMessageBox::critical(NULL,"Erreur","Impossible de renommer le fichier !");

    */
