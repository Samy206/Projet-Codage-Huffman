#include "../../Headers/GUI/GetUserText.h"
#include "../../Headers/GUI/Context.h"

GetUserText::GetUserText()
{
    layout = new QGridLayout();
    setLayout(layout);

    // QLineEdit pour la saisie de texte
    input_txt = new QLineEdit(this);
    input_txt->setPlaceholderText("Saisissez ici le texte à encoder");
    input_txt->show();
    layout->addWidget(input_txt, 2, 0, 1, 3); // Troisieme de la grille de menu, à gauche

    // Bouton Zoomer
    bZoomer = new QPushButton("🔍", this);
    bZoomer->show();
    bZoomer->setMaximumWidth(40);
    layout->addWidget(bZoomer, 0, 2);

    // Label pour le texte initial
    std::string tmp = "<b>Texte à coder : </b>"+ Context::getInstance().getText();
    wContenu = new QLabel(QString::fromStdString(tmp));
    wContenu->setWordWrap(true);
    wContenu->show();
    layout->addWidget(wContenu, 0, 0, 1, 2); // Premier de la grille de menu

    // Label pour le texte codé
    tmp = "<b>Texte codé : </b>" + Context::getInstance().getResult();
    wResult = new QLabel(QString::fromStdString(tmp));
    wResult->setWordWrap(true); // Retour à la ligne si le texte est trop long
    wResult->show();
    layout->addWidget(wResult, 1, 0, 1, 3); // Deuxieme de la grille de menu

    // On connect le bouton Valider et la touche enter au slot setText pour actualiser le texte 
    // connect(bValider, SIGNAL(clicked()), this, SLOT(setText()));
    // connect(input_txt, SIGNAL(returnPressed()), this, SLOT(setText()));
    
    // Le signal est envoyé au slot setText() à chaque modification  pour actualiser le texte 
    connect(input_txt, SIGNAL(textChanged(QString)), this, SLOT(setText()));

    connect(&Context::getInstance(), SIGNAL(textEntered()), this, SLOT(textEntered()));
    connect(&Context::getInstance(), SIGNAL(textDecrypted()), this, SLOT(textDecrypted()));

    connect(bZoomer, SIGNAL(clicked()), this, SLOT(zoomed()));

    //// PARTIE 3 ////

    wP3 = new QLabel(QString::fromStdString("<b>Partie 3 :</b> Décryptage d'un texte à partir de l'arbre binaire de cryptage défini ci-dessus"));
    wP3->setWordWrap(true); // Retour à la ligne si le texte est trop long
    wP3->show();
    layout->addWidget(wP3, 3, 0, 1, 3); // Quatrieme de la grille de menu 

    // QLineEdit pour la saisie de crypted text
    input_cry = new QLineEdit(this);
    // QRegularExpression regex("^[0-1]*$");
    // QValidator *validator = new QRegularExpressionValidator(regex, this);
    // input_cry->setValidator(validator);
    input_cry->setPlaceholderText("Saisissez ici le texte à décoder");
    input_cry->show();
    layout->addWidget(input_cry, 4, 0, 1, 3); // Cinquieme de la grille de menu à gauche

    connect(input_cry, SIGNAL(textChanged(QString)), this, SLOT(checkChange(const QString&)));

    decode_result = new QLabel();
    decode_result->setWordWrap(true); // Retour à la ligne si le texte est trop long
    decode_result->show();
    layout->addWidget(decode_result, 5, 0, 1, 3); // Sixieme de la grille de menu 
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
    // input_txt->setText("");
}

void GetUserText::zoomed()  {
    Context::getInstance().changeZoom();
}

void GetUserText::checkChange(const QString & text)  {
    QRegularExpression regex("^[0-1]+$");
    QRegularExpressionMatch match = regex.match(text);
    if (!match.hasMatch()) 
        decode_result->setText("<font color='red'>L'expression à décoder doit contenir uniquement des 0 ou des 1.</font>");
    else  {
        decode_result->setText(text);
        
        // Envoyer au contexte pour décryptage  
        Context::getInstance().decrypteText(text.toStdString());
    }
}

void GetUserText::textDecrypted()  {
    switch (Context::getInstance().getDecrypteStatus())  {
        case -1:
            // Erreur lors de l'exécution de l'algorithme de décryptage, l'arbre ne correspond donc pas au texte 
            decode_result->setText("<font color='red'>Ce texte ne peut être décodé avec l'arbre binaire de cryptage défini.</font>");
            break;
        case 1:
            // Le texte n'a pas été codé par la partie 2, mais l'arbre fourni peut effectivement servir à décoder ce texte
            decode_result->setText("<font color='yellow'>Ce texte n'a pas été encodé par l'arbre binaire de cryptage défini mais il peut tout de même servir à le décoder :</font><br><b>Texte décodé : " + QString::fromStdString(Context::getInstance().getDecrypted()) + "</b></br>");
            break;
        case 2:
            decode_result->setText("<font color='green'>Ce texte a pu être été codé par l'arbre binaire de cryptage défini car les codes et occurences correspondent :</font><br><b>Texte décodé : " + QString::fromStdString(Context::getInstance().getDecrypted()) + "</b><br><i>On ne peut toutefois pas s'assurer que l'arbre binaire de cryptage défini a permis d'encoder ce texte.</i>");
            break;
    }
}
