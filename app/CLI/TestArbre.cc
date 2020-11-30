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
}
