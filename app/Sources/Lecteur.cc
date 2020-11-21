#include "Lecteur.h"


Lecteur::Lecteur(int size)
{
    taille = size;
    lettres = new char [taille];
    occurences = new double[taille];
};

Lecteur::Lecteur(Lecteur& autre)
{
    *this = autre;
};

void operator=(lecteur& receveur ,Lecteur& donneur)
{
    receveur.taille = donneur.taille;
    receveur.lettres = new char [receveur.taille];
    receveur.occurences = new char [receveur.occurences];
    for(int i = 0 ; i < receveur.taille ; i++)
    {
        receveur.lettres[i] = donneur.lettres[i];
        receveur.occurences = donneur.occurences[i];
    }

    receveur.contenu = donneur.contenu;
};


Lecteur::~Lecteur()
{
    delete lettres;
    delete occurences;
};