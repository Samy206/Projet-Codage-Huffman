#include "DessineArbre.h"
#include <math.h>
#include <QDebug>
#include <QtGui/QPaintDevice>

DessineArbre::DessineArbre(ArbreB& arbreB) {
    arbre = arbreB;
    resize(800, 500);
};

void DessineArbre::write(QPainter *p, int x, int y, QString txt) {
    int taille_x = p->fontMetrics().horizontalAdvance(txt);
    p->drawText(x - taille_x/2, y, txt);
}

/* */
int compte_profondeur(Sommet *courant) {
    if (courant == NULL)
        return 0;
    return 1 + compte_profondeur(courant->getFilsG()) + compte_profondeur(courant->getFilsD());
}

void DessineArbre::paint_tree_scales(Sommet *racine, int x , int *y, int last, int k, QPainter *p, QPen *pen) {
    if (racine == NULL)
        return;
    if (x > 800)
        resize(x, *y);

    int hauteur_texte = p->fontMetrics().height();
    int longueur_texte = p->fontMetrics().horizontalAdvance(racine->formalize_sommet());
    longueur_texte = 55;
    // qDebug() << "Longueur: " << longueur_texte << ", hauteur: " << hauteur_texte;
    const QRectF Rect(x, *y, longueur_texte+20, hauteur_texte+8);
    p->drawText(Rect, Qt::AlignCenter, racine->formalize_sommet());
    p->drawRoundedRect(Rect, 10, 10);

    /* Possède un frère: ligne verticale liant les deux frères */
    if (last == 0) {
        // pen->setColor(Qt::green);
        pen->setStyle(Qt::DashDotLine);
        p->setPen(*pen);
        p->drawLine(x + 20, *y+hauteur_texte+8,x+20, *y+(k*compte_profondeur(racine)));
    }
    /* N'a pas d'autre frère: */
    // else { }
    /* Possède au moins un fils */
    if (racine->getFilsG() != NULL || racine->getFilsD() != NULL) {
        pen->setColor(Qt::blue);
        pen->setStyle(Qt::SolidLine);
        p->setPen(*pen);

        int new_y = (*y+hauteur_texte+8)+k - hauteur_texte/2;

        p->drawLine(x+longueur_texte, *y+hauteur_texte+8, x+longueur_texte, new_y);
        p->drawLine(x+longueur_texte, new_y, x+longueur_texte+17, new_y);
    }
    *y += k;


    pen->setColor(Qt::black);
    pen->setStyle(Qt::SolidLine);
    p->setPen(*pen);
    if (racine->getFilsG() != NULL && racine->getFilsD() != NULL) {
        paint_tree_scales(racine->getFilsG(), x+1.8*k, y, 0, k, p, pen);
        paint_tree_scales(racine->getFilsD(), x+1.8*k, y, 1, k, p, pen);
    }
    else {
        if (racine->getFilsD() != NULL )
            paint_tree_scales(racine->getFilsD(), x+1.8*k, y, 1, k, p, pen);

        else
            paint_tree_scales(racine->getFilsD(), x+1.8*k, y, 0, k, p, pen);

        if (racine->getFilsG() != NULL)

            paint_tree_scales(racine->getFilsG(), x+1.8*k, y, 1, k, p, pen);
        else
            paint_tree_scales(racine->getFilsG(), x+1.8*k, y, 0, k, p, pen);
    }

}

void DessineArbre::paint_tree(Sommet *racine, int x , int y, int angle, bool isLeft, int depth, QPainter *p) {
    // std::cout << "Painter: start " << racine->actuel.formalize_sommet() << std::endl;
    int leftAngle, rightAngle;
    int dx, dy, nx, ny;
    if (racine == NULL)
        return;

    p->drawEllipse(x, y, 5, 5);
    write(p, x, y-10, racine->formalize_sommet());
    // p->drawText(x,y, racine->actuel.formalize_sommet());

    if (racine->getFilsG() != NULL) {

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
        paint_tree(racine->getFilsG(),nx,ny,leftAngle,true,depth+1, p);
    }
    if (racine->getFilsD() != NULL) {

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
        paint_tree(racine->getFilsD(), nx, ny, rightAngle, false, depth+1, p);
    }

    if (racine->getFilsG()==NULL && racine->getFilsD()==NULL) {return ; }
};

void DessineArbre::paintEvent(QPaintEvent *e) {
    QPainter paint(this);
    QPen pen(Qt::black, 2);
    paint.setPen(pen);

    paint.setRenderHint(QPainter::Antialiasing);
    int y = 70;

    write(&paint, width()/2, 20, "Test: Constructeur par copie");
    write(&paint, width()/2, 40, "Génération d'un arbre construit par copie");

    // paint_tree(arbre.getRacine(), width()/2, y, 10, true, 0, &paint);

    paint_tree_scales(arbre.getRacine(), 10, &y, 1, 40, &paint, &pen);
    resize(800, y);

    // paint_tree_scales_2(arbre.getRacine(), width()/2, &y, 1, 50, &paint);
};

DessineArbre::~DessineArbre() { };
