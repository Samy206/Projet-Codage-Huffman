#ifndef DESSINEARBRE_H
#define DESSINEARBRE_H

#include "ArbreB.h"
#include "MainMenu.h"

#include <QMainWindow>
#include <QScrollArea>

#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>


/**
 * Permet le dessin d'un arbre binaire sur la zone graphique, affiché de gauche à droite.
 * 
 * @arbre   ArbreB      Arbre binaire à afficher
 */
class DessineArbre : public QWidget{
private :
    ArbreB arbre;

public :
    /**
     * Constructeur par défaut
     */ 
    DessineArbre(ArbreB&);

    /**
     * Destructeur de classe
     */ 
    ~DessineArbre();

    /**
     * Ecrit un @QString sur l'interface 
     * */
    void write(QPainter*, int, int, QString);

    /** 
     * Représente l'arbre binaire sur l'interface
     */ 
    void paint_tree_scales(Sommet *, int x , int *y, int last, int k, QPainter*, QPen*);
    void paint_tree(Sommet *,  int x , int y, int angle, bool isLeft, int depth, QPainter*);

    /**
     * Déclenche l'évènement "dessin" à l'exécution du programme 
     */  
    void paintEvent(QPaintEvent * painter);

    const int rootLengt=160;
    const double PI=3.1415926;
};

#endif // DESSINEARBRE_H
