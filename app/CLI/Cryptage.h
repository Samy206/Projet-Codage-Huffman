#ifndef CRYPTAGE_H
#define CRYPTAGE_H
#include "Lecteur.h"
#include "ArbreB.h"
#include "Sommet.h"
#include <string>
#include <utility>

class Cryptage
{
   private :
      Lecteur lecteur;
      ArbreB arbre_huffman;
      std::vector<Sommet> arbres_restants;
      std::string contenu;
      std::pair <char,std::string> * codage;

   public :
      /**
       * Constructeur de classe
       */
      Cryptage(Lecteur&);
      ~Cryptage();

      void echange(const int, const int) ;

      /**
       * @brief Algorithme de cryptage: création de l'arbre de Huffman à partir d'un vecteur de lettres et occurences.
       * 
       * Initialement: On créé un arbre (Sommet) étiqueté par l'occurence de chacune des lettres du `lecteur`
       * Le vecteur `arbres_restants` gère le nombre d'arbres restants lors de l'exécution de l'algorithme
       * 
       * Condition d'arrêt de la boucle: Tant qu'il reste plus d'un arbre dans le vecteur arbres_restants
       * 1. On tri le vecteur de sorte à considérer A1 et A2 les deux arbres portant les étiquettes e1 et e2 les plus faibles
       * 2. Création de l'arbre A (Sommet `newSomm`) étiqueté e1 + e2 et attribution de ses fils A1 et A2
       */ 
      void construction_arbre();
      void encodage();
      int get_code(std::pair<char,std::string> *, char,int);

};


#endif

