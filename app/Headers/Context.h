#pragma once

#include "CLI/Sommet.h"
#include "CLI/ArbreB.h"
#include "CLI/Lecteur.h"
#include "CLI/Cryptage.h"
#include <QtCore/QObject>

/**
 * @brief Contexte principal de l'application
 * 
 * Permet de gérer l'arbre courant, les textes en entrées et sorties, ainsi que quelques options globales.
 */
class Context : public QObject {

    Q_OBJECT

private:
    std::string txt_to_crypt; // Texte initial à crypter
    std::string crypted_text; // Résultat crypté
    int zoom = 0; // Permet de zoomer lors de l'affichage
    ArbreB arbre_courant;

    /**
     * @brief Constructeur de classe déclaré private, le getter d'instance sera public
     */
    Context(); 

public:

    /**
     * @brief Classe singleton: le constructeur est private, on un un getter d'instance à la place.
     * 
     * @return Context& 
     */
    static Context& getInstance() {
        static Context singleton;
        return singleton;
    }

    // Pour s'assurer que la classe reste en Singleton
    Context(Context const&) = delete;
    Context& operator=(Context const&) = delete;

    // Getters:

    /**
     * @brief Getter pour l'arbre contexte @return ArbreB*
     */
    ArbreB* getArbre() { return &arbre_courant; };

    /**
     * @brief Getter pour l'option Zoom du contexte @return int
     */
    int getZoom() { return zoom; };

    /**
     * @brief Getter de texte en entrée @return std::string
     */
    std::string getText() { return txt_to_crypt; };
    /**
     * @brief Getter de texte crypté (résultat) @return std::string
     */
    std::string getResult() { return crypted_text; };

    // Setters:

    /**
     * @brief Setter pour l'arbre courant du contexte
     *
     * @param e_arbre
     */
    void setArbre(ArbreB arbre);

    /**
     * @brief Setter pour modifier le texte en entrée à partir d'un fichier (après action de l'utilisateur)
     * 
     * @param file
     */
    void setText(std::ifstream & file);

    /**
     * @brief Setter pour modifier le texte en entrée à partir d'une string (après action de l'utilisateur)
     * 
     * On émet le signal textEntered() pour activer la suite du processus d'actualisation
     * @param string
     */
    void setText(std::string const& val);

    /**
     * @brief Setter pour modifier le paramètre Zoom
     */
    void changeZoom(); 

public slots:


signals:
    /**
     * @brief Emitted when the arbre changed
     *
     */
   void arbreChanged();

   void textEntered();
};