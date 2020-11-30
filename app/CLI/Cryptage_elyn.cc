#include "Cryptage.h"
#include <algorithm>
using namespace std;

Cryptage::Cryptage(Lecteur& l)
{
    lecteur = l;
};

Cryptage::~Cryptage() { };

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
} 


/**
 * Initialement, chaque lettre est un arbre binaire ramené à un sommet étiqueté par la proportion
 * d’occurences de cette lettre dans le texte. Tant qu’il y a plus d’un arbre, réaliser les opérations suivantes :
 * 1. Considérer A1 et A2 les deux arbres dont les racines portent les plus petites étiquettes e1 et e2.
 * 2. Construire un nouvel arbre A dont la racine r a pour fils les racines de A1 et A2.
 * 3. La racine r est étiqueté par e1 + e2.
 * – Pour chaque noeud de l’arbre final, l’arête vers son fils gauche est étiquetée 0 et celle vers son fils droit 1.
 * – Le code associé à une lettre est le mot binaire composé des étiquettes sur les arêtes entre la racine de 
 *   l’arbre final et la feuille étiquetée avec cette lettre.
 */

// Initialement : Créer un sommet pour chacune des lettres dont l'occurence n'est pas nulle 
// Condition de boucle : Tant qu'il y a plus d'un arbre
// 1. Trouver les deux arbres dont les occurences sont les plus petites
    // - Tri fusion
    // - Deux derniers sont retournés

void Cryptage::creation_arbre() {
    sommets_restants = new Sommet[26];

    // Les deux std::vector sont à passer idéalement en Map
    vector<float> tmp2 = lecteur.getOccurences(); // Vector des occurences
    vector<char> tmp1 = lecteur.getLettres(); // Vector des lettres
    
    // On créé un Sommet pour chacune des lettre dont l'occurence n'est pas nulle
        // À optimiser: on devrait pouvoir avoir le nombre exacte de lettre différentes au lieu de tester sur l'alphabet
    for(int i = 0 ; i < 26 ; i++) {
        if(tmp2[i] != 0.0) {
            Sommet * tmp = new Sommet(tmp1[i], tmp2[i], 1);
            sommets_restants_vect.push_back(*tmp);
            delete tmp;
        }
    }

    // On trie les arbres restants par occurence à l'aide d'un Tri Fusion
    bubbleSort(&sommets_restants_vect, sommets_restants_vect.size());
    std::cout << "TestTri :" << endl;
    for (Sommet s : sommets_restants_vect)
        cout << s.formalize_sommet() << endl;

    std::cout << " > Step 1" << endl;
    std::cout << "Text: " << lecteur.getContenu() << endl; 
    
    Sommet A1, A2; // Deux sommets avec les plus faibles occurences
    Sommet *newSomm; // Nouveau sommet créé, racine de A1 et A2

    int etape = 2;
    char *indent = new char[1];
    indent[0] = '\0';

    std::cout << "Nbr de sommets dans le vect: " << sommets_restants_vect.size() << endl;
    // Condition d'arrêt: Tant qu'il y a plus d'un arbre (tant que nb_sommet > 2)
    while(sommets_restants_vect.size() > 1) {
        std::cout << "\n > Step " << etape << endl;
        std::cout << "Sommets restants:" << endl;
        for (Sommet s : sommets_restants_vect) {
            // std::cout << s.formalize_sommet() << endl;
            tst_print_sommet(&s, indent, 1);
        }

        A1 = sommets_restants_vect.back();  sommets_restants_vect.pop_back();
        A2 = sommets_restants_vect.back();  sommets_restants_vect.pop_back();

        std::cout << "Sommets selectionnés:\nA1: " << A1.formalize_sommet() << "\nA2: " << A2.formalize_sommet() << endl;

        std::cout << "Nbr de sommets dans le vect: " << sommets_restants_vect.size() << endl;

        // Création de l'arbre A (Sommet newSomm) étiqueté e1 + e2
        newSomm = new Sommet(' ', A1.getFreq() + A2.getFreq(), 1);

        // Le nouvel arbre a pour fils les racines de A1 et A2 (insertion de la fréquence la plus faible à gauche)
        newSomm->setFilsD(&A1);
        newSomm->setFilsG(&A2);

        // On place le nouvel arbre dans la liste des sommets courants (La surcharde de l'opérateur = copie aussi les fils)
        sommets_restants_vect.push_back(*newSomm); 
        
        std::cout << "Sommet créé et transféré:" << endl;
        tst_print_sommet(&(sommets_restants_vect.back()), indent, 1);
        delete newSomm; // Suppression de l'arbre A maintenant stocké dans la liste des sommets restants

        bubbleSort(&sommets_restants_vect, sommets_restants_vect.size()); // On re-trie la liste des sommets restants 
        // std::cout << "Sommets restants:" << endl;
        // for (Sommet s : sommets_restants_vect)
        //     tst_print_sommet(&s, indent, 1);
            // std::cout << i << ". " << sommets_restants[i].getLettre() << endl; 
        
        etape++;
    }
    
    ArbreB arbreTST(sommets_restants, nb_sommets);
    // arbre.ajout(arbre.getRacine(), &sommets[0]);
    // arbre.ajout(arbre.getRacine(), &sommets[1]);

    // cout<<"taille arbre : "<<arbreTST.getTaille()<<endl;
    std::cout << arbreTST << endl;
};

