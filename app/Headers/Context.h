#pragma once

#include "ArbreB.h"
#include <unistd.h>
#include <QtCore/QObject>

/**
 * @brief Contexte principale de l'application
 * 
 */
class Context : public QObject {

    Q_OBJECT

private:
    ArbreB arbre[6];
    ArbreB *arbre_courant;

    Context() {
        const char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
        'w','x','y','z'};

        float numbers [26];

        /*Génération d'un arbre binaire avec fréquences aléatoires et affichage de ce dernier (ainsi que sa taille et
        sa hauteur*/

        for(int i = 0 ; i < 13 ; i++) {
            numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
            arbre[0].ajout(arbre[0].getRacine(),cars[i],numbers[i]);
        }
        
        /* Constructeur par copie */
        // arbre[1](arbre[0]);

        /* Décomposition */
        arbre[0].decomposition(arbre[1], arbre[2]);

        /* Fusion */
        arbre[4].fusion_arbre(arbre[1], arbre[2]);

        setArbre(0);
    }

public:

    /**
     * @brief Classe singleton: le constructeur est private, on un un getter d'instance à la place.
     * 
     * @return Context& 
     */
    static Context& getInstance()
    {
        static Context singleton;
        return singleton;
    }

    // Pour s'assurer que la classe reste en Singleton
    Context(Context const&) = delete;
    Context& operator=(Context const&) = delete;

    /**
     * @brief Setter pour l'arbre contexte
     *
     * @param e_arbre
     */
    void setArbre(int pos) {
        arbre_courant = &(arbre[pos]);
        emit arbreChanged();
    }


    /**
     * @brief Getter pour l'arbre contexte
     *
     * @return ArbreB
     */
    ArbreB* getArbre() { return arbre_courant; };


public slots:

    /**
     * @brief Re-génère un arbre binaire étiqueté aléatoire
     *
     */
    void genereArbre() {
        setArbre(0);
    }

    void decomposeGauche() {
        setArbre(1);
    }
    void decomposeDroite() {
        setArbre(2);
    }
    void fusion() {
        setArbre(4);
    }


signals:
    /**
     * @brief Emitted when the arbre changed
     *
     */
   void arbreChanged();
};