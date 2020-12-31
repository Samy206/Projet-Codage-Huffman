######################################################################
# Automatically generated by qmake (3.1) Thu Dec 31 10:36:22 2020
######################################################################

TEMPLATE = app
TARGET = QMakefile
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += app/Headers/GUI/Context.h \
           app/Headers/GUI/DessineArbre.h \
           app/Headers/GUI/DisplayResults.h \
           app/Headers/GUI/GetUserText.h \
           app/Headers/GUI/MainWindow.h \
           app/Headers/Partie2/ArbreB.h \
           app/Headers/Partie2/Cryptage.h \
           app/Headers/Partie2/Decryptage.h \
           app/Headers/Partie2/Lecteur.h \
           app/Headers/Partie2/Sommet.h
SOURCES += app/Sources/GUI/Context.cc \
           app/Sources/GUI/DessineArbre.cc \
           app/Sources/GUI/GetUserText.cc \
           app/Sources/GUI/graphicMain.cc \
           app/Sources/GUI/MainWindow.cc \
           app/Sources/Partie2/ArbreB.cc \
           app/Sources/Partie2/Cryptage.cc \
           app/Sources/Partie2/Decryptage.cc \
           app/Sources/Partie2/Lecteur.cc \
           app/Sources/Partie2/Sommet.cc \
           app/Sources/Partie2/TestArbre.cc
RESOURCES += qdarkstyle/style.qrc
