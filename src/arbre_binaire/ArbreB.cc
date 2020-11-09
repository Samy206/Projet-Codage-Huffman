#include "ArbreB.h"
using namespace std;

ArbreB::ArbreB(Sommet * sommets , int size)
{
    racine = NULL;
    taille = 0;
    if(sommets != NULL)
    {
        for(int i = 0 ; i < size ; i++)
        {
            ajout(racine,sommets[i]);
        }
    }
};

ArbreB::ArbreB(Noeud * noeuds, int size)
{
    racine = NULL ;
    taille =  0 ;

    if(noeuds != NULL)
    {
        for(int i = 0 ; i < size ; i++)
            ajout(racine,&noeuds[i]);
    }
};

ArbreB::ArbreB(ArbreB& arbre)
{
    *this = arbre;

};

void ArbreB::operator=(ArbreB& arbre)
{
    if(racine != arbre.getRacine())
    {
        taille = arbre.getTaille();
        ajout(arbre);
    }
};

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
};
void ArbreB::ajout(Noeud * existant,Noeud * nouveau)
{
    int freqNew = nouveau->actuel.getFreq();

    if(existant == NULL)
    {
        existant = nouveau;
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
};

Noeud * ArbreB::copie_noeuds(Noeud * source)
{
    Noeud * nouveau = new Noeud;

    nouveau->actuel = source->actuel;

    if(source->filsg != NULL)
        nouveau->filsg = copie_noeuds(source->filsg);

    if(source->filsd != NULL)
        nouveau->filsd = copie_noeuds(source->filsd);

    return nouveau;
};

void ArbreB::ajout(ArbreB& arbre)
{
    ajout(racine,copie_noeuds(arbre.getRacine()));

};

void ArbreB::print_tree(Noeud *root, int space){
   if (root == NULL)
      return;
   print_tree(root->filsd, space+2);
   for (int i = 0; i < space; i++)
      cout<<"\t";

   cout<<" ("<<root->actuel.getLettre()<<" ; "<<root->actuel.getFreq()<<")"<<"\n";

   print_tree(root->filsg, space+2);
}

std::ostream& operator<<(std::ostream& flux ,ArbreB& arbre)
{
    arbre.print_tree(arbre.getRacine(),0);
    return flux;
}

void ArbreB::operator+=(ArbreB& arbre)
{
    this->ajout(arbre);

};

Noeud * ArbreB::recherche_noeud(Noeud* noeud,const char car)
{

    if (noeud == NULL){
		return NULL;
	}
	else{
	    Noeud* tmp= NULL;
		if (noeud->actuel.getLettre() == car){
		    cout<<"la lettre recherchée a été trouvée\n";
			tmp= noeud;
		}
		else{
            if (noeud->filsd != NULL){
               tmp = recherche_noeud(noeud->filsd,car);
            }
            if (noeud->filsg != NULL){
               tmp = recherche_noeud(noeud->filsg,car);
            }
		}
		return tmp;
	}
};

void ArbreB::supprimer_noeud(const char car)
{
    Noeud * tmp1 = recherche_noeud(racine,car);
    recherche_noeud
    if(tmp1 != NULL)
    {
        Noeud * tmp2 = NULL;
        Noeud * tmp3 = NULL;
        if(tmp1 == racine)
        {
            tmp2 = tmp1->filsg;
            tmp3 = tmp1->filsd;
            tmp1->filsg = NULL;
            tmp1->filsd = NULL;
            delete racine;
            racine = NULL;
            cout<<"racine :"<< racine <<endl;
            if(tmp2 != NULL && tmp3 != NULL && racine == NULL)
            {
                cout<<"still added the sons\n";
                ajout(racine,tmp3);
                ajout(racine,tmp2);
            }
        }
        else
        {


            if(tmp1->filsg != NULL)
                tmp2 = tmp1->filsg;

            if(tmp1->filsd != NULL)
                tmp3 = tmp1->filsd;

            delete tmp1;
            tmp1 = NULL;
            if(tmp2 != NULL)
                ajout(racine,tmp2);

            if(tmp3 != NULL)
                ajout(racine,tmp3);
        }

        taille--;
    }
};


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

ArbreB::~ArbreB()
{
    free_tree(racine);
};