#include "Sommet.h"
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
    filsd = nullptr;
    filsg = nullptr;
};

/*on utilise l'opérateur '=' pour le constructeur par recopie*/
// Sommet::Sommet(Sommet& source)
// {
//     *this = source;
// };

// CONST PAR COPIE AVEC UN CONST
Sommet::Sommet(const Sommet& s) 
{
    filsg = nullptr;
    filsd = nullptr;
    if (s.filsd != nullptr) {
        // delete filsd;
        filsd = new Sommet(*s.filsd);
        // filsd = new Sommet (s.filsd->getLettre(), s.filsd->getFreq(), s.filsd->getTaille());
    }
    
    if (s.filsg != nullptr) {
        // delete filsg;
        filsg = new Sommet(*(s.filsg));
        // filsg = new Sommet (s.filsg->getLettre(), s.filsg->getFreq(), s.filsg->getTaille());
    }

    freq = s.freq;
    lettre = s.lettre;
    taille = s.taille;
};


/*L'opérateur '=' utilise les setteurs afin de reprendre et copier les données du sommet passé en param*/
void Sommet::operator=(Sommet& source)
{
    setLettre(source.getLettre());
    setFreq(source.getFreq());
    setTaille(source.getTaille());

    if(source.getFilsD() != NULL && filsd == NULL)
        filsd = new Sommet(source.getFilsD()->getLettre(), source.getFilsD()->getFreq());

    else if (source.getFilsD() != NULL && filsd != NULL)
    {
        setLettre(source.getFilsD()->getLettre());
        setFreq(source.getFilsD()->getFreq());
        setTaille(source.getFilsD()->getTaille());
    }

    if(source.getFilsG() != NULL && filsg == NULL)
        filsg = new Sommet(source.getFilsG()->getLettre(),source.getFilsG()->getFreq());

    else if (source.getFilsG() != NULL && filsg != NULL)
    {
        setLettre(source.getFilsG()->getLettre());
        setFreq(source.getFilsG()->getFreq());
        setTaille(source.getFilsG()->getTaille());
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
    sprintf(sommet, "(%c : %.1f)", lettre, freq);
    sommet[14] = '\0';
    return sommet;
}

/*Le destructeur ne fait rien car quand on crée un sommet seul ses fils sont initiés à NULL, et les autres attributs
sont déclarés de manière statique*/
Sommet::~Sommet()
{
    ;
};
