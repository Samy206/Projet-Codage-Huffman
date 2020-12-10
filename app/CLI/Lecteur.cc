#include "Lecteur.h"
using namespace std;

Lecteur::Lecteur()
{
    ;
};

Lecteur::Lecteur(Lecteur& autre)
{
    *this = autre;
};

void Lecteur::operator=(Lecteur& donneur)
{
    occurences = donneur.getOccurences();
    contenu = donneur.getContenu();
    lettres = donneur.getLettres();
};


int Lecteur::get_indice(const char c)
{
    int taille = lettres.size();
    for(int i = 0; i < taille ; i++)
    {
        if(c == lettres[i])
            return i;
    }

    return -1;
}

void Lecteur::lecture(ifstream& myfile)
{
    std::stringstream strStream;
    if(myfile.is_open() )
    {
        strStream << myfile.rdbuf(); //read the file
        contenu = strStream.str(); //str holds the content of the file
    }
    myfile.close();
    lecture(contenu);
}

void Lecteur::lecture(string const& chaine)
{
    contenu = chaine;
    int size = contenu.size();
    if(size != 0)
    {
        int indice = -1 ;
        int ascii = -1;
        char convert;
        for(int i = 0 ; i < size ; i++)
        {
            if(contenu[i] != ' ' && contenu[i] != ';' && contenu[i] != ',' && contenu[i] != '.')
            {
                ascii= (int) (contenu[i]);
                if(ascii >= 0 && ascii <= 255)

                {
                    convert = contenu[i];

                    if(ascii >= 65 && ascii <= 90)
                        convert = (char) (ascii+32);

                    indice = get_indice(convert);
                    if(indice == -1)
                    {
                        lettres.push_back(convert);
                        occurences.push_back(1);
                    }
                    else
                        occurences[indice] += 1;
                }
            }
        }
    }
}

ostream& operator<<(ostream& flux,Lecteur& lecteur)
{

    int i = 0;
    flux<<"Pour le texte : \n[ "<<lecteur.contenu<<" ] on obtient :\n\n";
    flux<<"Lecteur : { ";
    for(i = 0 ; i < 26 ; i++)
    {
        if(lecteur.occurences[i] != 0.0)
        {
            if(i == 0 )
                flux<< "( " <<lecteur.lettres[i] <<" ; "<<lecteur.occurences[i]<<" )";

            else
                flux<< " | ( " <<lecteur.lettres[i] <<" ; "<<lecteur.occurences[i]<<" )";
        }

    }
    flux<<"} \n";
    return flux;
};


Lecteur::~Lecteur()
{
;
};