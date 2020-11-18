#include "../headers/Sommet.h"
using namespace std;

Sommet::Sommet(const char car, const float part) //on assigne chaque attribut à une valeur
{
    lettre = car;
    freq = part;
    taille = 1;
    filsd = NULL;
    filsg = NULL;
};

Sommet::Sommet(Sommet& source) //on utilise l'opérateur = pour le constructeur par recopie
{
    *this = source;
};

void Sommet::operator=(Sommet& source) // on copie les champs un par un
{

        setLettre(source.getLettre());
        setFreq(source.getFreq());
};


//la somme de deux sommets nous donne un sommet sans lettre ( avec le caractère espace ) et la somme de leur fréquence
Sommet operator+(Sommet& terme1, Sommet& terme2)
{
    if ( (terme2.filsg == NULL && terme2.filsd == NULL) &&
         (terme1.filsg == NULL && terme1.filsd == NULL)
       )
    {
        Sommet nouveau;
        const char c = ' ';
        nouveau.setLettre(c);                                       //caractère vide assignée
        nouveau.setFreq ( terme1.getFreq() + terme2.getFreq() );    //somme des fréquences assignée
        return nouveau;
    }
    else
    cout<<"On ne peut pas additionner deux sommets s'ils ont des fils, car cela reviendrait  à additionner des arbres.\n";
};

std::ostream& operator<<(std::ostream& flux,Sommet& sommet) //affichage de la lettre et de sa fréquence
{
    flux<<"Ce sommet a pour lettre "<<sommet.lettre<<" ,qui apparaît "<<sommet.freq<<" fois dans le texte\n";
    return flux;
};

char* Sommet::formalize_sommet() {
    char* sommet = new char[10];
    sprintf(sommet, "(%c : %.0f)", lettre, freq);
    sommet[9] = '\0';
    return sommet;
}

Sommet::~Sommet()
{
    if(filsg != NULL)
        delete filsg;

    if(filsd != NULL)
        delete filsd;
};