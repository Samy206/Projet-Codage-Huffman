#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>


//class Sommet :
    //1) On met les attributs en private afin de les protéger, mais on définit quand même la classe ArbreB comme
        //étant une classe amie afin de pouvoir modifier les données de l'arbre de manière optimale
    //2) Le premier constructeur initie des valeurs par défaut afin de ne pas avoir à créer un autre constructeur
           //sans paramètres
    //3) Il y aussi le constructeur par recopie qui est implémenté
    //4) On déclare aussi des accesseurs et des méthodes pour modifier les attributs de manière à respecter
        //l'encapsulation
    //5) On redéfinit les opérateurs +, = et <<

    //Ps : les accesseurs et les setteurs sont inline car ce sont des méthodes assez basiques
class Sommet
{
    private :
        //Attributs : {lettre,freq} = données ; taille = (1 <= nbr de sommets <= 3)  ; {filsg,filsd} = utilisé
                                                                                        //dans la classe ArbreB
        char lettre;
        float freq;
        int taille;
        Sommet * filsg;
        Sommet * filsd;

    public :

        Sommet(const char =' ',const float = 0);
        Sommet(Sommet &);
        ~Sommet();

        char getLettre() {return lettre;};
        float getFreq() {return freq;};
        Sommet * getFilsG() {return filsg;};
        Sommet * getFilsD() {return filsd;};
        int getTaille() {return taille;};
        void setLettre(const char car) {lettre = car;};
        void setFreq(const float part) {freq = part;};
        void setFilsG(Sommet * sommet) {filsg = sommet ;};
        void setFilsD(Sommet * sommet) {filsd = sommet ;};
        void setTaille(const int size) {taille = size;};

        void operator=(Sommet &);
        friend Sommet operator+(Sommet & ,Sommet &);
        friend std::ostream& operator<<(std::ostream&,Sommet&);
        friend class ArbreB;
        char* formalize_sommet();
};


#endif