#include "../Headers/ArbreB.h"
using namespace std;


/*Ce constructeur se base sur la méthode ajout qui est implémentée pour ajouter un sommet dans toutes les situations
(y compris quand l'arbreB est vide), et on peut donc ajouter plusieurs sommets via un tableau et sa taille
PS : les variables racine et taille sont mis à jour à chaque ajout , et hauteur est calculée une fois qu'on a ajouté
tout les sommets*/

ArbreB::ArbreB(Sommet * sommets , int size )
{
    racine = NULL;
    taille = 0;

    if(sommets != NULL)
    {
        for(int i = 0 ; i < size ; i++)
        {
            ajout(racine,&sommets[i]);
        }
    }
    hauteur = calcule_hauteur(racine);
};

/*Ce deuxième constructeur se base entièrement sur l'opérateur '='*/
ArbreB::ArbreB(ArbreB& arbre)
{
    racine = NULL;
    taille = arbre.getTaille();
    hauteur = arbre.getHauteur();
    *this = arbre;
};

/* Si l'arbre this est vide
      on copie la taille et la hauteur, et on utilise la méthode ajout avec la variable 'arbre' en paramètre
   Sinon
      on commence par libérer la mémoire de l'arbre actuelle et on copie l'autre
*/
void ArbreB::operator=(ArbreB& arbre)
{
    if(racine != NULL) {free_tree(racine);}
    ajout(arbre);
};

/* Pour la première méthode récursive on a la méthode ajout avec un sommet :
   On avance dans l'arbre avec le noeud nommée 'existant' ,
        si on arrive sur un noeud null : ( ça ne peut arriver que pour la racine d'où la ligne 74 ) ,
            on l'ajoute à ce sommet.

        sinon on compare la valeur des fréquences :
            si la fréquence du nouveau sommet est inférieur on le place à gauche,
                si la place est déjà prise on réitère la méthode sur le fils gauche
                sinon on l'ajoute là
            sinon
                on fait la même chose mais à droite
            et bien sûr on incrémente l'attribut 'taille'

Grâce à ça on obtient un arbre binaire de recherche classé selon la fréquence.*/
void ArbreB::ajout(Sommet * existant,Sommet *nouveau)
{
    int freqNew = nouveau->getFreq();

    if(existant == NULL)
    {
        racine = nouveau;
        taille+= nouveau->getTaille();
    }
    else
    {
        int freqActual = existant->getFreq();
        if(freqActual > freqNew)
        {
            if(existant->getFilsG() != NULL)
                ajout(existant->filsg,nouveau);

            else
            {
                existant->filsg = nouveau;
                taille+= nouveau->getTaille();
            }
        }
        else
        {
            if(existant->filsd != NULL)
                ajout(existant->filsd,nouveau);

            else
            {
                existant->filsd = nouveau;
                taille+= nouveau->getTaille();
            }
        }
    }

};

/*Cette méthode reprend les grandes lignes des lignes de la méthode précédente mais à partir d'un caractère et une
fréquence on crée un sommet tout en l'ajoutant à l'arbre*/
void ArbreB::ajout(Sommet* existant,const char car, const int occurence)
{

    if(existant == NULL)
    {
        racine = new Sommet(car,occurence,1);
        taille++;
    }
    else
    {
        int freqActual = existant->getFreq();
        if(freqActual > occurence)
        {
            if(existant->filsg != NULL)
                ajout(existant->filsg,car,occurence);

            else
            {
                existant->filsg = new Sommet(car,occurence,1);
                taille++;
            }
        }
        else
        {
            if(existant->filsd != NULL)
                ajout(existant->filsd,car,occurence);

            else
            {
                existant->filsd = new Sommet(car,occurence,1);
                taille++;
            }
        }

    }
    hauteur = calcule_hauteur(getRacine());
};

/* La méthode copie_sommets copie tout les sommets d'un arbre et renvoie le premier sommet qui a été copié, c'est donc
la copie totale d'un arbre qui est faite. On se base ici sur la surcharge de l'opérateur '=' de défini dans la classe
Sommet*/
/*Sommet * ArbreB::copie_sommets(Sommet * source)
{
    if(source != NULL) ajout(racine,source->getLettre(),source->getFreq());
    return NULL;
};*/

/* La méthode ajout avec un ArbreB ajoute la copie de tout ses sommets en faisant appel à la méthode précédente,
puis on ajoute cette copie au premier sommet de libre ( conformément à l'ABR) de l'arbre *this .
On fait cela pour éviter les problèmes d'appels au destructeurs à la fin du code.*/
void ArbreB::ajout(ArbreB& arbre)
{
    racine = new Sommet;
    *racine = *arbre.getRacine();
};


