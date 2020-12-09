#include "MainMenu.h"

MainMenu::MainMenu()
{
    layout = new QHBoxLayout();
    setLayout(layout);
    layout->setAlignment(Qt::AlignCenter);

    // input_txt = new QLineEdit();
    // input_txt->show();
    // layout->addWidget(input_txt);

    // bValider = new QPushButton("Valider", this);
    // bValider->show();
    // layout->addWidget(bValider);

    bQuitter = new QPushButton("Quitter", this);
    bQuitter->show();
    layout->addWidget(bQuitter);

    // On définit le style de Frame
    setFrameShape(Panel);
    // On définit l'ombre de frame
    setFrameShadow(Sunken);

    // connect(bGenerer, SIGNAL(clicked()), &Context::getInstance(), SLOT(genereArbre()));

    // connect(bDecomposeGauche, SIGNAL(clicked()), &Context::getInstance(), SLOT(decomposeGauche()));
    // connect(bDecomposeDroite, SIGNAL(clicked()), &Context::getInstance(), SLOT(decomposeDroite()));

    // connect(bFusion, SIGNAL(clicked()), &Context::getInstance(), SLOT(fusion()));

    // On connect le bouton quitter au quitter de l'application Qt
    connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    // // On connect le bouton Valider et la touche enter au slot textEntered pour actualiser le texte 
    // connect(input_txt, SIGNAL(returnPressed()), this, SLOT(textEntered()));
    // connect(bValider, SIGNAL(clicked()), this, SLOT(textEntered()));

};

MainMenu::~MainMenu() { }

// void MainMenu::textEntered() {
//     std::string tmp = input_txt->text().toStdString();
//     std::cout << tmp << std::endl;
// }
