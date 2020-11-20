#ifndef MAINMENU_H
#define MAINMENU_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QFrame>

/**
 * Menu de boutons pour la gestion du déroulement du programme.
 * 
 * @bSuivant    QPushButton*    Bouton pour passer à l'arbre suivant
 * @bQuitter    QPushButton*    Bouton permettant l'arrêt du programme
 * @layout      QHBoxLayout*    Layout en 'boîte' pour l'affichage des boutons
 */ 
class MainMenu : public QFrame {
private:
    QPushButton* bSuivant;
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
};


#endif // MAINMENU_H
