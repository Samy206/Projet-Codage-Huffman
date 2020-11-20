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
    ArbreB arbre_t[2];
    ArbreB* arbre; 

    Context() {
        const char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
        'w','x','y','z'};

        float numbers [26];
        Sommet  table1 [26];
        for(int i = 0 ; i < 26 ; i++) {
            numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
            Sommet * random = new Sommet(cars[i],numbers[i],1);
            table1[i] = *random;
            delete random;
        }

        /*Génération d'un arbre binaire avec fréquences aléatoires et affichage de ce dernier (ainsi que sa taille et
        sa hauteur*/
        
        arbre =  new ArbreB(table1, 26);
        arbre_t[0] = *arbre;

        // remplir la table
        // Boutons lier à des sets d'autres elems de la tables
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
    void setArbre(ArbreB& e_arbre) {
        // *arbre = e_arbre;
        // emit arbreChanged();
    }



    /**
     * @brief Getter pour l'arbre contexte
     *
     * @return ArbreB
     */
    ArbreB& getArbre() { return *arbre; };


public slots:

    /**
     * @brief Re-génère un arbre binaire étiqueté aléatoire
     *
     */
    void genereArbre() {   
        const char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
        'w','x','y','z'};

        float numbers [26];
        Sommet  table1 [26];
        for(int i = 0 ; i < 13 ; i++)
        {
            numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
            Sommet * random = new Sommet(cars[i],numbers[i],1);
            table1[i] = *random;
            delete random;
        }

        /*Génération d'un arbre binaire avec fréquences aléatoires et affichage de ce dernier (ainsi que sa taille et
        sa hauteur*/
        delete arbre;

        
        arbre =  new ArbreB(table1, 13);
        emit arbreChanged();
    }




signals:
    /**
     * @brief Emitted when the arbre changed
     *
     */
   void arbreChanged();
};