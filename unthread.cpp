#include "unthread.h"
#include "mainwindow.h"
#include <iostream>

using namespace std;

UnThread::UnThread(MainWindow *window, QObject *parent) :
    QThread(parent)
{
    this->c = window;        // le caractère à imprimer
}


// la fonction qui s'exécute au sein du Thread
void UnThread::run()
    {
     c->majmodelpieces();
     c->maj_fournisseurs();
    }

