#include "DessineArbre.h"
#include <math.h>
#include <QDebug>
#include <QtGui/QPaintDevice>

DessineArbre::DessineArbre(ArbreB& arbreB) {
    arbre = arbreB;
    setFixedSize(700, 2000);
};

void DessineArbre::write(QPainter *p, int x, int y, QString txt) {
    int taille_x = p->fontMetrics().horizontalAdvance(txt);
    p->drawText(x - taille_x/2, y, txt);
}

void DessineArbre::paint_tree_samy(Noeud *racine, int x , int y, QPainter *paint) {
    if (racine == NULL)
        return;

    char* sommet_txt = racine->actuel.formalize_sommet();
    int mid_txt = paint->fontMetrics().horizontalAdvance(sommet_txt) / 2;

    paint->drawText(x, y, sommet_txt);

    paint->drawLine(x+mid_txt, y+5,  x+mid_txt,     y+100);
    paint->drawLine(x+mid_txt, y+100, x+mid_txt+150, y+100);

    paint->drawLine(x+mid_txt, y+5,  x+mid_txt,     y+200);
    paint->drawLine(x+mid_txt, y+200, x+mid_txt+150, y+200);

    paint_tree_samy(racine->filsg, x + 150 , y + 100, paint);
    paint_tree_samy(racine->filsd, x + 150,  y + 200, paint);
}

/* */
int compte_profondeur(Noeud *courant) {
    if (courant == NULL)
        return 0;
    return 1 + compte_profondeur(courant->filsg) + compte_profondeur(courant->filsd);
}

void DessineArbre::paint_tree_scales(Noeud *racine, int x , int *y, int last, int k, QPainter *p) {
    if (racine == NULL)
        return;

    int hauteur_texte = p->fontMetrics().height();
    int longueur_texte = p->fontMetrics().horizontalAdvance(racine->actuel.formalize_sommet());
    // p->drawText(x, *y, racine->actuel.formalize_sommet());
    // p->drawRoundedRect(QRectF(x, *y-hauteur_texte, longueur_texte, hauteur_texte), 10, 10);

    const QRectF Rect(x, *y, longueur_texte+20, hauteur_texte+8);
    p->drawText(Rect, Qt::AlignCenter, racine->actuel.formalize_sommet());
    p->drawRoundedRect(Rect, 10, 10);


    if (last == 0) {
        // Ancien espace + ligne verticale + nouvel espace
        p->drawLine(x, *y, x, *y+(k*compte_profondeur(racine)));
        *y += k;
    }
    else {
        // Ancien espace + nouvel espace
        *y += k;
        // p->drawLine(x, *y, x+30, *y);
    }

    if (racine->filsg != NULL && racine->filsd != NULL) {
        paint_tree_scales(racine->filsg, x+k, y, 0, k, p);
        paint_tree_scales(racine->filsd, x+k, y, 1, k, p);
    }
    else {
        if (racine->filsd != NULL )
            paint_tree_scales(racine->filsd, x+30, y, 1, k, p);

        else
            paint_tree_scales(racine->filsd, x+30, y, 0, k, p);

        if (racine->filsg != NULL)

            paint_tree_scales(racine->filsg, x+30, y, 1, k, p);
        else
            paint_tree_scales(racine->filsg, x+30, y, 0, k, p);
    }
    /*
    if(racine->filsg != NULL || racine->filsd != NULL)
    {
        if(racine->filsg != NULL && racine->filsd != NULL)
        {
            int i = *y;
            while(i != *y+30)
            {
                i += 5;
                p->drawLine(x+30,i-5,x+30,i);
                i+= 5;
            }
            paint_tree_scales(racine->filsg, x+30,y,1,p);
            paint_tree_scales(racine->filsd, x+30,y,0,p);
        }
        else if (racine->filsg != NULL && racine->filsd == NULL)
               paint_tree_scales(racine->filsg, x+30,y,1,p);

        else if (racine->filsg == NULL && racine->filsd != NULL)
               paint_tree_scales(racine->filsd, x+30,y,1,p);
    } */
}

void DessineArbre::paint_tree(Noeud *racine, int x , int y, int angle, bool isLeft, int depth, QPainter *p) {
    // std::cout << "Painter: start " << racine->actuel.formalize_sommet() << std::endl;
    int leftAngle, rightAngle;
    int dx, dy, nx, ny;
    if (racine == NULL)
        return;

    p->drawEllipse(x, y, 5, 5);
    write(p, x, y-10, racine->actuel.formalize_sommet());
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
};

void DessineArbre::paintEvent(QPaintEvent *e) {
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);
    int y = 70;

    write(&paint, width()/2, 20, "Test: Constructeur par copie");
    write(&paint, width()/2, 40, "Génération d'un arbre construit par copie");

    // paint_tree(arbre.getRacine(), width()/2, y, 10, true, 0, &paint);
    // paint_tree_samy(arbre.getRacine(), 10, y, &paint);

    paint_tree_scales(arbre.getRacine(), 10, &y, 1, 30, &paint);
};

DessineArbre::~DessineArbre() { };
