#ifndef DECRYPTAGE_H
#define DECRYPTAGE_H
#include "ArbreB.h"
#include "Lecteur.h"
#include <iostream> // cout
#include <string>
#include <map>


/**
 * @file Decryptage.h
 * @brief Partie 3 : 
 */ 
class Decryptage
{
    private:
        std::string crypted; // Texte crypté 
        ArbreB arbre_huffman; // Arbre binaire de cryptage - A IMPLEMENTER ?
        std::map <char,std::string> encod_map; // Map des encodages

    public:
        /**
         * @brief Constructeur de classe: constitué d'un chaine cryptée et d'une map
         */
        Decryptage(std::string, std::map <char,std::string>);
        Decryptage(std::string, ArbreB);
        ~Decryptage();

        /** 
         * @brief Renvoie la taille de chaîne maximale parmi les chaine d'encodage de caractères de la map
         */ 
        int calcul_taille_max(std::map <char,std::string>);


        /**
         * @brief Algorithme de décryptage 
         * 
         * - Pour vérifier que le texte crypté correspond bien à la map de l'encodage : 
         *      On récupère la taille de l'encodage maximal de la map
         *      Pour chaque caractère du texte crypté, on l'ajoute à la string current et on compare à ce que contient la map
         *      Si la taille de la string current dépasse la taille maximale, c'est que les caractères cryptés n'existent pas dans cette map
         *      Ce qui veut dire que le texte n'a pas été codé avec cette map
         * 
         *      A l'inverse, si le texte est correctement retranscrit, on conclue que le texte donné pourrait avoir été codé avec cette map (ses lettres sont inclus dans celles de la map)
         * 
         */
        void decrypte_map();
        void decrypte_arbre();
};

#endif // DECRYPTAGE_H