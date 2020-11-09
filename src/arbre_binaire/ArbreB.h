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
        ArbreB(Noeud * = NULL, int = 0);
        ArbreB(ArbreB&);

        Noeud * getRacine() {return racine;};
        int getTaille() {return taille;};

        void ajout(Noeud *,Sommet &);
        void ajout(Noeud *,Noeud *);
        void ajout(ArbreB&);
        Noeud * copie_noeuds(Noeud * source);
        void operator=(ArbreB&);
        void print_tree(Noeud *, int);
        void free_tree(Noeud *);
        Noeud * recherche_noeud(Noeud*,const char);
        void supprimer_noeud(const char);

        friend std::ostream& operator<<(std::ostream&,ArbreB&);
        void operator+=(ArbreB&);
        Noeud * supp_noeud(char);
        ~ArbreB();

};


#endif