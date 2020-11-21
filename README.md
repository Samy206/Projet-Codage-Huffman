# Cryptage et décryptage : Partie 1
Samy BOUMALI & Amine ATEK

## Contenu de l'archive

Cette archive contient le répertoire `app/` contenant les sources et headers du programme CLI et Graphique ; une mécanisme de construction (`Makefile`), un `Doxyfile` utile à la génération d'une documentation faisant office de listing commenté, d'un compte rendu `CR_Boumali_Atek.pdf` ainsi que de ce présent fichier `README.md`. 


## Commandes et utilisation

1. Exécuter la partie 1 sous interface graphique :
```
 make 
```

2. Listing des classes :
```
make listing
```
> Nécessite le programme Doxygen. Un répertoire `doc/` sera créé avec le listing en `html`. Le Makefile tentera par défaut d'ouvrir la documentation avec `firefox` mais cela pourrait ne pas fonctionner si vous n'avez pas le programme. Je vous recommande donc d'ouvrir le fichier `doc/html/files.html` avec votre navigateur habituel pour accéder au listing détaillé et commenté des classes.

3. Exécuter en mode CLI (affichage sur terminal, permet de mieux visualiser les tests effectuées)
```
make cli
```

4. Exécuter en mode debug (Valgrind et mem-check)
```
make debug
```

## Précisions

1. La compilation graphique nécessite d'avoir `qmake`, outil de compilation pour les projet Qt.

2. L'affichage de l'arbre est assez particulier :
- Deux fils d'un même sommets sont liés par un trait vertical noir.
- Un fils est lié à son père par un trait angulaire bleu.
- L'arbre est affiché de la gauche vers la droite à raison d'un sommet par ligne en abscisses.
