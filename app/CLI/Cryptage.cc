#include "Cryptage.h"

using namespace std;

Cryptage::Cryptage(Lecteur& l) {
    lecteur = l;
};


Cryptage::~Cryptage() {
    arbres_restants.clear();
    // delete[] codage;
}; 


void tst_print_sommet(Sommet *root, char *indent, int last) {
    if (root == NULL)
        return;

    cout << indent << "+- " << "("<<root->getLettre()<<" : "<<root->getFreq()<< ")\n";
    char indent2[90];
    if (last == 0)
        sprintf(indent2, "%s|   ", indent);
    else
        sprintf(indent2, "%s    ", indent);

    if (root->getFilsG() != NULL && root->getFilsD() != NULL) {
        tst_print_sommet(root->getFilsG(), indent2, 0);
        tst_print_sommet(root->getFilsD(), indent2, 1);
    }
    else {
        if (root->getFilsD() != NULL && root->getFilsG() == NULL)
            tst_print_sommet(root->getFilsD(), indent2, 1);
        else
            tst_print_sommet(root->getFilsD(), indent2, 0);

        if (root->getFilsG() != NULL && root->getFilsG() == NULL)
            tst_print_sommet(root->getFilsG(), indent2, 1);
        else
            tst_print_sommet(root->getFilsG(), indent2, 0);
    }
}

void swap(Sommet* tab, int i, int j) {
    Sommet S1 = tab[i];
    tab[i] = tab[j];
    tab[j] = S1;
}

// An optimized version of Bubble Sort
void bubbleSort(std::vector<Sommet> *vect, int n) {
    Sommet *tmp_tab = new Sommet[vect->size()];
    int i = 0;
    for (Sommet s : *vect) {
        tmp_tab[i] = vect->back(); vect->pop_back();
        i++;
    }

    int j;
    bool swapped;
    for (i = 0; i < n-1; i++)
    {
        swapped = false;
        for (j = 0; j < n-i-1; j++)
        {
            if (tmp_tab[j].getFreq() > tmp_tab[j+1].getFreq())
            {
                swap(tmp_tab, j, j+1);
                swapped = true;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == false)
            break;
    }

    for(i = n-1; i >= 0; i--)
        vect->push_back(tmp_tab[i]);

    delete[] tmp_tab;
}

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
void Cryptage::construction_arbre() {
    // Les deux std::vector sont à passer idéalement en Map
    vector<float> tmp2 = lecteur.getOccurences(); // Vector des occurences
    vector<char> tmp1 = lecteur.getLettres(); // Vector des lettres

    // Initialement, on créé un Sommet pour chacune des lettre dont l'occurence n'est pas nulle
        // À optimiser: on devrait pouvoir avoir le nombre exacte de lettre différentes au lieu de tester sur l'alphabet
    for(int i = 0 ; i < 26 ; i++) {
        if(tmp2[i] != 0.0) {
            Sommet * tmp = new Sommet(tmp1[i], tmp2[i], 1);
            arbres_restants.push_back(*tmp);
            delete tmp;
        }
    }

    // On trie les arbres restants par occurence à l'aide d'un Tri Fusion
    vector<Sommet> * combinaisons = new vector<Sommet>;
    *combinaisons = arbres_restants;
    bubbleSort(combinaisons, combinaisons->size());

    Sommet A1, A2; // Deux sommets avec les plus faibles occurences
    Sommet *newSomm; // Nouveau sommet créé, racine de A1 et A2

    // Condition d'arrêt: Tant qu'il y a plus d'un arbre dans le vecteur de gestion des arbres restants
    while(combinaisons->size() > 1) {
        // On considère les deux sommets ayant l'occurence la plus faible
        A1 = combinaisons->back();  combinaisons->pop_back();
        A2 = combinaisons->back();  combinaisons->pop_back();

        // Création de l'arbre A (Sommet newSomm) étiqueté e1 + e2
        newSomm = new Sommet(' ', A1.getFreq() + A2.getFreq(), 1);

        // Le nouvel arbre a pour fils les racines de A1 et A2
        newSomm->setFilsD(&A2);
        newSomm->setFilsG(&A1);

        // On place le nouvel arbre dans la liste des sommets courants (La surcharde de l'opérateur = copie aussi les fils)
        combinaisons->push_back(*newSomm);

        delete newSomm; // Suppression de l'arbre A maintenant stocké dans la liste des sommets restants

        bubbleSort(combinaisons, combinaisons->size()); // On re-trie la liste des sommets restants
    }

    // À la fin de cette boucle, le vecteur de gestion des arbres restants contient l'abre de cryptage fina
    if (combinaisons->size() != 1) {
        std::cout << "Erreur lors de la création de l'arbre de cryptage" << std::endl;
        return;
    }

    // On ajoute maintenant ce Sommet à l'Arbre de la classe Cryptage

    //// *** PARTIE À RETIRER QUAND ON RÉUSSIRA L'AJOUT DU SOMMET À L'ARBRE DE LA CLASSE *** ////

    char *indent = new char[1]; indent[0] = '\0'; // Utile pour afficher les arbres dans le terminal
    delete[] indent;

    arbre_huffman.ajout(arbre_huffman.getRacine(), &combinaisons->back());
    //std::cout<<"Taille arbre: "<< arbre_huffman.getTaille() << endl;
    std::cout << arbre_huffman << endl;

};


int Cryptage::get_code(pair<char,string> * vec, char lettre, int size)
{
    int indice = -1;
    for(int i = 0 ; i < size ; i++)
    {
        if(vec[i].first == lettre)
        {
            indice = i;
            break;
        }
    }
    return indice;
};

void Cryptage::encodage() {
    int taille = arbres_restants.size();
    codage = new std::pair <char, string> [taille];
    for(int i = 0 ; i < taille; i++) {
        codage[i].first = arbres_restants[i].getLettre();
        codage[i].second = "";

        arbre_huffman.create_code(arbre_huffman.getRacine(), arbres_restants[i].getLettre(), codage[i].second, 0);
    }

    for(size_t i = 0; i < arbres_restants.size(); i++)
        cout<<codage[i].first << ": " << codage[i].second<<endl;

    string contenunew;
    int ascii;
    int code;
    char c;
    for(size_t i = 0 ; i < lecteur.getContenu().size() ; i++)
    {
        ascii = -1;
        ascii = int(lecteur.getContenu()[i]);

        if(ascii >= 65 && ascii <= 90)
        {
            c = (char) (ascii+32);
            code = get_code(codage,c,taille);
            contenunew += codage[code].second;
        }
        else if(ascii >= 97 && ascii <= 122)
        {
             code = get_code(codage,(lecteur.getContenu()[i]),taille);
             contenunew += codage[code].second;
        }
        else
            contenunew += lecteur.getContenu()[i];
    }

    cout<<"Nouveau texte : "<<contenunew<<endl;
}

