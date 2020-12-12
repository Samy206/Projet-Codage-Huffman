#ifndef DISPLAYRESULTS_H
#define DISPLAYRESULTS_H

#include "Context.h"

#include <QMainWindow>

#include <QLabel>
#include <QBoxLayout>



/**
 * @file DisplayResults.h
 * @brief Permet l'affichage des résultats de l'encodage sous la forme d'un Label dans un Layout positionné à droite de l'interface graphique.
 * 
 * @private   QLabel      Résultats à afficher
 */
class DisplayResults : public QWidget {

    Q_OBJECT

private :
    QLabel *results;
    QLabel *signature;
    QVBoxLayout *layout;

    std::map <char,std::string> map_res;

public :
    /**
     * Constructeur par défaut
     */ 
    DisplayResults()  {
        layout = new QVBoxLayout();
        setLayout(layout);

        map_res = Context::getInstance().getMapRes();
        std::string tmp = "<center><b>Résultats de l'encodage</b></center><br></br>";
        for (std::pair <char,std::string> p : map_res) {
            tmp += p.first;
            tmp += " : ";
            tmp += p.second;
            tmp += "<br></br>";
        }

        // QLabel pour afficher les résultats
        results = new QLabel(QString::fromStdString(tmp));
        // results->setAlignment(Qt::AlignCenter);
        results->setMargin(10);
        results->show();
        layout->addWidget(results, Qt::AlignCenter);

        layout->addSpacing(40);
        // QLabel signature
        signature = new QLabel("<center><b>Projet LA - Partie 2</b><br></br>Samy BOUMALI & Amine ATEK</center>");
        signature->show();
        layout->addWidget(signature,Qt::AlignBottom);

        connect(&Context::getInstance(), SIGNAL(resultsArrived()), this, SLOT(resultsArrived()));
    };

    /**
     * Destructeur de classe
     */ 
    ~DisplayResults() {};

    

public slots:

    /**
     * @brief Réaffiche les résultats quand ils arrivent
     * 
     */
    void resultsArrived()  {
        std::string tmp;
        map_res = Context::getInstance().getMapRes();
        if (map_res.size() > 0)  {
            tmp = "<center><b>Résultats de l'encodage</b></center><br></br>";
            for (std::pair <char,std::string> p : map_res) {
                tmp += p.first;
                tmp += " : ";
                tmp += p.second;
                tmp += "<br></br>";
            }
        }
        else
            tmp = "<center><b>Aucun encodage nécessaire</b></center>";
        

        // On actualise l'affichage du texte 
        results->setText(QString::fromStdString(tmp));
    };

signals: 

};

#endif // DISPLAYRESULTS_H
