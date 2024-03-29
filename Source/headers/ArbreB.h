#ifndef ARBREB_H
#define ARBREB_H
#include "Sommet.h"

//La classe ArbreB a pour attribut privé un pointeur sur un sommet ( c'est la racine ) et à partir de celui ci on peut
//avoir accès à tout les autres de manière récursive, mais elle a aussi une taille correspondante au nombre de sommets.
//Les méthodes "complexes" seront détaillées dans le ".cc" .

//Ps : les accesseurs et les setteurs sont inline car ce sont des méthodes assez basiques

//Pour les méthodes simples on a :
    //les accesseurs : getRacine , getTaille et calcule_hauteur .
    //"getRacine" renvoie un pointeur car elle est utilisée dans les méthodes récursives
    //calcule_hauteur parcours l'arbre en cherchant la feuille la plus éloignée de la racine de maière récursive

    //on surcharge la méthode ajout afin d'ajouter un élément de plusieurs manières

    //on a deux constructeurs (plutôt trois si on compte le constructeur vide implicitement déclaré par le
        //constructeurs aux paramètres par défaut)

    //on redéfinit les opérateurs += , = et <<

class ArbreB
{
    private :
        Sommet * racine;
        int taille;
        int hauteur;
    public :
        ArbreB(Sommet * = NULL , int = 0);
        ArbreB(ArbreB&);
        ~ArbreB();

        Sommet * getRacine() {return racine;};
        int getTaille() {return taille;};
        int getHauteur() {return hauteur;};
        int calcule_hauteur(Sommet *);

        void ajout(Sommet *,Sommet* );
        void ajout(Sommet*,const char, const int);
        void ajout(ArbreB&);
        Sommet * copie_sommets(Sommet * source);
        void print_tree(Sommet *root, char *indent, int last);
        void free_tree(Sommet *);
        Sommet * recherche_sommet(Sommet*,const char);
        Sommet * recherche_sommet(Sommet*,const char ,const int);
        void fusion_arbre(ArbreB&, ArbreB&);
        void supprimer_sommet(Sommet *,const char);
        void change_etiquette(const char,const int);
        void decomposition(ArbreB&, ArbreB&);


        friend std::ostream& operator<<(std::ostream&,ArbreB&);
        void operator+=(ArbreB&);
        void operator=(ArbreB&);
};


#endif