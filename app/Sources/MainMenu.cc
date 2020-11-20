#include "MainMenu.h"
#include <QDebug>
MainMenu::MainMenu()
{
    layout = new QVBoxLayout();
    setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);

    bGenerer = new QPushButton("Générer un arbre", this);
    bGenerer->show();
    layout->addWidget(bGenerer);

    bCopie = new QPushButton("Construire par copie", this);
    bCopie->show();
    layout->addWidget(bCopie);

    bQuitter = new QPushButton("Quitter", this);
    bQuitter->show();
    layout->addWidget(bQuitter);

    // On définit le style de Frame
    setFrameShape(Panel);
    // On définit l'ombre de frame
    setFrameShadow(Sunken);

    // On connect le bouton quitter au quitter de l'application Qt
    connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    // connect(bGenerer, SIGNAL(clicked()), &Context::getInstance(), SLOT(genereArbre()));

    // connect(bReinitialiser, SIGNAL(clicked()), &Context::getInstance(), SLOT(resetNom()));
    // connect(bReinitialiser, SIGNAL(clicked()), &Context::getInstance(), SLOT(resetPrenom()));
};


MainMenu::~MainMenu() { }