/*Cette méthode affiche l'arbre en forme d'escaliers de manière récursive */
void ArbreB::print_tree(Sommet *root, char *indent, int last) {
    if (root == NULL)
        return;

    cout << indent << "+- " << "("<<root->getLettre()<<" : "<<root->getFreq()<< ")\n";
    char indent2[90];
    if (last == 0)
        sprintf(indent2, "%s|   ", indent);
    else
        sprintf(indent2, "%s    ", indent);

    if (root->filsg != NULL && root->filsd != NULL) {
        print_tree(root->filsg, indent2, 0);
        print_tree(root->filsd, indent2, 1);
    }
    else {
        if (root->filsd != NULL && root->filsg == NULL)
            print_tree(root->filsd, indent2, 1);
        else
            print_tree(root->filsd, indent2, 0);

        if (root->filsg != NULL && root->filsg == NULL)
            print_tree(root->filsg, indent2, 1);
        else
            print_tree(root->filsg, indent2, 0);
    }
}

/*Cet opérateur se contente de faire appel à la méthode précédente*/
ostream& operator<<(ostream& flux ,ArbreB& arbre) {

    char *indent = new char[1];
    indent[0] = '\0';
    arbre.print_tree(arbre.getRacine(), indent, 1);
    delete[] indent;
    return flux;
}

/*Celui ci fait appel à la méthode ajout avec un ArbreB sans pour autant supprimer l'arbre this avant*/
void ArbreB::operator+=(ArbreB& arbre)
{
    this->ajout(arbre);

};

/*Grâce au paramètre 'sommet' la récursivité est permise et à chaque itération on compare sa lettre à celle qui est
recherchée et on renvoie un pointeur sur le sommet correspondant si on le trouve, sinon on applique cela sur les fils
gauche et droite. Dans le cas où la lettre n'est pas dans l'arbre on renvoie NULL*/

//////

/**
 * Algorithme d'encodage d'une lettre par parcours d'un arbre donné.
 * 
 * @sommet      Sommet courant de l'arbre de Huffman final
 * @car         Caractère à encoder 
 * @s           Chaine de caractère pour stocker l'encodage
 * @curr        Sert de condition d'arrêt à la récursion (lorsque la lettre est encodé)
 * 
 * ! Cette méthode ne fonctionne que si le @car est bien dans l'arbre.
 * – Pour chaque noeud, l’arête vers son fils gauche est étiquetée 0 et celle vers son fils droit 1
 * – Le code associé à une lettre est le mot binaire composé des étiquettes entre la racinela feuille-lettre
 */ 
int ArbreB::create_code(Sommet *sommet, const char car, string& s, int curr) {
    if (curr == 1) // Condition d'arrêt
        return 1;
    
    if (sommet->getLettre() == car) // La lettre du sommet est celle que l'on cherche
        return 1;
    else {
        if (sommet->filsg != NULL){
            s.push_back('0'); // Branche gauche: On ajoute '0' au code huffman de la lettre courante
            curr = create_code(sommet->filsg, car, s, curr);
        }
        // On vérifie que le sommet n'a pas été trouvé dans la branche gauche en vérifiant que curr tjrs == 0
        if (!curr && sommet->filsd != NULL) {
            s.push_back('1'); // Branche droite: On ajoute '1' au code huffman de la lettre courante
            curr = create_code(sommet->filsd, car, s, curr);
        }
    }
    
    if (!curr) // Si le sommet a été trouvé dans l'une des deux branches, on pop_back pas
        s.pop_back(); // On annule la dernière étiquette ajouté
	
    return curr;
};

/*Surcharge de la méthode recherche avec en paramètre une fréquence et une fréquence . Cette recherche est plus
efficace que la précédente car l'arbre crée est un ABR basé sur l'occurence d'apparence des lettres.
    Quand on est sur un sommet on vérifie qu'il ne soit pas nul:
        S'il l'est on renvoit null
        Sinon on compare la fréquence et la lettre qu'on recherche aux données du sommet, et selon le résultat
        de cette comparaison on cherche à gauche ou à droite*/
// string ArbreB::recherche_sommet(Sommet * sommet,const char car,const int part,string& res)
// {

// 	if(sommet != nullptr)
// 	{
//         int freq_actuel = sommet->getFreq();
//         char c_actuel = sommet->getLettre();

// 		if (freq_actuel == part && c_actuel == car)
// 			return res;


// 		else if(freq_actuel > part)
// 		{
// 		    res += '0';

// 		    recherche_sommet(sommet->filsg,car,part,res);
// 	    }

