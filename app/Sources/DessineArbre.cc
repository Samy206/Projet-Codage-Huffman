#include "DessineArbre.h"
#include <math.h>
#include <QDebug>
#include <QtGui/QPaintDevice>

int max_x = 200;
/**
 * Constructeur par défaut
 */ 
DessineArbre::DessineArbre() {
    qDebug() << "DessineArbre: Chargement de l'arbre..";
    arbre = Context::getInstance().getArbre();
    qDebug() << "DessineArbre: Arbre chargé";
    resize(max_x, 500);

    connect(&Context::getInstance(), SIGNAL(arbreChanged()), this, SLOT(arbreChanged()));
};

/**
 * Ecrit un @QString sur l'interface 
 */
void DessineArbre::write(QPainter *p, int x, int y, QString txt) {
    int taille_x = p->fontMetrics().horizontalAdvance(txt);
    p->drawText(x - taille_x/2, y, txt);
}

/**
 * Compte le nombre de sommet fils avant de revenir au frère de @courant
 */
int compte_profondeur(Sommet *courant) {
    if (courant == NULL)
        return 0;
    return 1 + compte_profondeur(courant->getFilsG()) + compte_profondeur(courant->getFilsD());
}

/**
 * Fonction principale d'affichage: affiche l'arbre binaire de la gauche vers la droite.
 * 
 * Deux fils d'un même sommets sont liés par un trait vertical noir.
 * Un fils est lié à son père par un trait angulaire bleu.
 */  
void DessineArbre::paint_tree_scales(Sommet *racine, int x , int *y, int last, int k, QPainter *p, QPen *pen) {
    std::cout << "Picasso: En action." << std::endl;
    // Condition d'arrêt de la récursion
    if (racine == NULL)
        return;

    // On réajuste la taille de la zone si l'arbre dépasse la zone de base
    if (x > max_x) {
        max_x = x;
    }


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

/**
 * Déclenche l'évènement "dessin" à l'exécution du programme 
 */  
void DessineArbre::paintEvent(QPaintEvent *e) {
    std::cout << "PaintEvent: Je fais mon taff de suite !" << std::endl;

    QPainter paint(this);
    QPen pen(Qt::black, 2);
    paint.setPen(pen);
    paint.setRenderHint(QPainter::Antialiasing);
    
    write(&paint, width()/2, 20, "Test: Constructeur par copie");
    write(&paint, width()/2, 40, "Génération d'un arbre construit par copie");
    
    int y = 70;
    paint_tree_scales(arbre->getRacine(), 10, &y, 1, 40, &paint, &pen);
    resize(max_x+90, y);
};

DessineArbre::~DessineArbre() { };

void DessineArbre::setArbre() {
    std::cout << "DessineArbre::setArbre: jsp pk jsuis la moi" << std::endl;
    // Context::getInstance().setArbre(arbre);
}

void DessineArbre::arbreChanged() {
    std::cout << "ArbreChanged: Signal reçu par ici, j'appelle le getter !" << std::endl;
    arbre = Context::getInstance().getArbre();
    std::cout << "ArbreChanged: Nouvel arbre reçu :" << std::endl;
    std::cout << *arbre << std::endl;
}
