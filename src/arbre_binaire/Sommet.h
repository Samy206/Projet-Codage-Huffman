#ifndef SOMMET_H
#define SOMMET_H

#include <iostream>

/*
 * Classe Sommet :
 *    Les attributs sont marqués `protected` pour que la Class fille ArbreB puisse avoir accès à ces derniers
 *          @lettre    représente un caractère du texte à analyser
 *          @freq      représente la fréquence d'occurrence de ce caractère
 *    Constructeurs:
 *          1. Constructeur par défaut avec valeurs initialisés si aucun paramètres
 *          2. Constructeur par copie
 *    Accesseurs (Getters) et modificateurs (Setters) implémentés pour le respect de l'encapsulation
 *    Surcharges des opérateurs +, = et <<
 */
 
class Sommet {
    protected :
        char lettre;
        float freq;

    public:
        Sommet(const char =' ',const float = 0);
        Sommet(Sommet &);
        ~Sommet();

        char  getLettre()              { return lettre; };
        float getFreq()                { return freq;   };
        void setLettre(const char car) { lettre = car;  };
        void setFreq(const float part) { freq   = part; };

        void operator=(Sommet &);
        friend Sommet operator+(Sommet & ,Sommet &);
        friend std::ostream& operator<<(std::ostream&,Sommet&);
};


#endif