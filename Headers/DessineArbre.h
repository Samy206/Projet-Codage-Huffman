#ifndef DESSINEARBRE_H
#define DESSINEARBRE_H

#include "ArbreB.h"
#include "MainMenu.h"

#include <QMainWindow>
#include <QScrollArea>

#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>

class DessineArbre : public QWidget{
private :
    ArbreB arbre;

public :
    DessineArbre(ArbreB&);
    ~DessineArbre();

    void write(QPainter*, int, int, QString);

    void paint_tree(Noeud * racine,  int x , int y, int angle, bool isLeft, int depth, QPainter*);
    void paintEvent(QPaintEvent * painter);

    const int rootLengt=160;
    const double PI=3.1415926;
};

#endif // DESSINEARBRE_H
