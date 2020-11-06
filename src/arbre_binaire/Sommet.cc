#include "Sommet.h"
#include <iostream>

Sommet::Sommet(const char car, const int part)
{
    lettre = car;
    freq = part;
};

Sommet::Sommet(Sommet& source)
{
    *this = source;
};

void Sommet::operator=(Sommet& source)
{
    lettre = source.getLettre();
    freq = source.getFreq();
};

Sommet operator+(Sommet& terme1, Sommet& terme2)
{
    Sommet nouveau;
    nouveau.setFreq ( terme1.getFreq() + terme2.getFreq() );
    return nouveau;
};

friend std::ostream& operator<<(std::ostream& flux,Sommet& sommet)
{
    flux<<"Ce sommet a pour lettre "<<sommet.lettre<<" ,qui apparaît "<<sommet.freq<<" dans le texte\n";
};

Sommet::~Sommet()
{
    delete this;
};