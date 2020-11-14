#include "Affichage.h"

Affichage::Affichage(QGraphicsScene* scene, QGraphicsView* view) {
    this->_scene = scene;
    this->_view = view;
}

QByteArray Affichage::_prepareGraph(ArbreB arbre){
    QByteArray a = QByteArray();

    QTextStream stream(&a, QIODevice::ReadWrite);
    stream << "graph ""{" << Qt::endl;
    stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << Qt::endl;
    stream << "\tsubgraph cluster17{" << Qt::endl;

    this->_graphWalk(arbre.getRacine(), &stream);
    stream << "\t}\n" << "}" << Qt::endl;
    stream.flush();

    return a;
}

void Affichage::_graphWalk(Noeud* p, QTextStream *stream) {
    if (p != NULL){
        *stream << "\t\t" << "n" << p->actuel.getLettre() << "[label=\"" << p->actuel.formalize_sommet() <<"\"];" << Qt::endl;

        if(p->filsg != NULL) {
            *stream << "\t\tn" << p->actuel.getLettre() << "--" << "n" << p->filsg->actuel.getLettre() << ";" << Qt::endl;
            this->_graphWalk(p->filsg, stream);
        } /*
        else {
            *stream << "\t\t" << "n" << p->actuel.getLettre() << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << Qt::endl;
            *stream << "\t\tn" << p->actuel.getLettre() << "--" << "n" << p->actuel.getLettre() << "leftNull" << Qt::endl;
        } */

        if(p->filsd != NULL) {
            *stream << "\t\tn" << p->actuel.getLettre() << "--" << "n" << p->filsd->actuel.getLettre() << ";" << Qt::endl;
            this->_graphWalk(p->filsd, stream);
        } /*
        else{
            *stream << "\t\t" << "n" << p->actuel.getLettre() << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << Qt::endl;
            *stream << "\t\tn" << p->actuel.getLettre() << "--" << "n" << p->actuel.getLettre() << "rightNull" << Qt::endl;
        } */
    }
}

void Affichage::show(ArbreB arbre) {
    QProcess* p = new QProcess();
    QByteArray a = this->_prepareGraph(arbre);

    p->setProcessChannelMode(QProcess::MergedChannels);
    p->start("dot", QStringList() << "-Tpng");
    p->write(a);

    QByteArray data;
    QPixmap pixmap = QPixmap();

    while(p->waitForReadyRead(100)){
        data.append(p->readAll());
    }

    pixmap.loadFromData(data);

    this->_scene->addPixmap(pixmap);
    this->_view->show();
}
