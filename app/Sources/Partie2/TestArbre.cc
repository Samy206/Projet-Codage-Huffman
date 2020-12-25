#include "../../Headers/Partie2/ArbreB.h"
#include "../../Headers/Partie2/Lecteur.h"
#include "../../Headers/Partie2/Cryptage.h"

#include "../../Headers/Partie2/Decryptage.h"
using namespace std;
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
    /*std::cout << "\n\033[1;37m> Test de décryptage avec la bonne combinaison: \033[0m" << std::endl;
    Decryptage dr(crypted, cr.get_map());
    dr.decrypte_map();

    std::cout << "\n\033[1;37m> Test de décryptage avec une mauvaise combinaison: \033[0m" << std::endl;
    std::map<char, std::string> foo_map = { {'t', "00"}, {'e', "11"}, {'i', "10"} };
    Decryptage dr2(crypted, foo_map);
    dr2.decrypte_map();

    std::cout << "\n\033[1;37m> Test de décryptage avec les bons encodages mais pas les mêmes caractères: \033[0m" << std::endl;
    std::map<char, std::string> foo_map2 = { {'t', "00"}, {'e', "11"}, {'i', "10"}, {'a', "01"} };
    Decryptage dr3(crypted, foo_map2);
    dr3.decrypte_map();*/
    //std::cout<<"cr arbre : \n"<<cr.get_arbre();

    /*string truc("abcde");
    Lecteur l1;
    l1.lecture(truc);
    Cryptage cr1(l1);
    cr1.construction_arbre();
    string autre = cr1.encodage();*/
    Decryptage dr4(crypted,cr.get_arbre());
    dr4.decrypte_arbre();
    /*ArbreB arbre;
    arbre.ajout(arbre.getRacine(),'a',43);
    arbre.ajout(arbre.getRacine(),'b',433);
    arbre.ajout(arbre.getRacine(),'c',431);
    arbre.ajout(arbre.getRacine(),'g',8431);
    arbre.ajout(arbre.getRacine(),'d',4331);
    arbre.ajout(arbre.getRacine(),'e',4311);
    arbre.ajout(arbre.getRacine(),'f',6431);
    cout<<"wtf : "<<arbre.get_occ_sommet(arbre.getRacine(),'d')<<endl;*/
}
