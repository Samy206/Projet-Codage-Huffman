#ifndef LECTEUR_H
#define LECTEUR_H


class Lecteur
{
    private :
        string contenu;
        char * lettres;
        double * occurences;
        int taille;

    public :
        Lecteur(int = 0);
        Lecteur(Lecteur&);
        ~Lecteur();

        int getTaille(){return taille;};
        char * getLettres() {return lettres;};
        double * getOccurences() {return occurences;};
        setTaille(int size) {taille = size; };


        friend void operator=(lecteur&,Lecteur&);
}




#endif