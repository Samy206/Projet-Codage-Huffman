#ifndef ARBREB_H
#define ARBREB_H
#include "Sommet.h"


//Le type noeud nous permet de ne pas trop surcharger les attributs de la classe ArbreB

typedef struct noeud
{
    Sommet actuel ;
    struct noeud * filsg;
    struct noeud * filsd;
}Noeud;

//La classe ArbreB a pour attribut privé un pointeur sur un noeud ( c'est la racine ) et à partir de celui ci on peut
//avoir accès à tout les autres noeuds de manière récursive, ainsi qu'une taille correspondant au nombre de noeuds.
//Les méthodes "complexes" seront détaillées dans le ".cc" .

//Ps : les accesseurs et les setteurs sont inline car ce sont des méthodes assez basiques

//Pour les méthodes simples on a :
    //les accesseurs : getRacine et getTaille . "getRacine" renvoie un pointeur car elle est utilisée dans les méthodes
        //récursives

    //on surcharge la méthode ajout afin d'ajouter un élément de plusieurs manières

    //on a trois constructeurs (plutôt quatre si on compte le constructeur vide implicitement déclaré par le
        //constructeurs aux paramètres par défaut

    //on redéfinit les opérateurs += , = et <<

class ArbreB : public Sommet
{
    private :
        Noeud * racine;
        int taille ;

    public :
        ArbreB(Sommet * , int);
        ArbreB(Noeud * = NULL, int = 0);
        ArbreB(ArbreB&);
        ~ArbreB();

        Noeud * getRacine() {return racine;};
        int getTaille() {return taille;};

        void ajout(Noeud *,Sommet &);
        void ajout(Noeud *,Noeud *);
        void ajout(ArbreB&);
        Noeud * copie_noeuds(Noeud * source);
        void print_tree(Noeud *, int);
        void free_tree(Noeud *);
        Noeud * recherche_noeud(Noeud*,const char);
        void supprimer_noeud(Noeud *,const char);
        void change_etiquette(const char,const int);

        friend std::ostream& operator<<(std::ostream&,ArbreB&);
        void operator+=(ArbreB&);
        void operator=(ArbreB&);


};


#endif