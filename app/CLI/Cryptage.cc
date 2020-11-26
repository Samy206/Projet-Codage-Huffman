#include "Cryptage.h"
using namespace std;

Cryptage::Cryptage(Lecteur& l)
{
    lecteur = l;
    sommets = NULL;
    nb_sommets = 0;
};

Cryptage::~Cryptage()
{
    ;
};



void fusion(Sommet tableau[],int deb1,int fin1,int fin2)
{

    int deb2=fin1+1;
    int compt1=deb1;
    int compt2=deb2;
    int i;

    Sommet *table1 =new Sommet[fin1-deb1+1];;


    //on recopie les éléments du début du tableau
    for(i=deb1;i<=fin1;i++)
    {
        table1[i-deb1]=tableau[i];
    }

    for(i=deb1;i<=fin2;i++)
    {
        if (compt1==deb2) //c'est que tous les éléments du premier tableau ont été utilisés
            break; //tous les éléments ont donc été classés

        else if (compt2==(fin2+1)) //c'est que tous les éléments du second tableau ont été utilisés
        {
            tableau[i]=table1[compt1-deb1]; //on ajoute les éléments restants du premier tableau
            compt1++;
        }
        else if (table1[compt1-deb1].getFreq() > tableau[compt2].getFreq())
        {
            tableau[i]=table1[compt1-deb1]; //on ajoute un élément du premier tableau
            compt1++;
        }
        else
        {
            tableau[i]=tableau[compt2]; //on ajoute un élément du second tableau
            compt2++;
        }
    }
    delete []table1;
}


void tri_fusion_bis(Sommet tableau[],int deb,int fin)
{
    if (deb!=fin)
    {
        int milieu=(fin+deb)/2;
        tri_fusion_bis(tableau,deb,milieu);
        tri_fusion_bis(tableau,milieu+1,fin);
        fusion(tableau,deb,milieu,fin);
    }
}

void tri_fusion(Sommet tableau[],int longueur)
{
   if (longueur>0)
      tri_fusion_bis(tableau,0,longueur-1);
}

void Cryptage::creation_arbre()
{
    sommets = new Sommet[26];

    vector<float> tmp2 = lecteur.getOccurences();
    vector<char> tmp1 = lecteur.getLettres();

    for(int i = 0 ; i < 26 ; i++)
    {
        if(tmp2[i] != 0.0)
        {
            Sommet * tmp = new Sommet(tmp1[i],tmp2[i]);
            sommets[nb_sommets] = *tmp;
            nb_sommets++;
            delete tmp;
        }
    }

    tri_fusion(sommets,nb_sommets);
    int indiceA, indiceB;
    Sommet tmp;
    Sommet * Somtmp1;
    cout<<"texte : "<<lecteur.getContenu()<<endl;
    while(nb_sommets > 2)
    {
        indiceA = nb_sommets - 1;
        indiceB = nb_sommets - 2;
        tmp = sommets[indiceB];
        Somtmp1 = new Sommet(' ',sommets[indiceB].getFreq()+sommets[indiceA].getFreq());
        sommets[indiceB] = *Somtmp1;

        if(tmp.getFreq() > sommets[indiceA].getFreq())
        {
            sommets[indiceB].setFilsD(&tmp);
            sommets[indiceB].setFilsG(&sommets[indiceA]);
        }
        else
        {
            sommets[indiceB].setFilsG(&tmp);
            sommets[indiceB].setFilsD(&sommets[indiceA]);
        }
        nb_sommets --;
        tri_fusion(sommets,nb_sommets);
        delete Somtmp1;
    }

    arbre.ajout(arbre.getRacine(),&sommets[0]);
    arbre.ajout(arbre.getRacine(),&sommets[1]);

    cout<<"taille arbre : "<<arbre.getTaille()<<endl;
    cout<<arbre<<endl;

};

