#include "MainWindow.h"

#include <QApplication>

#include <QFile>
#include <QTextStream>


/**
 * @file graphicMain.cc
 * @brief Partie 2 : Constitue la fonction main lors de l'exécution graphique pour le Cryptage, charge le thème et lie lance la GUI.
 */
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