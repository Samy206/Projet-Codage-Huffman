#include "ArbreB.cc"
#include "Sommet.cc"
using namespace std;

int main()
{
    const char c1 = 'a';
    const char c2 = 'b';
    const char c3 = 'c';

    const int i1 = 10;
    const int i2 = 6;
    const int i3 = 3;

    Sommet first(c1,i1), second(c2,i2), third(c3,i3);

    Sommet table[3];
    table[0] = first;
    table[1] = second;
    table[2] = third;

    ArbreB arbre(table,3);


}


