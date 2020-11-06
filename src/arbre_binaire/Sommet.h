#ifndef SOMMET_H
#define SOMMET_H

class Sommet
{
    protected :
        char lettre;
        int freq;

    public :
        Sommet(const char =' ',const int = 0);
        Sommet(Sommet &);
        ~Sommet();

        char getLettre() {return lettre;};
        int getFreq() {return freq;};
        void setFreq(const int part) {freq = part;};

        void operator=(Sommet &);
        friend Sommet operator+(Sommet & ,Sommet &);
        friend std::ostream& operator<<(std::ostream&,Sommet&);
};


#endif