#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ArbreB.h"
#include "MainMenu.h"
#include "DessineArbre.h"

#include <QMainWindow>
#include <QScrollArea>
#include <QLabel>

class MainWindow : public QWidget {
private :
    MainMenu* wMenu;
    QGridLayout* layout; // Grid Layout pour l'affichage

    QScrollArea* wZoneArbre;

    DessineArbre* dessin;

public :
    MainWindow(ArbreB);
    ~MainWindow();
};

#endif // MAINWINDOW_H
