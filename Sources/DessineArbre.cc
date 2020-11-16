#include "DessineArbre.h"
#include <math.h>
#include <QtGui/QPaintDevice>

DessineArbre::DessineArbre(ArbreB& arbreB) {
    arbre = arbreB;
    setFixedSize(700, 500);
};

void DessineArbre::write(QPainter *p, int x, int y, QString txt) {
    int taille_x = p->fontMetrics().horizontalAdvance(txt);
    p->drawText(x - taille_x/2, y, txt);
}

void DessineArbre::paint_tree(Noeud *racine, int x , int y, int angle, bool isLeft, int depth, QPainter *p) {
    // std::cout << "Painter: start " << racine->actuel.formalize_sommet() << std::endl;
    int leftAngle, rightAngle;
    int dx, dy, nx, ny;
    if (racine == NULL)
        return;

    write(p, x, y, racine->actuel.formalize_sommet());
    // p->drawText(x,y, racine->actuel.formalize_sommet());

    if (racine->filsg != NULL) {

        if (depth<2)
            leftAngle = angle + rand()%15;
        else {
            if (!isLeft)
                leftAngle = angle + rand()%5 + 10;
            else
                leftAngle = rand()%45;
        }

        int lenEdge = rootLengt-depth*35;
        dx = -cos(leftAngle*PI/180)*lenEdge;
        dy = sin(leftAngle*PI/180)*lenEdge;
        nx = x+dx;
        ny = y+dy;

        // std::cout << "Painter: end->left " << racine->filsg->actuel.formalize_sommet() << std::endl;
        p->drawLine(x,y, nx, ny);
        paint_tree(racine->filsg,nx,ny,leftAngle,true,depth+1, p);
    }
    if (racine->filsd != NULL) {

        if (depth<2)
                    rightAngle = angle + rand()%15;
        else {
            if (isLeft)
                rightAngle = angle + rand()%5 + 10;
            else
                rightAngle = rand()%45;
        }

        int lenEdge = rootLengt-depth*15;
        dx = cos(rightAngle*PI/180)*lenEdge;
        dy = sin(rightAngle*PI/180)*lenEdge;
        nx = x+dx;
        ny = y+dy;

        // std::cout << "Painter: end->right " << racine->filsd->actuel.formalize_sommet() << std::endl;
        p->drawLine(x,y,nx,ny);
        paint_tree(racine->filsd, nx, ny, rightAngle, false, depth+1, p);
    }

    if (racine->filsg==NULL && racine->filsd==NULL) {return ; }

    /*
    if(racine != NULL)
    {
        QPainter paint(this);
        char* data = racine->actuel.formalize_sommet();



        char* sommet_txt = racine->actuel.formalize_sommet();
        int mid_txt = paint.fontMetrics().horizontalAdvance(sommet_txt) / 2;

        paint.drawText(x, y, sommet_txt);

        paint.drawLine(x+mid_txt, y+5,  x+mid_txt,     y+100);
        paint.drawLine(x+mid_txt, y+100, x+mid_txt+150, y+100);

        paint.drawLine(x+mid_txt, y+5,  x+mid_txt,     y+200);
        paint.drawLine(x+mid_txt, y+200, x+mid_txt+150, y+200);

        paint_tree(racine->filsg, x + 150 , y + 100 );
        paint_tree(racine->filsd, x + 150,  y + 200);

    } */
};

void DessineArbre::paintEvent(QPaintEvent *e) {
    QPainter paint(this);

    write(&paint, width()/2, 20, "Test: Constructeur par copie");
    write(&paint, width()/2, 40, "Génération d'un arbre construit par copie");

    paint_tree(arbre.getRacine(), width()/2, 70, 10, true, 0, &paint);
   /*
   if(arbre.getRacine() != NULL)
       paint_tree(arbre.getRacine(), 50, 50, 1); */
};

DessineArbre::~DessineArbre() { };
