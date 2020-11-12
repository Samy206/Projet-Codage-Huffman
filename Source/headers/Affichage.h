#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "ArbreB.h"

#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>

class Affichage {
    public:
        Affichage(QGraphicsScene* scene, QGraphicsView* view);

        // void preorderWalk();

        void show(ArbreB);

    private:
        QGraphicsScene* _scene;
        QGraphicsView* _view;

        // void preorderWalk(Noeud* p);
        QByteArray _prepareGraph(ArbreB);
        void _graphWalk(Noeud* p,  QTextStream* stream);
};

#endif // AFFICHAGE_H
