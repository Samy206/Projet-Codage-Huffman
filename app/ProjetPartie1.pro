# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = ProjetPartie1 
RESOURCES += qdarkstyle/style.qrc

QT = core gui widgets

HEADERS = \
   $$PWD/CLI/Sommet.h \
   $$PWD/CLI/ArbreB.h \
   $$PWD/CLI/Lecteur.h \
   $$PWD/CLI/Cryptage.h \
   $$PWD/Headers/DessineArbre.h \
   $$PWD/Headers/MainWindow.h \
   $$PWD/Headers/GetUserText.h \
   $$PWD/Headers/Context.h 

SOURCES = \
   $$PWD/CLI/Sommet.cc \
   $$PWD/CLI/ArbreB.cc \
   $$PWD/CLI/Lecteur.cc \
   $$PWD/CLI/Cryptage.cc \
   $$PWD/Sources/DessineArbre.cc \
   $$PWD/Sources/MainWindow.cc \
   $$PWD/Sources/GetUserText.cc \
   $$PWD/Sources/Context.cc \
   $$PWD/Sources/graphicMain.cc

INCLUDEPATH = \
    $$PWD/Headers



#DEFINES = 
