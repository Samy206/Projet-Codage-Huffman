#include "Context.h"

/**
 * @brief Constructeur de classe déclaré private, le getter d'instance sera public
 */
Context::Context()  {
    // On initie le contexte avec le texte fourni initialement
    // A_DEAD_DAD_CEDED_A_BAD_BABE_A_BEADED_ABACA_BED
    std::ifstream myfile("Texte.txt");
    setText(myfile);
}

// Setters:

/**
 * @brief Setter pour l'arbre courant du contexte
 *
 * @param e_arbre
 */
void Context::setArbre(ArbreB arbre) {
    // if (arbre_courant.getTaille() != 0) 
    //     arbre_courant.free_tree(arbre_courant.getRacine());
    
    // arbre_courant.ajout(arbre);

    arbre_courant = arbre;
    std::cout << "Done !" << std::endl;
    emit arbreChanged();
}

/**
 * @brief Setter pour modifier le texte en entrée à partir d'un fichier (après action de l'utilisateur)
 * 
 * @param file
 */
void Context::setText(std::ifstream & file)  {
    // On transforme le fichier en string
    std::stringstream strStream;
    std::string contenu;
    if(file.is_open()) {
        strStream << file.rdbuf(); //read the file
        contenu = strStream.str(); //str holds the content of the file
    }
    file.close();
    // On appelle le setter qui utilise la String
    setText(contenu);
}

/**
 * @brief Setter pour modifier le texte en entrée à partir d'une string (après action de l'utilisateur)
 * 
 * On émet le signal textEntered() pour activer la suite du processus d'actualisation
 * @param string
 */
void Context::setText(std::string const& val)  {
    txt_to_crypt = val;
    std::cout << "Nouveau texte: " << val << std::endl;

    Lecteur l;
    l.lecture(val);
    std::cout << "Text: " << l.getContenu() << std::endl;

    // Faire un nouvel arbre
    Cryptage cr(l);
    cr.construction_arbre();
    crypted_text = cr.encodage();

    // Signal émis l'actualisation de l'affichage texte
    emit textEntered();
    
    // PRINT à RETIRER une FOIS QUE PLUS DE BUGS
    std::cout << cr.get_arbre() << std::endl; // Ok !

    // Vider l'arbre courant et set l'arbre

    setArbre(cr.get_arbre());
    
    // Le mettre dans arbre_courant
}

/**
 * @brief Setter pour modifier le paramètre Zoom
 */
void Context::changeZoom()  { 
    zoom = 3-zoom; 
    emit arbreChanged(); 
};
