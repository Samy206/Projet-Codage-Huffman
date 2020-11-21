#include "Lecteur.h"
using namespace std;

Lecteur::Lecteur()
{
    for(int i = 0 ; i < 26 ; i++)
    {
        occurences.push_back(0.0);
    }
    char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
    'w','x','y','z'};
    lettres.insert(lettres.end(),cars,cars+26);
};

Lecteur::Lecteur(Lecteur& autre)
{
    *this = autre;
    char cars[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
        'w','x','y','z'};
    lettres.insert(lettres.end(),cars,cars+26);
};

void Lecteur::operator=(Lecteur& donneur)
{
    vector<float>  tmp2 (donneur.getOccurences());

    occurences = tmp2;


    contenu = donneur.getContenu();
};


void Lecteur::lecture(ifstream& myfile)
{
    std::stringstream strStream;
    if(myfile.is_open() )
    {
        strStream << myfile.rdbuf(); //read the file
        contenu = strStream.str(); //str holds the content of the file
    }
    myfile.close();

    int size = contenu.size();
    if(size != 0)
    {
        int compteur = 0 ;
        int ascii = -1;

        for(int i = 0 ; i < size ; i++)
        {
            ascii = -1;
            ascii = int(contenu[i]);

            if(ascii >= 65 && ascii <= 90)
            {
                compteur++;
                occurences[ascii-65] ++;
            }
            else if(ascii >= 97 && ascii <= 122)
            {
                compteur++;
                occurences[ascii-97] = occurences[ascii-97] +1  ;

            }
            else
                continue;

        }
        cout<<compteur<<" wsh, size : "<<size<<"\n";
        cout<<contenu<<endl;
        for(int i = 0 ; i < compteur ; i++)
        {
            occurences[i] /= compteur;
        }
    }

}

ostream& operator<<(ostream& flux,Lecteur& lecteur)
{
    flux<<"Lecteur : { ";
    int i = 0;
    for(i = 0 ; i < 26 ; i++)
    {
        if(lecteur.occurences[i] != 0.0)
        {
            if(i != 25 )
                flux<< "( " <<lecteur.lettres[i] <<" ; "<<lecteur.occurences[i]<<" ) |";
            else
                flux<< "( " <<lecteur.lettres[i] <<" ; "<<lecteur.occurences[i]<<" ) }"<<endl;
        }

    }
    return flux;
};

Lecteur::~Lecteur()
{
;
};