#include "ArbreB.cc"
#include "Sommet.cc"
using namespace std;

int main()
{
    srand(4);
    const char cars[26] = {'a','b','c','d','e','f','j','h','i','g','k','l','m','n','o','p','q','r','s','t','u',
        'v','w','x','y','z'};

    int numbers [26];
    Sommet table1 [26];

    for(int i = 0 ; i < 26 ; i++)
    {
        numbers[i] = rand() % 100;
        Sommet * random = new Sommet(cars[i],numbers[i]);
        table1[i] = *random;
        delete random;
    }



    ArbreB arbre1(table1,26);
    cout <<arbre1<<"\n\n";
    const char c = 'h';
    arbre1.supprimer_noeud(c);

    cout<<"\n\n"<<arbre1;

}


