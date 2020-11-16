#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "ArbreB.h"
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>

class Affichage : public QWidget{
    private :
      QPushButton * quitter;
      QPushButton * afficher;
      ArbreB arbre;

    public :
       Affichage(ArbreB&);
       ~Affichage();

       void paintEvent(QPaintEvent * painter);
       void paint_tree(Noeud * racine, int x , int y);
};

#endif // AFFICHAGE_H
