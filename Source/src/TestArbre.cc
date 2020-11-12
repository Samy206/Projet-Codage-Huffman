#include "../headers/ArbreB.h"
// #include "../headers/Affichage.h"

#include <unistd.h>
using namespace std;

int main()
{
    srand(getpid());
    const char cars[13] = {'a','b','c','d','e','f','j','h','i','g','k','l','m'};

    float numbers [13];
    Sommet table1 [13];

    for(int i = 0 ; i < 13 ; i++)
    {
        numbers[i] = rand() % 100; // Initialisation aléatoires des occurrences des lettres
        Sommet * random = new Sommet(cars[i],numbers[i]);
        table1[i] = *random;
        delete random;
    }

    cout << " > Test constructeur: Génération d'un arbre binaire avec fréquences aléatoires :\n+- Arbre1:" << endl;
    ArbreB arbre1(table1,13);
    cout << arbre1 << endl;
    /*for(int i = 0 ; i < 6 ; i++)
    {
        cout<<"Suppression de la lettre "<<cars[i]<<" -----------------------------------------------------\n\n";
        arbre1.supprimer_noeud(arbre1.getRacine(),cars[i]);
        cout<<arbre1;
    }*/


    ArbreB arbre2(arbre1);
    cout << " > Test constructeur par copie: Génération d'un arbre construit par copie :\n+- Arbre2:" << endl;
    cout << arbre2 << endl;

    cout << " > Test recherche: Recherche du noeud comportant le caractère 'j':" << endl;
    const char recherche = 'j';
    Noeud * res = arbre2.recherche_noeud(arbre2.getRacine(),recherche);

    if(res != NULL)
        cout<<"Noeud trouvé: (" << res->actuel.getLettre() << " : " << res->actuel.getFreq() << ")" << endl;
    else
        cout << "Aucun noeud ne comporte le caractère '" << recherche << "'" << endl;



    /*
    Noeud * table2 = new Noeud[13];
    for(int i = 0 ; i < 13 ; i++)
    {
        numbers[i] = rand() % 100;
        Sommet * random = new Sommet(cars[i],numbers[i]);
        table2[i].actuel = *random;
        table2[i].filsg = NULL;
        table2[i].filsd = NULL;
        delete random;
    }
    ArbreB arbre3(table2,13);


    cout<<"\nAffichage arbre3 , on l'initialise avec des variables de type Noeud\n\n"<<arbre3;
    arbre3.change_etiquette(cars[2],19);
    cout<<"\nChangement de la fréquence de c à 19\n\n"<<arbre3; */
}


