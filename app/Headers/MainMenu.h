#ifndef MAINMENU_H
#define MAINMENU_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QFrame>

class MainMenu : public QFrame {
private:
    QPushButton* bSuivant;
    QPushButton* bQuitter;
    QHBoxLayout* layout; // Box Layout pour le menu

public:
    MainMenu();
    ~MainMenu();
};


#endif // MAINMENU_H
