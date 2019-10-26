#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T16:54:40
#
#-------------------------------------------------

QT       += core gui charts printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = truc3
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    pieces.cpp \
    fichiers.cpp \
    base.cpp \
    addpiecesbase.cpp \
    machine.cpp \
    bt.cpp \
    date.cpp \
    commandes.cpp \
    addbtbase.cpp \
    addcommandebase.cpp \
    addmachinebase.cpp \
    addtablebase.cpp \
    setpiecesbase.cpp \
    addpiecesmachine.cpp \
    parametres.cpp \
    setmachine.cpp \
    setbtbase.cpp \
    setcommande.cpp \
    mainwindow-exportpdf.cpp \
    mainwindow-maj-models.cpp \
    traceur.cpp \
    trace.cpp \
    listutilisationpieces.cpp \
    fournisseurs.cpp \
    mainwindow-stats.cpp \
    mainwindow-tri.cpp \
    unthread.cpp \

HEADERS += \
        mainwindow.h \
    pieces.h \
    fichiers.h \
    base.h \
    addpiecesbase.h \
    machine.h \
    bt.h \
    date.h \
    machine.h \
    commandes.h \
    addbtbase.h \
    addcommandebase.h \
    addmachinebase.h \
    addtablebase.h \
    setpiecesbase.h \
    addpiecesmachine.h \
    parametres.h \
    setmachine.h \
    setbtbase.h \
    setcommande.h \
    traceur.h \
    trace.h \
    listutilisationpieces.h \
    fournisseurs.h \
    unthread.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
