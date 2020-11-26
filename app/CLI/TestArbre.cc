#include "ArbreB.h"
#include "Lecteur.h"
#include "Cryptage.h"
using namespace std;

int main(int argc, char* argv[])
{
    Lecteur l;
    ifstream mytext("Texte.txt");
    l.lecture(mytext);
    Cryptage cr(l);
    cr.creation_arbre();
}
