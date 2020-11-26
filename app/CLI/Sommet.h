#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>


/**
 * Représente un sommet d'arbre binaire étiqueté par une Lettre, une Fréquence ainsi qu'un pointeur vers chacun de ses fils.
 * 
 * Attributs privés: 
 * @lettre      char        Lettre caractérisant le sommet
 * @freq        float       Fréquence d'occurence de cette lettre
 * @taille      int         1 <= nombre de sommets <= 3
 * @filsg       Sommet*     Pointeur vers le fils gauche du sommet
 * @filsd       Sommet*     Pointeur vers le fils gauche du sommet
 * 
 */
class Sommet
{
    private :
        char lettre;
        float freq;
        int taille;
        Sommet * filsg;
        Sommet * filsd;

    public :
         /** 
         * Constructeurs:
         * - Paramètres par défaut
         * - Constructeur vide déclaré implicitement
         * - Constructeur par copie
         */
        Sommet(const char =' ',const float = 0, const int = 0);
        Sommet(Sommet &);

        /**
         *  Destructeur de classe 
         * */
        ~Sommet();

        /**
         *  Getters des attributs privés (déclarés inline) pour assurer l'encapsulation 
         * */
        char getLettre() {return lettre;};
        float getFreq() {return freq;};
        Sommet * getFilsG() {return filsg;};
        Sommet * getFilsD() {return filsd;};
        int getTaille() {return taille;};

        /**
         *  Setters des attributs privés (déclarés inline) pour assurer l'encapsulation 
         * */
        void setLettre(const char car) {lettre = car;};
        void setFreq(const float part) {freq = part;};
        void setFilsG(Sommet * sommet) {filsg = sommet ; taille++;};
        void setFilsD(Sommet * sommet) {filsd = sommet ;taille++;};
        void setTaille(const int size) {taille = size;};

        /**
         *  Représente un sommet sous la forme d'une chaîne de caractère (char : freq) 
         * */
        char* formalize_sommet();
    
        /**
         *  Surcharge des opérateurs =, + et << 
         * */
        void operator=(Sommet &);
        friend Sommet operator+(Sommet & ,Sommet &);
        friend std::ostream& operator<<(std::ostream&,Sommet&);

        /**
         *  Classe ArbreB déclarée classe amie afin de pouvoir modifier les données de l'arbre de manière optimale 
         * */
        friend class ArbreB;
};


#endif