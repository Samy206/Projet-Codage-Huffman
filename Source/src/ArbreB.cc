#include "../headers/ArbreB.h"
using namespace std;


/*Ce constructeur se base sur la méthode ajout qui est implémentée pour ajouter un sommet dans toutes les situations
(y compris quand l'arbreB est vide), et on peut donc ajouter plusieurs sommets via un tableau*/
ArbreB::ArbreB(Sommet * sommets , int size) {
    racine = NULL;
    taille = 0;

    if(sommets != NULL) {
        for(int i = 0 ; i < size ; i++)
            ajout(racine, &sommets[i]);
    }
};

ArbreB::ArbreB(ArbreB& arbre) //ce deuxième constructeur se base sur l'opérateur =
{
    *this = arbre;

};

/* L'opérateur '=' fait appel à la méthode 'ajout' prenant en paramètre un ArbreB si celui ci ( plutôt sa racine
n'est pas nulle ) , et récupère la taille pour copier sa valeur*/
void ArbreB::operator=(ArbreB& arbre)
{
    if(arbre.getRacine() != NULL)
    {
        taille = arbre.getTaille();
        hauteur = arbre.getHauteur();
        ajout(arbre);
    }
    else
    {
        racine = NULL;
        taille = 0 ;
        hauteur = 0 ;
    }
};

/* Pour la première méthode récursive on a la méthode ajout avec un sommet :
   On avance dans l'arbre avec le noeud nommée 'existant' ,
        si on arrive sur un noeud null : ( ça ne peut arriver que pour la racine d'où la ligne 66 ) ,
        on crée une variable noeud à partir de 'sommet' et on l'ajoute à ce noeud ).

        sinon on compare la valeur des fréquences :
            si la fréquence du nouveau noeud est inférieur on le place à gauche,
                si la place est déjà prise on réitère la méthode sur le fils gauche
                sinon on crée une variable noeud et on l'ajoute là
            sinon
                on fait la même chose mais à droite
            et bien sûr on incrémente l'attribut 'taille'

   Grâce à ça on obtient un arbre binaire de recherche classé selon la fréquence*/
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
                ajout(existant->getFilsG(),nouveau);

            else
            {
                existant->setFilsG(nouveau);
                taille+= nouveau->getTaille();
            }
        }
        else
        {
            if(existant->getFilsD() != NULL)
                ajout(existant->getFilsD(),nouveau);

            else
            {
                existant->setFilsD(nouveau);
                taille+= nouveau->getTaille();
            }
        }
    }
    hauteur = calcule_hauteur(racine);
};

/* La méthode copie_noeuds copie tout les sommets d'un arbre et renvoie le premier sommet qui a été copié, c'est donc
la copie totale d'un arbre qui est faite. On se base ici sur la surcharge de l'opérateur '=' de défini dans la classe
Sommet*/
Sommet * ArbreB::copie_sommets(Sommet * source)
{
    Sommet * nouveau = new Sommet;
    *nouveau = *source;

    if(source->getFilsG() != NULL)
        nouveau->setFilsG(copie_sommets(source->getFilsG()));
    else
        nouveau->setFilsG(NULL);

    if(source->getFilsD() != NULL)
        nouveau->setFilsD(copie_sommets(source->getFilsD()));
    else
        nouveau->setFilsD(NULL);
    return nouveau;
};

/* La méthode ajout avec un ArbreB ajoute la copie de tout ses noeuds en faisant appel à la méthode précédente, puis
on ajoute sa racine à l'arbre *this . On fait cela pour éviter les problèmes d'appels au destructeurs à la fin du
code.*/
void ArbreB::ajout(ArbreB& arbre)
{
    racine = copie_sommets(arbre.getRacine());

};

void ArbreB::test_print_tree(Sommet *root, char *indent, int last) {
    if (root == NULL)
        return;


    cout << indent << "+- " << "("<<root->getLettre()<<" : "<<root->getFreq()<< ")\n";
    char indent2[90];
    if (last == 0)
        sprintf(indent2, "%s|   ", indent);
    else
        sprintf(indent2, "%s    ", indent);

    if (root->getFilsG() != NULL && root->getFilsD() != NULL) {
        test_print_tree(root->getFilsG(), indent2, 0);
        test_print_tree(root->getFilsD(), indent2, 1);
    }
    else {
        if (root->getFilsD() != NULL && root->getFilsG() == NULL)
            test_print_tree(root->getFilsD(), indent2, 1);
        else
            test_print_tree(root->getFilsD(), indent2, 0);

        if (root->getFilsG() != NULL && root->getFilsD() == NULL)
            test_print_tree(root->getFilsG(), indent2, 1);
        else
            test_print_tree(root->getFilsG(), indent2, 0);
    }
}


/*Cette méthode affiche l'arbre binaire dans le terminal convenablement*/
void ArbreB::print_tree(Sommet *root, int space){
   if (root == NULL)
      return;
   print_tree(root->getFilsD(), space+2);
   for (int i = 0; i < space; i++)
      cout<<"\t";

   cout<<" ("<<root->getLettre()<<" ; "<<root->getFreq()<<")"<<"\n";

   print_tree(root->getFilsG(), space+2);
}

/*Cet opérateur se contente de faire appel à la méthode précédente*/
std::ostream& operator<<(std::ostream& flux ,ArbreB& arbre) {
    // arbre.print_tree(arbre.getRacine(),0);

    char *indent = new char[1];
    indent[0] = '\0';
    arbre.test_print_tree(arbre.getRacine(), indent, 1);
    delete[] indent;
    return flux;
}

/*Celui ci fait appel à la méthode ajout avec un ArbreB*/
void ArbreB::operator+=(ArbreB& arbre)
{
    this->ajout(arbre);

};

