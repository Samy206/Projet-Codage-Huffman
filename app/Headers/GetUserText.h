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


class GetUserText : public QFrame {
    Q_OBJECT
private:
    QPushButton* bValider;
    QLineEdit *input_txt;
    QGridLayout* layout; // Grid Layout pour le menu

    QLabel* wContenu;

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

    void textEntered();

signals:

};


#endif // GETUSERTEXT__H
