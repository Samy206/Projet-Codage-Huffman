#ifndef CRYPTAGE_H
#define CRYPTAGE_H
#include "Lecteur.h"
#include "ArbreB.h"
#include "Sommet.h"
#include <string>

class Cryptage
{
     private :
        Lecteur lecteur;
        ArbreB arbre;
        Sommet * sommets_restants;
        int nb_sommets;
        std::string contenu;

        std::vector<Sommet> sommets_restants_vect;

     public :

        Cryptage(Lecteur&);
        ~Cryptage();

        void echange(const int,const int) ;

        void creation_arbre();


};


#endif

