#include "Sommet.h"
using namespace std;

/*Malgré la présence des attributs filsg et filsd dans la classe Sommet, dans les méthodes suivantes on part du
principe qu'on a affaire à des sommets sans fils car ces derniers feront l'objet d'intérêt de la classe ArbreB*/


/*Quand on créer un sommet on ne lui donne qu'un caractère et qu'une occurence, ses fils seront ajoutés lors de la
créations de l'arbre*/
Sommet::Sommet(char car, int part,int size)
{
    filsd = NULL;
    filsg = NULL;
    lettre = car;
    freq = part;
    taille = size;
};

/*on utilise l'opérateur '=' pour le constructeur par recopie*/
// Sommet::Sommet(Sommet& source)
// {
//     *this = source;
// };

// CONST PAR COPIE AVEC UN CONST
Sommet::Sommet(const Sommet& s) 
{
    filsg = NULL;
    filsd = NULL;
    freq = s.freq;
    lettre = s.lettre;
    taille = s.taille;

    if (s.filsd != NULL) {
        filsd = new Sommet(*s.filsd);
    }

    if (s.filsg != NULL) {
        filsg = new Sommet(*s.filsg);
    }
};


/*L'opérateur '=' utilise les setteurs afin de reprendre et copier les données du sommet passé en param*/
void Sommet::operator=(const Sommet& source)
{
    lettre = source.lettre;
    freq = source.freq;
    taille = source.taille;
    if(source.filsd != NULL )
    {
        if(filsd != NULL) delete filsd;
        filsd = new Sommet;
        *filsd = (*source.filsd);
    }
    if(source.filsg != NULL )
    {
        if(filsg != NULL) delete filsg;
        filsg = new Sommet;
        *filsg = (*source.filsg);
    }
    if(source.filsg == NULL && source.filsd == NULL)
    {
        if(filsg != NULL) filsg->clean_sommet();
        if(filsd != NULL) filsd->clean_sommet();
        filsg = NULL;
        filsd = NULL;
    }

};


/*la somme de deux sommets nous donne un sommet sans lettre ( avec le caractère espace ) et la somme de leur
fréquence*/
Sommet operator+(Sommet& terme1, Sommet& terme2)
{
   Sommet nouveau;
   nouveau.setLettre(' ');                                       //caractère vide assignée
   nouveau.setFreq ( terme1.getFreq() + terme2.getFreq() );    //somme des fréquences assignée
   nouveau.filsg = &terme1;
   nouveau.filsd = &terme2;
   nouveau.setTaille(3);

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
    char* sommet = new char[15];
    sprintf(sommet, "(%c : %d)", lettre, freq);
    sommet[14] = '\0';
    return sommet;
}

/*Cette méthode libère la mémoire d'un sommet (et de ses fils potentiels)  avant qu'on copie d'autres données dans ce
dernier, et on adopte la récursion comme pour les arbres*/
void Sommet::clean_sommet()
{
    Sommet * tmp1 = filsg;
    Sommet * tmp2 = filsd;

    if(tmp2 != NULL)
        tmp2->clean_sommet();

    if(tmp1 != NULL)
        tmp1->clean_sommet();

    delete this;
}


/*Le destructeur ne fait rien car quand on crée un sommet seul ses fils sont initiés à NULL, et les autres attributs
sont déclarés de manière statique*/
Sommet::~Sommet()
{
    ;
};