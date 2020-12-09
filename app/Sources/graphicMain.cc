#include "MainWindow.h"

#include <QApplication>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
    /* Qt application graphique */
    QApplication app(argc, argv);

    // Affichage graphique //
    MainWindow aff;
    aff.show();

    return app.exec();
}