#include "Affichage.h"
#include <QtGui/QPaintDevice>
#include <QPushButton>

Affichage::Affichage(ArbreB& arbreB)
{
    quitter = new QPushButton("quitter",this);
    afficher = new QPushButton("afficher",this);
    afficher->move(0,400);
    afficher->show();
    quitter->show();
    arbre = arbreB;
};

Affichage::~Affichage()
{
    delete quitter;
    delete afficher;
};

void Affichage::paint_tree(Noeud * racine, int x , int y)
{

    if(racine != NULL)
    {
        QPainter paint(this);
        paint.drawText(x,y,racine->actuel.formalize_sommet());
        paint.drawLine(x,y-20,x,y+100);
        paint.drawLine(x,y+100,x+150,y+100);
        paint.drawLine(x,y-20,x,y+200);
        paint.drawLine(x,y+200,x+150,y+200);
        paint_tree(racine->filsg, x + 150 , y + 100 );
        paint_tree(racine->filsd, x + 150,  y + 200);
    }
};

void Affichage::paintEvent(QPaintEvent * painter)
{
   if(arbre.getRacine() != NULL)
       paint_tree(arbre.getRacine(),50,50);
};