// 		else
// 		{
// 		   res += '1';
// 		   recherche_sommet(sommet->filsd,car,part,res);
// 		}

// 		return res;
// 	}
// 	else
// 	  return NULL;
// };

/*Mis à part les actions à appliquer, cette méthode ne diffère pas de la précédente, en effet ici à la place de
renvoyer le sommet correspondant au caractère on récupère l'adresse des ses fils, on le supprime, et on ajoute
ses fils à nouveau.
PS: on ajout en premier le fils droit car il a une valeur supérieure.*/
void ArbreB::supprimer_sommet(Sommet * sommet ,const char car)
{

	if(sommet != NULL )
	{
	    Sommet * tmp1 = NULL;
	    Sommet * tmp2 = NULL;
	    Sommet * tmp3 = NULL;

        if(sommet->getLettre() == car)
        {
            if(sommet->filsg != NULL)
                tmp1 = sommet->filsg;

            if(sommet->filsd != NULL)
                tmp2 = sommet->filsd;

            delete racine;
            racine = NULL;

            if(tmp2 != NULL)
                ajout(racine,tmp2);

            if(tmp1 != NULL)
                ajout(racine,tmp1);

        }

		if (sommet->filsg != NULL && sommet->filsg->getLettre() == car){
		    tmp1 = sommet->filsg;


		    if(tmp1->filsg != NULL)
		        tmp2 = tmp1->filsg;

		    if(tmp1->filsd != NULL)
            	tmp3 = tmp1->filsd;

            delete tmp1;
            sommet->filsg = NULL;

            if(tmp3 != NULL)
                ajout(racine,tmp3);

            if(tmp2 != NULL)
                ajout(racine,tmp2);

		}
		else if (sommet->filsd != NULL && sommet->filsd->getLettre() == car){
		    tmp1 = sommet->filsd;


            if(tmp1->filsg != NULL)
                tmp2 = tmp1->filsg;

            if(tmp1->filsd != NULL)
               	tmp3 = tmp1->filsd;

            delete tmp1;
            sommet->filsd = NULL;

            if(tmp3 != NULL)
                ajout(racine,tmp3);

            if(tmp2 != NULL)
                ajout(racine,tmp2);
		}
		else
		{
             supprimer_sommet(sommet->filsd,car);
             supprimer_sommet(sommet->filsg,car);
		}
		taille--;
	}


};

/*On recherche un noeud et on met simplement à jour sa fréquence*/
/*void ArbreB::change_etiquette(const char car,const int part)
{
    Sommet * tmp = recherche_sommet(racine,car);
    if(tmp != NULL)
    {
        tmp->freq = part;
    }
};*/

/* Calcul de la hauteur d'un arbre de manière récursive :
  on incrémente la hauteur à chaque itération, et on renvoie le maximum des deux sous-arbres + 1  à chaque fois*/
int ArbreB::calcule_hauteur(Sommet * actuelle)
{
    if(actuelle != NULL)
    {
        int gauche , droite ;
        gauche = calcule_hauteur(actuelle->filsg);
        droite = calcule_hauteur(actuelle->filsd);

        if(gauche > droite)
            return (gauche + 1);

        else
            return (droite + 1);
    }
    return 0;
};

/*Copie des noeuds en partant du fils gauche et du fils droit de la racine, et stockage de ces copies dans les
ArbreB passés en paramètre*/
void ArbreB::decomposition(ArbreB& a_gauche, ArbreB& a_droit)
{

    if(racine->filsg != NULL)
        a_gauche.ajout(a_gauche.getRacine(),racine->filsg);

    if(racine->filsd != NULL)
        a_droit.ajout(a_droit.getRacine(),racine->filsd);

};

/*Cette méthode se base sur l'opérateur += et fusionne les deux arbres passés en paramètre*/
void ArbreB::fusion_arbre(ArbreB& arbre1, ArbreB& arbre2)
{
    if(arbre1.getRacine() != NULL)
        *this += arbre1;

    if(arbre2.getRacine() != NULL)
        *this += arbre2;

};


/*On parcours l'arbre et on delete les sommet un par un*/
void ArbreB::free_tree(Sommet * root)
{
    if(root != NULL )
    {
        Sommet * tmpG = NULL;
        Sommet * tmpD = NULL;

        if(root->filsg != NULL)
           tmpG = root->filsg;

        if(root->filsd != NULL)
            tmpD = root->filsd;

        delete root;
        if(tmpG != NULL)free_tree(tmpG);
        if(tmpD != NULL)free_tree(tmpD);

    }
};

/*Le destructeur fait appel à la méthode précèdente*/
ArbreB::~ArbreB()
{
    free_tree(racine);
};