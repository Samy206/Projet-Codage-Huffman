#include "ArbreB.h"
#include <vector>
#include "Lecteur.h"
#include "Cryptage.h"
using namespace std;

int main(int argc, char* argv[]) {
    Lecteur l;
    ifstream mytext("app/text.txt");
    l.lecture(mytext);
    std::cout << "Text: " << l.getContenu() << endl;
    Cryptage cr(l);
    cr.construction_arbre();

    std::cout << cr.get_arbre() << std::endl;

    cr.encodage();
}
