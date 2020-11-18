#include "../headers/ArbreB.h"

#include <unistd.h>
using namespace std;

int main()
{
    srand(getpid());
    const char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z'};

    float numbers [26];
    Sommet table1 [26];

    for(int i = 0 ; i < 26 ; i++) {
        numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
        Sommet * random = new Sommet(cars[i], numbers[i]);
        table1[i] = *random;
        delete random;
    }

    ArbreB *arbre1 =  new ArbreB(table1, 26);


    cout << " > Test constructeur: Génération d'un arbre binaire avec fréquences aléatoires :\n+- Arbre1:" << endl;

    cout << *arbre1 << endl;

    cout<<"L'Arbre1 a une hauteur de valeur égale à "<< arbre1->getHauteur() <<" et comporte "
    << arbre1->getTaille()<< " nœuds.\n\n";

    // arbre1->free_tree(arbre1->getRacine());



    ArbreB arbre2(*arbre1);
    cout << " > Test constructeur par copie: Génération d'un arbre construit par copie :\n+- Arbre2:" << endl;
    cout << arbre2 << endl;
    cout<<"l'Arbre2 a donc les mêmes caracteristiques que l'Arbre1.\n\n";

    cout << " > Test recherche: Recherche du noeud comportant le caractère 'j':" << endl;
    const char recherche = 'j';
    Sommet * res = arbre2.recherche_sommet(arbre2.getRacine(),recherche);


    if(res != NULL)
        cout<< "Noeud trouvé: " << res->formalize_sommet()<< endl;
    else
        cout << "Aucun noeud ne comporte le caractère '" << recherche << "'\n" << endl;

    ArbreB arbre3, arbre4;
    cout<< "Décomposition de l'Arbre2 :\n\n";
    arbre2.decomposition(arbre3,arbre4);
    if(arbre3.getRacine() != NULL)
        cout<<"Affichage de l'Arbre3 (sous-arbre gauche) : \n\n"<<arbre3<<"\n\n";
    else
        cout<<"Arbre3 (sous-arbre gauche) : inexistant dans l'Arbre2\n\n";

    if(arbre4.getRacine() != NULL)
        cout<<"Affichage de l'Arbre4 (sous-arbre droit) : \n\n"<<arbre4<<"\n\n";
    else
        cout<<"Arbre4 (sous-arbre gauche) : inexistant dans l'Arbre2\n\n";

}