/*Grâce au paramètre noeud la récursivité est permise et à chaque itération on compare sa lettre à celle qui est
recherchée et on renvoie un pointeur sur le noeud correspondant si on le trouve, sinon on applique cela sur les fils
gauche et droite. Dans le cas où la lettre n'est pas dans l'arbre on renvoie NULL*/
Sommet * ArbreB::recherche_sommet(Sommet* sommet,const char car)
{

    if (sommet == NULL){
		return NULL;
	}
	else
	{
	    Sommet * tmp= NULL;
        Sommet * tmp1 = NULL;
		if (sommet->getLettre() == car){
			tmp= sommet;
		}
		else{
            if (sommet->getFilsD() != NULL){
               tmp1 = recherche_sommet(sommet->getFilsD(),car);

            if(tmp1 != NULL)
               tmp = tmp1;
            }

            if (sommet->getFilsG() != NULL){
               tmp1 = recherche_sommet(sommet->getFilsG(),car);

            if(tmp1 != NULL)
                tmp = tmp1;
            }
		}
		return tmp;
	}
};

/*Surcharge de la méthode recherche avec en paramètre une fréquence à la place d'un char. Cette recherche est plus
efficace que la précédente car l'arbre crée est un ABR basé sur l'occurence d'apparence des lettres.
    Quand on est sur un noeud on vérifie qu'il ne soit pas nul:
        S'il l'est on renvoit null
        Sinon on compare la fréquence qu'on recherche à la fréquence actuelle, et selon le résultat de cette comparaison
        on cherche à gauche ou à droite*/
Sommet * ArbreB::recherche_sommet(Sommet * sommet,const char car,const int part)
{

    if (sommet == NULL){
		return NULL;
	}
	else
	{
	    Sommet* tmp= NULL;
        int freq_actuel = sommet->getFreq();
        char c_actuel = sommet->getLettre();

		if (freq_actuel == part && c_actuel == car)
			tmp= sommet;

		else if(freq_actuel > part)
		    tmp = recherche_sommet(sommet->getFilsG(),car,part);

		else
		   tmp = recherche_sommet(sommet->getFilsD(),car,part);

		return tmp;

	}
};

/*Mis à part les actions à appliquer, cette méthode ne diffère pas de la précédente, en effet ici à la place de
renvoyer le noeud correspondant au caractère on récupère l'adresse des ses fils, on le supprime, et on ajoute ses fils
à nouveau.
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
            if(sommet->getFilsG() != NULL)
                tmp1 = sommet->getFilsG();

            if(sommet->getFilsD() != NULL)
                tmp2 = sommet->getFilsD();

            delete racine;
            racine = NULL;

            if(tmp2 != NULL)
                ajout(racine,tmp2);

            if(tmp1 != NULL)
                ajout(racine,tmp1);

        }

		if (sommet->getFilsG() != NULL && sommet->getFilsG()->getLettre() == car){
		    tmp1 = sommet->getFilsG();


		    if(tmp1->getFilsG() != NULL)
		        tmp2 = tmp1->getFilsG();

		    if(tmp1->getFilsD() != NULL)
            	tmp3 = tmp1->getFilsD();

            delete tmp1;
            sommet->setFilsG(NULL);

            if(tmp3 != NULL)
                ajout(racine,tmp3);

            if(tmp2 != NULL)
                ajout(racine,tmp2);

		}
		else if (sommet->getFilsD() != NULL && sommet->getFilsD()->getLettre() == car){
		    tmp1 = sommet->getFilsD();


            if(tmp1->getFilsG() != NULL)
                tmp2 = tmp1->getFilsG();

            if(tmp1->getFilsD() != NULL)
               	tmp3 = tmp1->getFilsD();

            delete tmp1;
            sommet->setFilsD(NULL);

            if(tmp3 != NULL)
                ajout(racine,tmp3);

            if(tmp2 != NULL)
                ajout(racine,tmp2);
		}
		else
		{
             supprimer_sommet(sommet->getFilsD(),car);
             supprimer_sommet(sommet->getFilsG(),car);
		}
		taille--;
	}


};

/*On recherche un noeud et on met simplement à jour sa fréquence*/
void ArbreB::change_etiquette(const char car,const int part)
{
    Sommet * tmp = recherche_sommet(racine,car);
    if(tmp != NULL)
    {
        tmp->setFreq(part);
    }
};

/* Calcul de la hauteur d'un arbre de manière récursive :
  on incrémente la hauteur à chaque itération, et on renvoie le maximum des deux sous-arbres + 1  à chaque fois*/
int ArbreB::calcule_hauteur(Sommet * actuelle)
{
    if(actuelle != NULL)
    {
        int gauche , droite ;
        gauche = calcule_hauteur(actuelle->getFilsG());
        droite = calcule_hauteur(actuelle->getFilsD());

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
    if(racine->getFilsG() != NULL)
        a_gauche.ajout(a_gauche.getRacine(),copie_sommets(racine->getFilsG()));

    if(racine->getFilsD() != NULL)
        a_droit.ajout(a_droit.getRacine(),copie_sommets(racine->getFilsD()));

};


/*On parcours l'arbre et on delete les noeuds un par un*/
void ArbreB::free_tree(Sommet * root) {
    if (root == NULL)
        return;

    free_tree(root->getFilsG());
    free_tree(root->getFilsD());
    delete root;

    /*
    if(root != NULL) {
        this->racine = NULL;
        Sommet * tmpG = root->getFilsG() ;
        Sommet * tmpD = root->getFilsD() ;

        delete root;
        root = NULL;
        free_tree(tmpG);
        free_tree(tmpD);
    } */
};

/* Le destructeur fait appel à la méthode précédente*/
ArbreB::~ArbreB() {
    free_tree(racine);
};