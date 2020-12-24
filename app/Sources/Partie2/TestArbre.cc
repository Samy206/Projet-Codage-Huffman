#include "../../Headers/Partie2/ArbreB.h"
#include "../../Headers/Partie2/Lecteur.h"
#include "../../Headers/Partie2/Cryptage.h"

#include "../../Headers/Partie2/Decryptage.h"

/**
 * @file TestArbre.cc
 * @brief Partie 2 : Constitue la fonction main lors de l'exécution sans interface graphique pour le Cryptage.
 * Construit l'arbre de cryptage du texte lu depuis le fichier text.txt puis l'encode selon l'algorithme de Huffman. 
 */
int main(int argc, char* argv[]) {
    std::cout << "\033[1;33mProjet LA - Partie 2 | Samy BOUMALI & Amine ATEK\033[0m - Exécution CLI\n\n" << std::endl;
    
    // Ouverture, lecture et calcul des occurrences des lettres pour le texte donné en entrée
    Lecteur l;
    std::ifstream mytext("app/text.txt");
    l.lecture(mytext);

    // Affichage du texte
    std::cout << "\033[1;37m> Texte à coder: \033[0m" << l.getContenu() << std::endl;
    Cryptage cr(l);

    // Construction et affichage de l'arbre binaire de cryptage
    cr.construction_arbre();
    std::cout << "\n\033[1;37mArbre binaire de cryptage:\033[0m\n" << cr.get_arbre() << std::endl;

    // Encodage et affichage du texte après exécution de l'algorithme de Huffman
    std::string crypted = cr.encodage();

    // Test de décryptage avec une bonne combinaison
    std::cout << "\n\033[1;37m> Test de décryptage avec la bonne combinaison: \033[0m" << std::endl;
    Decryptage dr(crypted, cr.get_map());
    dr.decrypte();

    std::cout << "\n\033[1;37m> Test de décryptage avec une mauvaise combinaison: \033[0m" << std::endl;
    std::map<char, std::string> foo_map = { {'t', "00"}, {'e', "11"}, {'a', "01"} };
    Decryptage dr2(crypted, foo_map);
    dr2.decrypte();
}
