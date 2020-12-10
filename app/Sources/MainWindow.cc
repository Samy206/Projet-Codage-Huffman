#include "MainWindow.h"


MainWindow::MainWindow() {
    layout = new QGridLayout();
    setLayout(layout);

    // Top image banner
    /*
    QLabel  *label_img  = new QLabel(this);
    QPixmap *pixmap_img = new QPixmap("banner.jpeg");
    QRect rect(0, 0, 870, 100);
    QPixmap cropped = pixmap_img->copy(rect); // Rogner l'image à la taille 700x100
    label_img->setPixmap(cropped.scaled(870, 100, Qt::KeepAspectRatio));
    // label_img->setFixedSize(700, 100);
    label_img->setAlignment(Qt::AlignCenter);
    layout->addWidget(label_img, 0, 0, 1, 2);
    */

    // Zone d'intéraction avec l'utilisateur (barre de saisie et boutons)
    wInput = new GetUserText();
    wInput->show();
    // wInput->setMaximumWidth(2000);
    layout->addWidget(wInput, 2, 0, 1, 2);

    // Zone résultats
    resultats = new DisplayResults();

    wZoneResultats = new QScrollArea(this);
    wZoneResultats->setWidget(resultats);
    wZoneResultats->show();
    wZoneResultats->setMaximumWidth(260);
    layout->addWidget(wZoneResultats, 0, 1);

    // Zone de dessin (Mid)
    dessin = new DessineArbre();

    wZoneArbre = new QScrollArea(this);
    wZoneArbre->setWidget(dessin);
    wZoneArbre->show();
    // wZoneArbre->setMinimumSize(800, 300);
    layout->addWidget(wZoneArbre, 0, 0);
}

MainWindow::~MainWindow() { }
