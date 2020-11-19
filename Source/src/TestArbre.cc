#include "../headers/ArbreB.h"

#include <unistd.h>
using namespace std;

int main()
{
/*------------------------------------------------------------------------------------------------------------------
    Initialisation des tableaux utiles à la création des arbres
-------------------------------------------------------------------------------------------------------------------*/
    srand(getpid());
    const char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z'};

    float numbers [26];
    Sommet  table1 [26];
    for(int i = 0 ; i < 26 ; i++)
    {
        numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
        Sommet * random = new Sommet(cars[i],numbers[i],1);
        table1[i] = *random;
        delete random;
    }
/*------------------------------------------------------------------------------------------------------------------
    Création des arbres et test des méthodes implémentées
-----------------------------------------------------------------------------------------------------------------*/

    /*Génération d'un arbre binaire avec fréquences aléatoires et affichage de ce dernier (ainsi que sa taille et
    sa hauteur*/
    ArbreB *arbre1 =  new ArbreB(table1,26);
    cout << ">Test constructeur: Génération d'un arbre binaire avec fréquences aléatoires :\n+- Arbre1:" << endl;
    cout <<*arbre1 << endl;
    cout<<"  L'Arbre1 a une hauteur de valeur égale à "<< arbre1->getHauteur()<<" et comporte "
    <<arbre1->getTaille()<< " noeuds.\n\n";

    /*Test constructeur par copie: Génération d'un arbre construit par copie, et même affichage que le précédent*/
    ArbreB arbre2(*arbre1);
    cout << ">Test constructeur par copie: Génération d'un arbre construit par copie :\n+- Arbre2:" << endl;
    cout <<arbre2 << endl;
    cout<<"  l'Arbre2 a donc les mêmes caracteristiques que l'Arbre1.\n\n";

    /*Test de recherche d'un sommet dans un arbre*/
    cout << ">Test recherche: Recherche du sommet comportant le caractère 'j':" << endl;
    const char recherche = 'j';
    Sommet * res = arbre2.recherche_sommet(arbre2.getRacine(),recherche);

    if(res != NULL)
        cout<< "    Sommet trouvé: " << res->formalize_sommet()<< "\n";
    else
        cout << "   Aucun sommet ne comporte le caractère '" << recherche << "'\n";

    res = arbre2.recherche_sommet(arbre2.getRacine(),cars[5],numbers[5]);

     if(res != NULL)
         cout<< "    Sommet trouvé: " << res->formalize_sommet()<< "\n\n";
     else
         cout << "   Aucun sommet ne comporte le caractère '" << recherche << "'\n\n" << endl;


    /*Test de la décomposition d'un arbre en deux sous-arbre et affichage de ces derniers*/
    ArbreB arbre3, arbre4;
    cout<<">Test décomposition de l'Arbre2 :\n\n";
    arbre2.decomposition(arbre3,arbre4);
    if(arbre3.getRacine() != NULL)
        cout<<"     Affichage de l'Arbre3 (sous-arbre gauche) : \n\n"<<arbre3<<"\n\n";
    else
        cout<<"     Arbre3 (sous-arbre gauche) : inexistant dans l'Arbre2\n\n";

    if(arbre4.getRacine() != NULL)
        cout<<"     Affichage de l'Arbre4 (sous-arbre droit) : \n\n"<<arbre4<<"\n\n";
    else
        cout<<"     Arbre4 (sous-arbre gauche) : inexistant dans l'Arbre2\n\n";

    /*Test de la fusion des arbres 3 et 4, et affichage du résultat*/
    ArbreB arbre5;
    arbre5.fusion_arbre(arbre3,arbre4);
    cout<<"Affichage de l'Arbre5 ( fusion des deux arbres précédents ) : \n\n"<<arbre5<<endl<<endl;

/*------------------------------------------------------------------------------------------------------------------
    FIN
-----------------------------------------------------------------------------------------------------------------*/
}


