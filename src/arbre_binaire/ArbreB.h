#ifndef ARBREB_H
#define ARBREB_H
#include "Sommet.h"
#include <iostream>

typedef struct noeud
{
    Sommet actuel ;
    struct noeud * filsg;
    struct noeud * filsd;
}Noeud;

class ArbreB : public Sommet
{
    private :
        Noeud * racine;
        int taille ;
    public :
        ArbreB(Sommet * , int);
        //ArbreB(Noeud * = NULL, int = 0);


        Noeud * getRacine() {return racine;};
        int getTaille() {return taille;};

        void ajout(Noeud *,Sommet &);

        void print_tree(Noeud *, int);
        void free_tree(Noeud *);

        Noeud * supp_noeud(char);
        ~ArbreB();

};


#endif