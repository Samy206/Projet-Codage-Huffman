#include "../../Headers/GUI/GetUserText.h"
#include "../../Headers/GUI/Context.h"

GetUserText::GetUserText()
{
    layout = new QGridLayout();
    setLayout(layout);

    // QLineEdit pour la saisie de texte
    input_txt = new QLineEdit();
    input_txt->setPlaceholderText("Saisissez ici le texte à encoder");
    input_txt->show();
    layout->addWidget(input_txt, 2, 0); // Deuxième de la grille de menu, à gauche

    // Bouton Valider
    bValider = new QPushButton("Valider", this);
    bValider->show();
    layout->addWidget(bValider, 2, 1);

    // Bouton Zoomer
    bZoomer = new QPushButton("Zoom", this);
    bZoomer->show();
    layout->addWidget(bZoomer, 2, 2);

    // Label pour le texte initial
    std::string tmp = "<b>Texte à coder : </b>"+ Context::getInstance().getText();
    wContenu = new QLabel(QString::fromStdString(tmp));
    wContenu->setWordWrap(true);
    wContenu->show();
    layout->addWidget(wContenu, 0, 0, 1, 3); // Premier de la grille de menu

    // Label pour le texte codé
    tmp = "<b>Texte codé : </b>" + Context::getInstance().getResult();
    wResult = new QLabel(QString::fromStdString(tmp));
    wResult->setWordWrap(true); // Retour à la ligne si le texte est trop long
    wResult->show();
    layout->addWidget(wResult, 1, 0, 1, 3); // Premier de la grille de menu

    // On connect le bouton Valider et la touche enter au slot setText pour actualiser le texte 
    connect(bValider, SIGNAL(clicked()), this, SLOT(setText()));
    connect(input_txt, SIGNAL(returnPressed()), this, SLOT(setText()));

    connect(&Context::getInstance(), SIGNAL(textEntered()), this, SLOT(textEntered()));

    connect(bZoomer, SIGNAL(clicked()), this, SLOT(zoomed()));
    
    ////

    // Bouton Quitter
    bQuitter = new QPushButton("Quitter", this);
    bQuitter->show();
    layout->addWidget(bQuitter, 2, 3);

    // On connect le bouton quitter au quitter de l'application Qt
    connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}

GetUserText::~GetUserText() { }

// Quand nouveau texte est entré, on l'envoie directement au setText du contexte
void GetUserText::setText() {
    if (!input_txt->text().isEmpty()) // En cas de Valider sans rien pour pas seg-fault
        Context::getInstance().setText(input_txt->text().toStdString());
}

// Signal reçu par le contexte après enregistrement du nouveau texte
void GetUserText::textEntered() {
    std::string tmp;
    // On actualise l'affichage du texte 
    tmp = "<b>Texte à coder : </b>" + Context::getInstance().getText();
    wContenu->setText(QString::fromStdString(tmp));
    
    // On actualise l'affichage du resultat
    tmp = "<b>Texte codé : </b>" + Context::getInstance().getResult();
    if( (tmp.length() > 130)  ) // Texte sans espace et plus long que 130 caractères
    {
        for(size_t i = 1; i <= tmp.length()/130; i++)  {
            int n = i * 130;
            tmp.insert(n, " ");
        }
    }
    wResult->setText(QString::fromStdString(tmp));

    // On clear la barre de saisie
    input_txt->setText("");
}

void GetUserText::zoomed() {
    Context::getInstance().changeZoom();
}