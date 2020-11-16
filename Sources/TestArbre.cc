#include "ArbreB.h"
// #include "Affichage.h"
#include "MainWindow.h"

#include <unistd.h>
#include <QApplication>
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

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


    ArbreB arbre2(arbre1);
    cout << " > Test constructeur par copie: Génération d'un arbre construit par copie :\n+- Arbre2:" << endl;
    cout << arbre2 << endl;

    MainWindow aff(arbre2);
    aff.show();

    cout << " > Test recherche: Recherche du noeud comportant le caractère 'j':" << endl;
    const char recherche = 'j';
    Noeud * res = arbre2.recherche_noeud(arbre2.getRacine(),recherche);

    if(res != NULL)
        cout<<"Noeud trouvé: (" << res->actuel.getLettre() << " : " << res->actuel.getFreq() << ")" << endl;
    else
        cout << "Aucun noeud ne comporte le caractère '" << recherche << "'" << endl;


    return app.exec();

}


