#include "../headers/ArbreB.h"
using namespace std;

ArbreB::ArbreB(Sommet * sommets , int size )
{
    racine = NULL;
    taille = 0;

    if(sommets != NULL)
    {
        for(int i = 0 ; i < size ; i++)
            ajout(racine,sommets[i]);
    }
};

ArbreB::ArbreB(Noeud * noeuds, int size)
{
    racine = NULL ;
    taille =  0 ;
    hauteur = 0 ;
    if(noeuds != NULL)
    {
        for(int i = 0 ; i < size ; i++)
            ajout(racine,&noeuds[i]);
    }
};

/*Les deux premiers constructeurs se basent sur la méthode ajout, et grâce à la surcharge de cette dernière elle est
effective dans les deux cas*/

ArbreB::ArbreB(ArbreB& arbre) //ce troisième constructeur se base sur l'opérateur =
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
void ArbreB::ajout(Noeud * existant,Sommet & sommet)
{
    int freqNew = sommet.getFreq();

    if(existant == NULL)
    {
        Noeud * nouveau = new Noeud;
        nouveau->actuel = sommet;
        nouveau->filsg = NULL;
        nouveau->filsd = NULL;
        racine = nouveau;
        taille++;

    }
    else
    {
        int freqActual = existant->actuel.getFreq();
        if(freqActual > freqNew)
        {
            if(existant->filsg != NULL)
                ajout(existant->filsg,sommet);

            else
            {
                Noeud * nouveau = new Noeud;
                nouveau->actuel = sommet;
                nouveau->filsg = NULL;
                nouveau->filsd = NULL;
                existant->filsg = nouveau ;
                taille++;
            }
        }
        else
        {
            if(existant->filsd != NULL)
                ajout(existant->filsd,sommet);

            else
            {

                Noeud * nouveau = new Noeud;
                nouveau->actuel = sommet;
                nouveau->filsg = NULL;
                nouveau->filsd = NULL;
                existant->filsd = nouveau ;
                taille++;
            }
        }
    }
    hauteur = calcule_hauteur(racine);
};

/*Cette méthode diffère de la précédente uniquement sur un point, on a pas à créer une variable noeud vu qu'elle est
déjà passée en paramètre*/
void ArbreB::ajout(Noeud * existant,Noeud * nouveau)
{
    int freqNew = nouveau->actuel.getFreq();

    if(existant == NULL)
    {
        racine = nouveau;
        taille++;
    }
    else
    {
        int freqActual = existant->actuel.getFreq();
        if(freqActual > freqNew)
        {
            if(existant->filsg != NULL)
                ajout(existant->filsg,nouveau);

            else
            {
                existant->filsg = nouveau ;
                taille++;
            }
        }
        else
        {
            if(existant->filsd != NULL)
                ajout(existant->filsd,nouveau);

            else
            {
                existant->filsd = nouveau ;
                taille++;
            }
        }
    }
    hauteur = calcule_hauteur(racine);
};

/* La méthode copie_noeuds copie tout les noeuds d'un arbre et renvoie le premier noeud qui a été copié, c'est donc
la copie totale d'un arbre qui est faite*/
Noeud * ArbreB::copie_noeuds(Noeud * source)
{
    Noeud * nouveau = new Noeud;

    nouveau->actuel = source->actuel;

    if(source->filsg != NULL)
        nouveau->filsg = copie_noeuds(source->filsg);
    else
        nouveau->filsg = NULL;

    if(source->filsd != NULL)
        nouveau->filsd = copie_noeuds(source->filsd);
    else
        nouveau->filsd = NULL;
    return nouveau;
};

/* La méthode ajout avec un ArbreB ajoute la copie de tout ses noeuds en faisant appel à la méthode précédente, puis
on ajoute sa racine à l'arbre *this . On fait cela pour éviter les problèmes d'appels au destructeurs à la fin du
code.*/
void ArbreB::ajout(ArbreB& arbre)
{
    racine = copie_noeuds(arbre.getRacine());

};

void ArbreB::test_print_tree(Noeud *root, char *indent, int last) {
    if (root == NULL)
        return;


    cout << indent << "+- " << "("<<root->actuel.getLettre()<<" : "<<root->actuel.getFreq()<< ")\n";
    char indent2[90];
    if (last == 0)
        sprintf(indent2, "%s|   ", indent);
    else
        sprintf(indent2, "%s    ", indent);

    //if (root->filsg != NULL && root->filsd != NULL) {
        test_print_tree(root->filsg, indent2, 0);
        test_print_tree(root->filsd, indent2, 1);
   // }
    /*else {
        if (root->filsd != NULL && root->filsg == NULL)
            test_print_tree(root->filsd, indent2, 1);
        else
            test_print_tree(root->filsd, indent2, 0);

        if (root->filsg != NULL && root->filsd == NULL)
            test_print_tree(root->filsg, indent2, 1);
        else
            test_print_tree(root->filsg, indent2, 0);
    }*/
}


