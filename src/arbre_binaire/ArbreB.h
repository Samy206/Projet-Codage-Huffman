#ifndef ARBREB_H
#define ARBREB_H
#include "Sommet.h"
#include <iostream>

class Noeud : 
{
    public :
        Sommet actuel ;
    struct noeud * filsg;
    struct noeud * filsd;
};

class ArbreB : public Sommet
{
    private :
        Noeud * racine;
        int taille ;
    public :
        ArbreB(Sommet * , int);
        ArbreB(Noeud * = NULL, int = 0);
        ~ArbreB();

        Noeud * getRacine() {return racine;};
        int getTaille() {return taille;};

        void ajout(Sommet&);
        void ajout(Noeud*);
        void ajout(ArbreB&);

        friend std::ostream& operator<<(std::ostream&,ArbreB&);
        Noeud * supp_noeud(char);

};


#endif