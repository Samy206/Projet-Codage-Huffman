#include "ArbreB.h"
using namespace std;

ArbreB::ArbreB(Sommet * sommets , int size)
{
    if(sommets != NULL)
    {
        taille = 0;
        for(int i = 0 ; i < size ; i++)
        {
            ajout(sommets[i]);
            cout<<"taille :"<< taille<< "\n";
        }

    }
    else
    {
        racine = NULL ;
        taille =  0 ;
    }
};

ArbreB::ArbreB(Noeud * noeuds, int size)
{
    if(noeuds != NULL)
    {
        taille = 0;
        for(int i = 0 ; i < size ; i++)
            ajout(&noeuds[i]);

    }

    else
    {
        racine = NULL ;
        taille =  0 ;
    }
};

void ArbreB::ajout(Sommet & sommet)
{
    Noeud * nouveau = new Noeud;
    nouveau->actuel = sommet;
    nouveau->filsg = NULL;
    nouveau->filsd = NULL;

    if(taille == 0)
        racine = nouveau;

    else if (taille == 1 )
        racine->filsg = nouveau;

    else if (taille == 2)
        racine->filsd = nouveau;

    else
    {
        Noeud * tmp = racine ;

        if(tmp->filsg != NULL)
        {
            while(tmp->filsd != NULL)
                tmp = tmp->filsd ;

            if(tmp->filsg != NULL)
                tmp->filsd = nouveau;

            else
                tmp->filsg = nouveau;
        }

        else
            tmp->filsg = nouveau;
    }
    taille++;
};

void ArbreB::ajout(Noeud * nouveau)
{
    if(taille == 0)
        racine = nouveau;

    else if (taille == 1 )
        racine->filsg = nouveau;

    else if (taille == 2)
        racine->filsd = nouveau;

    else
    {
        Noeud * tmp = racine ;

        if(tmp->filsg != NULL)
        {
            while(tmp->filsd != NULL)
                tmp = tmp->filsd ;

            if(tmp->filsg != NULL)
                tmp->filsd = nouveau;

            else
                tmp->filsg = nouveau;
        }

        else
            tmp->filsg = nouveau;
    }
    taille++;
};

void ArbreB::ajout(ArbreB& arbre)
{
    if(taille == 0)
        racine = arbre.getRacine();

    else if (taille == 1 )
        racine->filsg = arbre.getRacine();

    else if (taille == 2)
        racine->filsd = arbre.getRacine();

    else
    {
        Noeud * tmp = racine ;

        if(tmp->filsg != NULL)
        {
            while(tmp->filsd != NULL)
                tmp = tmp->filsd ;

            if(tmp->filsg != NULL)
                tmp->filsd = arbre.getRacine();

            else
                tmp->filsg = arbre.getRacine();
        }

        else
            tmp->filsg = arbre.getRacine();
    }
    taille+= arbre.getTaille();
};

friend std::ostream& operator<<(std::ostream&,ArbreB&)
{
    Noeud * tmp = racine;
    while
}


ArbreB::~ArbreB()
{
    ;
};