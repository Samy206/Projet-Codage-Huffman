#ifndef GETUSERTEXT_H
#define GETUSERTEXT_H

#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <iostream>

#include <QDebug>
#include <QRegularExpression>
#include <QValidator>

// #include "../Partie2/Decryptage.h"

/**
 * @file GetUserText.h
 * @brief Menu principal des interactions avec l'utilisateur : comprend une barre de saisie, trois boutons et 
 *        deux labels pour l'affichage du texte à codé et du texte codé.
 */
class GetUserText : public QFrame {
    Q_OBJECT
private:
    QPushButton *bZoomer;

    QLineEdit *input_txt;
    QGridLayout* layout; // Grid Layout pour la saisie + quit

    QLabel* wContenu;
    QLabel* wResult;

    // Partie 3 :
    QLabel* wP3; // Titre pour séparation
    QLineEdit *input_cry; // Input pour le texte crypté
    QLabel *decode_result; // Résultat pour le décryptage

public:
    /**
     * Constructeur par défaut
     */ 
    GetUserText();

    /**
     * Destructeur de classe
     */ 
    ~GetUserText();


public slots:
    void setText();

    void zoomed();

    void textEntered();

    void checkChange(const QString &);

    void textDecrypted();

signals:

};


#endif // GETUSERTEXT__H
