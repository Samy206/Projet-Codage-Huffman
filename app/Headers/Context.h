#pragma once

#include "CLI/Sommet.h"
#include "CLI/ArbreB.h"
#include "CLI/Lecteur.h"
#include "CLI/Cryptage.h"
#include <QtCore/QObject>

/**
 * @brief Contexte principale de l'application
 * 
 */
class Context : public QObject {

    Q_OBJECT

private:
    std::string txt_to_crypt; // Texte initial à crypter
    std::string crypted_text; // Résultat crypté
    ArbreB arbre_courant;

    Context() {
        std::ifstream myfile("Texte.txt");
        std::stringstream strStream;
        std::string contenu;
        if(myfile.is_open()) {
            strStream << myfile.rdbuf(); //read the file
            contenu = strStream.str(); //str holds the content of the file
        }
        myfile.close();

        setText(contenu);
    }

public:

    /**
     * @brief Classe singleton: le constructeur est private, on un un getter d'instance à la place.
     * 
     * @return Context& 
     */
    static Context& getInstance()
    {
        static Context singleton;
        return singleton;
    }

    // Pour s'assurer que la classe reste en Singleton
    Context(Context const&) = delete;
    Context& operator=(Context const&) = delete;

    /**
     * @brief Setter pour l'arbre contexte
     *
     * @param e_arbre
     */
    void setArbre(ArbreB arbre) {
        // if (arbre_courant.getTaille() != 0) 
        //     arbre_courant.free_tree(arbre_courant.getRacine());
        
        // arbre_courant.ajout(arbre);

        arbre_courant = arbre;
        std::cout << "Done !" << std::endl;
        emit arbreChanged();
    }


    /**
     * @brief Getter pour l'arbre contexte
     *
     * @return ArbreB
     */
    ArbreB* getArbre() { return &arbre_courant; };

    /**
     * @brief Getter pour le texte en entrée
     * 
     * @return std::string texte
     */ 
    std::string getText() { return txt_to_crypt; };

    std::string getResult() { return crypted_text; };

    // Nouveau texte reçu, on emet le signal textEntered pour actualiser l'affichage texte
    void setText(std::string const& val)
    {
        txt_to_crypt = val;
        std::cout << "Nouveau texte: " << val << std::endl;

        Lecteur l;
        l.lecture(val);
        std::cout << "Text: " << l.getContenu() << std::endl;

        // Faire un nouvel arbre
        Cryptage cr(l);
        cr.construction_arbre();
        crypted_text = cr.encodage();

        emit textEntered();
        
        std::cout << cr.get_arbre() << std::endl; // Ok !

        // Vider l'arbre courant et set l'arbre

        setArbre(cr.get_arbre());
        
        // Le mettre dans arbre_courant
    }


public slots:
    /**
     * @brief Re-génère un arbre binaire étiqueté aléatoire
     *
     */
    void genereArbre() {
        // setArbre(0);
    }

    void decomposeGauche() {
        // setArbre(1);
    }
    void decomposeDroite() {
        // setArbre(2);
    }
    void fusion() {
        // setArbre(4);
    }


signals:
    /**
     * @brief Emitted when the arbre changed
     *
     */
   void arbreChanged();

   void textEntered();
};