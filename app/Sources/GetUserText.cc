#include "GetUserText.h"
#include "Context.h"

GetUserText::GetUserText()
{
    layout = new QGridLayout();
    setLayout(layout);
    // layout->setAlignment(Qt::AlignCenter);

    // On définit le style et l'ombrage de Frame
    setFrameShape(Panel);
    setFrameShadow(Sunken);

    // QLineEdit pour la saisie de texte
    input_txt = new QLineEdit();
    input_txt->show();
    layout->addWidget(input_txt, 2, 0);

    // Bouton Valider
    bValider = new QPushButton("Valider", this);
    bValider->show();
    layout->addWidget(bValider, 2, 1);

    std::string tmp = "Text: " + Context::getInstance().getTexte();
    wContenu = new QLabel(QString::fromStdString(tmp));
    wContenu->show();
    layout->addWidget(wContenu, 0, 0, 1, 3);

    // On connect le bouton Valider et la touche enter au slot setText pour actualiser le texte 
    connect(bValider, SIGNAL(clicked()), this, SLOT(setText()));
    connect(input_txt, SIGNAL(returnPressed()), this, SLOT(setText()));

    connect(&Context::getInstance(), SIGNAL(textEntered()), this, SLOT(textEntered()));
}

GetUserText::~GetUserText() { }

// Quand nouveau texte est entré, on l'envoie directement au setText du contexte
void GetUserText::setText() {
    Context::getInstance().setText(input_txt->text().toStdString());
}

// Signal reçu par le contexte après enregistrement du nouveau texte
void GetUserText::textEntered() {
    // On actualise l'affichage du texte 
    std::string tmp = "Text: " + Context::getInstance().getTexte();
    wContenu->setText(QString::fromStdString(tmp));
    // On clear la barre de saisie
    input_txt->setText("");
}
