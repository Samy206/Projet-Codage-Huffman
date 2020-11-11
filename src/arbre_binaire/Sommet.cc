#include "Sommet.h"


Sommet::Sommet(const char car, const float part) //on assigne chaque attribut à une valeur
{
    lettre = car;
    freq = part;
};

Sommet::Sommet(Sommet& source) //on utilise l'opérateur = pour le constructeur par recopie
{
    *this = source;
};

void Sommet::operator=(Sommet& source) // on copie les champs un par un
{
    lettre = source.getLettre();
    freq = source.getFreq();
};


//la somme de deux sommets nous donne un sommet sans lettre ( avec le caractère espace ) et la somme de leur fréquence
Sommet operator+(Sommet& terme1, Sommet& terme2)
{
    Sommet nouveau;
    const char c = ' ';
    nouveau.setLettre(c);                                       //caractère vide assignée
    nouveau.setFreq ( terme1.getFreq() + terme2.getFreq() );    //somme des fréquences assignée
    return nouveau;
};

std::ostream& operator<<(std::ostream& flux,Sommet& sommet) //affichage de la lettre et de sa fréquence
{
    flux<<"Ce sommet a pour lettre "<<sommet.lettre<<" ,qui apparaît "<<sommet.freq<<" fois dans le texte\n";
    return flux;
};

Sommet::~Sommet()
{
    ;
};