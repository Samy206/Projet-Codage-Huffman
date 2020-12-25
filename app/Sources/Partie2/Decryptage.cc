#include "../../Headers/Partie2/Decryptage.h"
using namespace std;
/**
 * @brief Constructeur de classe: constitué d'un chaine cryptée et d'une map
 */
Decryptage::Decryptage(std::string text, std::map <char,std::string> map) {
    crypted = text;
    encod_map = map;
};

/**
 * @brief Constructeur de classe: constitué d'un chaine cryptée et d'un arbre de huffman
 */
Decryptage::Decryptage(std::string text, ArbreB huffman)
{
    arbre_huffman = huffman;
    crypted = text;
};

/** 
 * @brief Renvoie la taille de chaîne maximale parmi les chaine d'encodage de caractères de la map
 */ 
int Decryptage::calcul_taille_max(std::map <char,std::string> encod_map) {
    int max = 0;
    for (std::pair<char,std::string> p : encod_map) {
        if (int(p.second.size()) > max)
            max = p.second.size();
    }
    return max;
};

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
void Decryptage::decrypte_map()  {
    int taille_max = calcul_taille_max(encod_map); // On calcule la taille maximale pour définir la condition d'arrêt
    std::string current; // Stocke les caractères lus dans @crypted tant qu'une lettre n'est pas reconnue
    std::string decrypted; // String résultat du décryptage
                
    // std::cout << "Taille maximale: " << taille_max << std::endl;

    // Boucle principale: Pour chaque caractère du texte crypté
    for (char c : crypted)  { 
        // Si le caractère lu ne fait pas partie des caractères non cryptés (n'est ni un 0 ni un 1, cas de l'espace par exp)
        if (c != '0' && c != '1')  { 
            decrypted.push_back(c); // On ajoute directement le caractère clair à la chaine résultat
            continue;
        }

        current.push_back(c); // On stocke le caractère dans la string current
        std::cout << "- Current: " << current << std::endl;

        // Condition d'arrêt: taille de current dépasse taille maximale de la map
        if (int(current.size()) > taille_max)  {
            std::cout << "\033[31mErreur: Le texte crypté donné n'a pas été codé par la map d'encodage donnée\033[00m" << std::endl;
            break;
        }

        // On vérifie si la string existe dans la map en la parcourant
            // Opti: Passer en unordered ou autre pour pouvoir utiliser find(std:string)
        for (std::pair<char,std::string> p : encod_map)  {
            if (current == p.second)  {
                std::cout << "Identification '" << p.second << "': " << p.first << std::endl;
                decrypted.push_back(p.first); // On ajoute le caractère clair à la chaine résultat
                current.clear(); // On vide la string current
                break; // On quitte la boucle
            }
        }
        // std::cout << "Résultat: " << decrypted << std::endl;
    }

    // On vérifie si l'exécution n'a pas étée breaked par la condition d'arrêt:
    // Si current a bien été clear, cela signifie que la lettre a été correctement écrite
    if (current.empty()) {
        std::cout << "\033[1;32mLe texte crypté aurait pu être crypté via la map donnée en paramètre, le texte décrypté est: '" << decrypted << "'\033[00m" << std::endl;
    }
    // Sinon, cela voudrait dire qu'il y a eu dépassement de taille, donc lettre non reconnue
    else  {
        std::cout << "\033[1;31mErreur lors de l'exécution de l'algorithme de décryptage\033[00m" << std::endl;
    }
};


void Decryptage::decrypte_arbre()
{

    //std::string current_s; // Stocke les caractères lus dans @crypted tant qu'une lettre n'est pas reconnue
    std::string decrypted; // String résultat du décryptage
    Sommet * current = arbre_huffman.getRacine();
    for(char c: crypted)
    {
        if(c == '1')
        {
            if(current->filsd == NULL)
            {
                cout << "\033[1;31mErreur lors de l'exécution de l'algorithme de décryptage\033[00m" << std::endl;
                return;
            }
            current = current->filsd;
            if(current->lettre != ' ')
            {

                decrypted += current->lettre;
                current = arbre_huffman.getRacine();
            }
        }

        else if(c == '0')
        {
            if(current->filsg == NULL)
            {
                cout << "\033[1;31mErreur lors de l'exécution de l'algorithme de décryptage\033[00m" << std::endl;
                return;
            }
            current = current->filsg;
            if(current->lettre != ' ')
            {
                decrypted += current->lettre;
                current = arbre_huffman.getRacine();
            }
        }

        else
        {
            if(current->lettre != ' ')
            {
                cout << "\033[1;31mErreur lors de l'exécution de l'algorithme de décryptage\033[00m" << std::endl;
                return;
            }

            else
            {
                decrypted += c;
            }
        }
    }

    if(current != arbre_huffman.getRacine())
    {
        cout << "\033[1;31mErreur lors de l'exécution de l'algorithme de décryptage, l'arbre ne correspond donc pas au texte\033[00m" << std::endl;
        return;
    }

    else
    {
        Lecteur l;
        l.lecture(decrypted);
        vector<char> lettres = l.getLettres();
        vector<float> occurences = l.getOccurences();
        int taille = lettres.size();
        float comparateur = 0.0;

        for(int i = 0 ; i < taille ; i++)
        {

            comparateur = arbre_huffman.get_occ_sommet(arbre_huffman.getRacine(),lettres[i]);
            if(comparateur != occurences[i])
            {
                 std::cout <<"\033[1;37m> Le texte n'a pas été codé par la partie 2, mais l'arbre fourni peut effectivement servir à décoder ce texte.\n> Résultat : \033[0m"<<decrypted<<std::endl;
                 return;
            }
        }
        std::cout <<"\033[1;37m> Le texte a peut-être été codé par la partie 2 mais on ne peut pas être sûrs.\n> Résultat : \033[0m"<<decrypted<<std::endl;
    }
};



Decryptage::~Decryptage()
{
    encod_map.erase(encod_map.begin(),encod_map.end());
};