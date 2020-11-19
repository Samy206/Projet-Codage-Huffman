#include "../headers/Sommet.h"
using namespace std;

/*Malgré la présence des attributs filsg et filsd dans la classe Sommet, dans les méthodes suivantes on part du
principe qu'on a affaire à des sommets sans fils car ces derniers feront l'objet d'intérêt de la classe ArbreB*/


/*Quand on créer un sommet on ne lui donne qu'un caractère et qu'une occurence, ses fils seront ajoutés lors de la
créations de l'arbre*/
Sommet::Sommet(const char car, const float part,const int size)
{
    lettre = car;
    freq = part;
    taille = size;
    filsd = NULL;
    filsg = NULL;
};

/*on utilise l'opérateur '=' pour le constructeur par recopie*/
Sommet::Sommet(Sommet& source)
{
    *this = source;
};

/*L'opérateur '=' utilise les setteurs afin de reprendre et copier les données du sommet passé en param*/
void Sommet::operator=(Sommet& source)
{
    setLettre(source.getLettre());
    setFreq(source.getFreq());
};


/*la somme de deux sommets nous donne un sommet sans lettre ( avec le caractère espace ) et la somme de leur
fréquence*/
Sommet operator+(Sommet& terme1, Sommet& terme2)
{
   Sommet nouveau;
   nouveau.setLettre(' ');                                       //caractère vide assignée
   nouveau.setFreq ( terme1.getFreq() + terme2.getFreq() );    //somme des fréquences assignée
   return nouveau;
};

/*ici on affiche un sommet de façon textuelle (utilisée pour avoir les informations d'un sommet seul)*/
std::ostream& operator<<(std::ostream& flux,Sommet& sommet) //affichage de la lettre et de sa fréquence
{
    flux<<"Ce sommet a pour lettre "<<sommet.lettre<<" ,qui apparaît "<<sommet.freq<<" fois dans le texte\n";
    return flux;
};

/*ici on affiche un sommet de façon plus 'mathématique', c-a-d qu'il est sous forme de couple de valeurs (utilisé
dans l'affichage d'un arbre)*/
char* Sommet::formalize_sommet() {
    char* sommet = new char[10];
    sprintf(sommet, "(%c : %.0f)", lettre, freq);
    sommet[9] = '\0';
    return sommet;
}

/*Le destructeur ne fait rien car quand on crée un sommet seul ses fils sont initiés à NULL, et les autres attributs
sont déclarés de manière statique*/
Sommet::~Sommet()
{
    ;
};