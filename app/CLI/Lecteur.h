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
        std::vector<int> occurences;

    public :
        Lecteur();
        Lecteur(Lecteur&);
        ~Lecteur();

        std::vector<char> getLettres() {return lettres;};
        std::vector<int> getOccurences() {return occurences;};
        std::string getContenu() {return contenu;};

        int get_indice(const char);
        void lecture(std::ifstream&);
        void lecture(std::string const &);
        void operator=(Lecteur&);
        friend std::ostream& operator<<(std::ostream&,Lecteur&);
};




#endif