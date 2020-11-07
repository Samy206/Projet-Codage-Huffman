#include "ArbreB.h"
using namespace std;
#define COUNT 5

ArbreB::ArbreB(Sommet * sommets , int size)
{
    if(sommets != NULL)
    {
        taille = 0;
        for(int i = 0 ; i < size ; i++)
        {
            ajout(racine,sommets[i]);
        }
    }
    else
    {
        racine = NULL ;
        taille =  0 ;
    }
};

/*ArbreB::ArbreB(Noeud * noeuds, int size)
{
    if(noeuds != NULL)
    {
        taille = 0;
        for(int i = 0 ; i < size ; i++)
            ajout(&noeuds[i]);

    }

    else
    {
        racine = NULL ;
        taille =  0 ;
    }
};*/

void ArbreB::ajout(Noeud * existant,Sommet & sommet)
{
    int freqNew = sommet.getFreq();

    if(existant == NULL)
    {
        Noeud * nouveau = new Noeud;
        nouveau->actuel = sommet;
        nouveau->filsg = NULL;
        nouveau->filsd = NULL;
        existant = nouveau;
        taille++;
        cout<<"ajout racine taille :"<<taille<<endl;
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


void print_tree(Noeud *root, int space){
   if (root == NULL)
      return;
   print_tree(root->filsd, space+2);
   for (int i = 0; i < space; i++)
      cout<<"\t";
   cout<<" ("<<root->actuel.getLettre()<<" ; "<<root->actuel.getFreq()<<")"<<"\n";
   print_tree(root->filsg, space+2);
}

void ArbreB::free_tree(Noeud * root)
{
    if(root != NULL)
    {
        Noeud * tmpG = root->filsg ;
        Noeud * tmpD = root->filsd ;

        delete root;
        free_tree(tmpG);
        free_tree(tmpD);
    }
};

ArbreB::~ArbreB()
{
    free_tree(racine);
};