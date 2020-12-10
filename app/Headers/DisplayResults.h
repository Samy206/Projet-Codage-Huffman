#ifndef DISPLAYRESULTS_H
#define DISPLAYRESULTS_H

#include "Context.h"

#include <QMainWindow>

#include <QLabel>
#include <QBoxLayout>



/**
 * Permet l'affichage des résultats de l'encodage
 * 
 * @results   QLabel      Résultats à afficher
 */
class DisplayResults : public QWidget {

    Q_OBJECT

private :
    QLabel *results;
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

        results = new QLabel(QString::fromStdString(tmp));
        // results->setAlignment(Qt::AlignCenter);
        results->setMargin(10);
        results->show();
        layout->addWidget(results);

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
        map_res = Context::getInstance().getMapRes();
        std::string tmp = "<center><b>Résultats de l'encodage</b></center><br></br>";
        for (std::pair <char,std::string> p : map_res) {
            tmp += p.first;
            tmp += " : ";
            tmp += p.second;
            tmp += "<br></br>";
        }

        // On actualise l'affichage du texte 
        results->setText(QString::fromStdString(tmp));
    };

signals: 

};

#endif // DISPLAYRESULTS_H
