#ifndef MAINMENU_H
#define MAINMENU_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QFrame>
#include <QLineEdit>
#include "Context.h"

/**
 * Menu de boutons pour la gestion du déroulement du programme.
 * 
 * @bSuivant    QPushButton*    Bouton pour passer à l'arbre suivant
 * @bQuitter    QPushButton*    Bouton permettant l'arrêt du programme
 * @layout      QHBoxLayout*    Layout en 'boîte' pour l'affichage des boutons
 */ 
class MainMenu : public QFrame {
    // Q_OBJECT
private:
    QLineEdit *input_txt;


    QPushButton* bGenerer;
    QPushButton* bDecomposeGauche;
    QPushButton* bDecomposeDroite;
    QPushButton* bFusion;

    QPushButton* bValider;
    QPushButton* bQuitter;
    QHBoxLayout* layout; // Box Layout pour le menu

public:
    /**
     * Constructeur par défaut
     */ 
    MainMenu();

    /**
     * Destructeur de classe
     */ 
    ~MainMenu();

// public slots:
//     void textEntered();

// signals:

};


#endif // MAINMENU_H
