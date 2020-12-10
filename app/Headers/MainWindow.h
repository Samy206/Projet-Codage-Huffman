#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GetUserText.h"
#include "DisplayResults.h"
#include "DessineArbre.h"

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>


/**
 * @brief Fenêtre principale du programme graphique, composé d'une bannière, d'un menu et d'une zone de dessin.
 * 
 * @wMenu       MainMenu*       Menu de boutons pour le déroulement du programme
 * @layout      QGridLayout*    Layout en grille pour le programme graphique
 * @wZoneArbre  QScrollArea*    Zone à barre de défilement pour l'affichage du dessin
 * @dessin      DessineArbre*   Dessin de l'arbre binaire
 */ 
class MainWindow : public QWidget {
private :
    GetUserText* wInput;
    QGridLayout* layout; // Grid Layout pour l'affichage

    DisplayResults* resultats;
    QScrollArea* wZoneResultats;

    DessineArbre* dessin;
    QScrollArea* wZoneArbre;

public :
    /**
     * Constructeur par défaut
     */ 
    MainWindow();
    
    /**
     * Destructeur de classe
     */ 
    ~MainWindow();
};

#endif // MAINWINDOW_H
