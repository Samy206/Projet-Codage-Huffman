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
    ArbreB arbre[3];
    ArbreB *arbre_courant;

    Context() {
        const char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
        'w','x','y','z'};

        float numbers [26];

        /*Génération d'un arbre binaire avec fréquences aléatoires et affichage de ce dernier (ainsi que sa taille et
        sa hauteur*/

        for(int i = 0 ; i < 26 ; i++) {
            numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
            arbre[0].ajout(arbre[0].getRacine(),cars[i],numbers[i]);
        }
        
        /* Constructeur par copie */
        // arbre[1](arbre[0]);

        /* Décomposition */
        arbre[0].decomposition(arbre[1], arbre[2]);
        // std::cout << arbre[1] << std::endl;

        // remplir la table
        // Boutons lier à des sets d'autres elems de la tables
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
        
        std::cout << "SetArbre: Le nouvel arbre est chargé, j'envoie le signal ArbreChanged !" << std::endl;
        if (arbre_courant == NULL) 
             std::cout << "SetArbre: Pas bien chargé.." << std::endl;
        emit arbreChanged();
    }



    /**
     * @brief Getter pour l'arbre contexte
     *
     * @return ArbreB
     */
    ArbreB* getArbre() { 
        std::cout << "GetArbre: Okep, je te renvoie l'arbre qu'il te faut !" << std::endl;
        if (arbre_courant == NULL) 
             std::cout << "GetArbre: Mais.." << std::endl;

        return arbre_courant;
    };


public slots:

    /**
     * @brief Re-génère un arbre binaire étiqueté aléatoire
     *
     */
    void genereArbre() {   
        const char cars[10] = {'a','b','c','d','e','f','g','h','i','j' };
        float numbers [10];

        /*Génération d'un arbre binaire avec fréquences aléatoires et affichage de ce dernier (ainsi que sa taille et
        sa hauteur*/

        for(int i = 0 ; i < 10 ; i++) {
            numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
            arbre[0].ajout(arbre[0].getRacine(),cars[i],numbers[i]);
        }

        setArbre(0);
    }

    void decomposeGauche() {
        std::cout << "Bouton: Hello, je set l'abre dont VOUS avez besoin !" << std::endl;
        setArbre(1);
    }
    void decomposeDroite() {
        setArbre(2);
    }


signals:
    /**
     * @brief Emitted when the arbre changed
     *
     */
   void arbreChanged();
};