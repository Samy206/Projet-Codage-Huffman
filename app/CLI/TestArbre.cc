#include "ArbreB.h"
#include "Lecteur.h"
using namespace std;

int main(int argc, char* argv[])
{
    Lecteur l;
    ifstream myfile ("Texte.txt");
    l.lecture(myfile);
    cout<<l;
}
