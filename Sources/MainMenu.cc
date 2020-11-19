#include "MainMenu.h"

MainMenu::MainMenu()
{
    layout = new QHBoxLayout();
    setLayout(layout);
    layout->setAlignment(Qt::AlignBottom);

    bQuitter = new QPushButton("Quitter", this);
    bQuitter->show();
    layout->addWidget(bQuitter);

    bSuivant = new QPushButton("Arbre suivant", this);
    bSuivant->show();
    layout->addWidget(bSuivant);

    // On définit le style de Frame
    setFrameShape(Panel);
    // On définit l'ombre de frame
    setFrameShadow(Sunken);
    setMaximumHeight(75);

    // On connect le bouton quitter au quitter de l'application Qt
    connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    // connect(bReinitialiser, SIGNAL(clicked()), &Context::getInstance(), SLOT(resetNom()));
    // connect(bReinitialiser, SIGNAL(clicked()), &Context::getInstance(), SLOT(resetPrenom()));
};


MainMenu::~MainMenu() { }
