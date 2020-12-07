#include "ArbreB.h"
#include <vector>
#include "Lecteur.h"
#include "Cryptage.h"
using namespace std;

int main(int argc, char* argv[]) {
    Lecteur l;
    ifstream mytext("Texte.txt");
    l.lecture(mytext);
    std::cout << "Text: " << l.getContenu() << endl;
    Cryptage cr(l);
    cr.construction_arbre();
    cr.encodage();

    /*Sommet som1('c',12,1);

    Sommet som2('a',12,1);
    Sommet som3('b',12,1);
    Sommet som5('k',12,1);
    Sommet som6('l',12,1);
    som2.setFilsG(&som5);
    som2.setFilsD(&som6);
    som1.setFilsG(&som2);
    som1.setFilsD(&som3);
    Sommet som4;
    som4 = som1;
    ArbreB arbre;
    arbre.ajout(arbre.getRacine(),&som4);
    cout<<"arbre :\n"<<arbre<<endl<<endl;
    ArbreB arbre1;
    som4 = som6;
    arbre1.ajout(arbre1.getRacine(),&som4);
    cout<<"arbre1 :\n"<<arbre<<endl<<endl;*/



}
