#ifndef LECTEUR_H
#define LECTEUR_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Lecteur
{
    private :
        std::string contenu;
        std::vector<char> lettres;
        std::vector<float> occurences;

    public :
        Lecteur();
        Lecteur(Lecteur&);
        ~Lecteur();

        std::vector<char> getLettres() {return lettres;};
        std::vector<float> getOccurences() {return occurences;};
        std::string getContenu() {return contenu;};

        void lecture(std::ifstream&);

        void operator=(Lecteur&);
        friend std::ostream& operator<<(std::ostream&,Lecteur&);
};




#endif