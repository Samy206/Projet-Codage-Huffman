#include "MainWindow.h"

#include <QApplication>

#include <QFile>
#include <QTextStream>

using namespace std;

int main(int argc, char* argv[])
{
    /* Qt application graphique */
    QApplication app(argc, argv);
    
    /* Modification du style d'affichage pour éviter les soucis de compatibilité couleurs entre les OS */
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
        printf("Unable to set stylesheet, file not found\n");
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }

    // Affichage graphique //
    MainWindow aff;
    aff.show();

    return app.exec();
}