#include "../headers/ArbreB.h"

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
        numbers[i] = rand() % 100;
        Sommet * random = new Sommet(cars[i],numbers[i]);
        table1[i] = *random;
        delete random;
    }

    ArbreB arbre1(table1,13);
    cout <<arbre1<<"\n\n";
    /*for(int i = 0 ; i < 6 ; i++)
    {
        cout<<"Suppression de la lettre "<<cars[i]<<" -----------------------------------------------------\n\n";
        arbre1.supprimer_noeud(arbre1.getRacine(),cars[i]);
        cout<<arbre1;
    }*/

    ArbreB arbre2(arbre1);
    cout<<"affichage arbre 2 copie de arbre1 \n\n"<<arbre2;

    const char recherche = 'j';
    Noeud * res = arbre2.recherche_noeud(arbre2.getRacine(),recherche);

    if(res != NULL)
        cout<<"\n\nres : lettre-> '"<<res->actuel.getLettre()<<"' , frequence : "<<res->actuel.getFreq()<<endl;


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
    cout<<"\nChangement de la fréquence de c à 19\n\n"<<arbre3;
}


