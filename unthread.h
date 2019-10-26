#ifndef UNTHREAD_H
#define UNTHREAD_H

#include <QThread>
#include "mainwindow.h"

// une classe héritée de QThread
class UnThread : public QThread
{
    Q_OBJECT

public:
    explicit UnThread(MainWindow *window, QObject *parent = 0);
    void run();

private:

    // le caractère que le Thread impimera
    MainWindow *c;
    
};

#endif // UNTHREAD_H
