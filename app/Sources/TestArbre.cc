#include "../Headers/ArbreB.h"
#include "../Headers/Lecteur.h"
#include "../Headers/Cryptage.h"


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
    cr.encodage();
}
