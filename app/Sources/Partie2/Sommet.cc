#include "../../Headers/Partie2/Sommet.h"
using namespace std;


/**
   *Quand on créer un sommet on ne lui donne qu'un caractère et une occurence, ses fils seront ajoutés lors de la
    création de l'arbre
*/
Sommet::Sommet(char car, float part,int size)
{
    filsd = NULL;
    filsg = NULL;
    lettre = car;
    freq = part;
    taille = size;
};

/**
    *CONST PAR COPIE AVEC UN CONST :
        on copie les données (lettre , fréquence et taille) , et si le sommet à copier comporte des fils on rappelle
        le constructeur par copie de manière récursive
*/
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


/**
   *L'opérateur '=' copie les données du sommet passé en paramètre et gère ses fils de la même manière (récursive) que
    le constructeur par copie. La seule différence est qu'on a peut-être à faire avec un sommet qui a déjà ses
    propres fils, et dans ce cas on appelle la méthode clean_sommet() sur eux afin de libérer leur mémoire avant
    de les remplacer ou juste de les supprimer si le sommet à copier n'a pas de fils lui-même.
*/
void Sommet::operator=(const Sommet& source)
{
    lettre = source.lettre;
    freq = source.freq;
    taille = source.taille;
    if(source.filsd != NULL )
    {
        if(filsd != NULL) filsd->clean_sommet();
        filsd = new Sommet;
        *filsd = (*source.filsd);
    }
    if(source.filsg != NULL )
    {
        if(filsg != NULL) filsg->clean_sommet();
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


/**
   *La somme de deux sommets nous donne un sommet sans lettre ( avec le caractère espace ) et la somme de leur
    fréquence
*/
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

/**
    *ici on affiche un sommet de façon textuelle (utilisée pour avoir les informations d'un sommet seul)
*/
std::ostream& operator<<(std::ostream& flux,Sommet& sommet) //affichage de la lettre et de sa fréquence
{
    flux<<"Ce sommet a pour lettre "<<sommet.lettre<<" ,qui apparaît "<<sommet.freq<<" fois dans le texte\n";
    return flux;
};

/**
   *Ici on affiche un sommet de façon plus 'mathématique', c-a-d qu'il est sous forme de couple de valeurs (utilisé
    dans l'affichage d'un arbre)
*/
char* Sommet::formalize_sommet() {
    char* sommet = new char[15];
    sprintf(sommet, "(%c : %.1f)", lettre, freq);
    sommet[14] = '\0';
    return sommet;
}

/**
   *Cette méthode libère la mémoire d'un sommet (et de ses fils potentiels)  avant qu'on copie d'autres données dans ce
    dernier, et on adopte la récursion comme pour les arbres
*/
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


/**
   *Le destructeur ne fait rien car la responsabilité de la destruction des sommets revient à l'arbre
*/
Sommet::~Sommet()
{
    ;
};