#include "MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(ArbreB arbre) {
    layout = new QGridLayout();
    setLayout(layout);

    qDebug() << "App path : " << qApp->applicationDirPath();

    // Top image banner
    QLabel  *label_img  = new QLabel(this);
    QPixmap *pixmap_img = new QPixmap("../banner.jpg");
    QRect rect(0, 0, 700, 100);
    QPixmap cropped = pixmap_img->copy(rect); // Rogner l'image à la taille 700x100
    label_img->setPixmap(cropped.scaled(700, 100, Qt::KeepAspectRatio));
    // label_img->setFixedSize(700, 100);
    label_img->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_img, 0, 0);

    // Main menu (Bottom)
    wMenu = new MainMenu();
    wMenu->show();
    layout->addWidget(wMenu, 2, 0);

    // Zone de dessin (Mid)
    dessin = new DessineArbre(arbre);

    wZoneArbre = new QScrollArea();
    wZoneArbre->setWidget(dessin);
    wZoneArbre->show();
    wZoneArbre->setMinimumSize(700, 500);
    layout->addWidget(wZoneArbre, 1, 0);
}

MainWindow::~MainWindow() { }