/*Cette méthode affiche l'arbre binaire dans le terminal convenablement*/
void ArbreB::print_tree(Noeud *root, int space){
   if (root == NULL)
      return;
   print_tree(root->filsd, space+2);
   for (int i = 0; i < space; i++)
      cout<<"\t";

   cout<<" ("<<root->actuel.getLettre()<<" ; "<<root->actuel.getFreq()<<")"<<"\n";

   print_tree(root->filsg, space+2);
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
Noeud * ArbreB::recherche_noeud(Noeud* noeud,const char car)
{

    if (noeud == NULL){
		return NULL;
	}
	else
	{
	    Noeud* tmp= NULL;
        Noeud* tmp1 = NULL;
		if (noeud->actuel.getLettre() == car){
			tmp= noeud;
		}
		else{
            if (noeud->filsd != NULL){
               tmp1 = recherche_noeud(noeud->filsd,car);
            if(tmp1 != NULL)
               tmp = tmp1;
            }
            if (noeud->filsg != NULL){
               tmp1 = recherche_noeud(noeud->filsg,car);
            if(tmp1 != NULL)
                tmp = tmp1;
            }
		}
		return tmp;
	}
};

/*Mis à part les actions à appliquer, cette méthode ne diffère pas de la précédente, en effet ici à la place de
renvoyer le noeud correspondant au caractère on récupère l'adresse des ses fils, on le supprime, et on ajoute ses fils
à nouveau.
PS: on ajout en premier le fils droit car il a une valeur supérieure.*/
void ArbreB::supprimer_noeud(Noeud * noeud ,const char car)
{

	if(noeud != NULL )
	{
	    Noeud * tmp1 = NULL;
	    Noeud * tmp2 = NULL;
	    Noeud * tmp3 = NULL;

        if(noeud->actuel.getLettre() == car)
        {
            if(noeud->filsg != NULL)
                tmp1 = noeud->filsg;

            if(noeud->filsd != NULL)
                tmp2 = noeud->filsd;

            delete racine;
            racine = NULL;

            if(tmp2 != NULL)
                ajout(racine,tmp2);

            if(tmp1 != NULL)
                ajout(racine,tmp1);

        }

		if (noeud->filsg != NULL && noeud->filsg->actuel.getLettre() == car){
		    tmp1 = noeud->filsg;


		    if(tmp1->filsg != NULL)
		        tmp2 = tmp1->filsg;

		    if(tmp1->filsd != NULL)
            	tmp3 = tmp1->filsd;

            delete tmp1;
            noeud->filsg = NULL;

            if(tmp3 != NULL)
                ajout(racine,tmp3);

            if(tmp2 != NULL)
                ajout(racine,tmp2);

		}
		else if (noeud->filsd != NULL && noeud->filsd->actuel.getLettre() == car){
		    tmp1 = noeud->filsd;


            if(tmp1->filsg != NULL)
                tmp2 = tmp1->filsg;

            if(tmp1->filsd != NULL)
               	tmp3 = tmp1->filsd;

            delete tmp1;
            noeud->filsd = NULL;

            if(tmp3 != NULL)
                ajout(racine,tmp3);

            if(tmp2 != NULL)
                ajout(racine,tmp2);
		}
		else
		{
             supprimer_noeud(noeud->filsd,car);
             supprimer_noeud(noeud->filsg,car);
		}
		taille--;
	}


};

/*On recherche un noeud et on met simplement à jour sa fréquence*/
void ArbreB::change_etiquette(const char car,const int part)
{
    Noeud * tmp = recherche_noeud(racine,car);
    if(tmp != NULL)
    {
        tmp->actuel.setFreq(part);
    }
};

/* Calcul de la hauteur d'un arbre de manière récursive :
  on incrémente la hauteur à chaque itération, et on renvoie le maximum des deux sous-arbres + 1  à chaque fois*/
int ArbreB::calcule_hauteur(Noeud * actuelle)
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


/*On parcours l'arbre et on delete les noeuds un par un*/
void ArbreB::free_tree(Noeud * root)
{
    if(root != NULL)
    {
        Noeud * tmpG = root->filsg ;
        Noeud * tmpD = root->filsd ;

        delete root;
        root = NULL;
        free_tree(tmpG);
        free_tree(tmpD);
    }
};

/*Le destructeur fait appel à la méthode précèdente*/
ArbreB::~ArbreB()
{
    free_tree(racine);
};