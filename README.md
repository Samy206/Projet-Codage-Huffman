# Cryptage et décryptage : Partie 1
Samy BOUMALI & Amine ATEK

## Contenu de l'archive

Cette archive contient le répertoire `app/` contenant les sources et headers du programme CLI et Graphique ; un mécanisme de construction (`Makefile`) dont les commandes sont répertoriés après ce texte, un `Doxyfile` utile à la génération d'une documentation faisant office de listing commenté, d'un compte rendu `CR_Boumali_Atek.pdf`, du répertoire `qdarkstyle` permettant la personnalisation de l'affichage graphique ainsi que de ce présent fichier `README.md`. 

## Commandes et utilisation

1. Exécuter la partie 2 (sous interface graphique) :
```
 make 
```

2. Listing des classes :
```
make listing
```
> Nécessite le programme Doxygen. Un répertoire `doc/` sera créé avec le listing en `html`. Le Makefile tentera par défaut d'ouvrir la documentation avec `firefox` mais cela pourrait ne pas fonctionner si vous n'avez pas le programme. Je vous recommande donc d'ouvrir le fichier `doc/html/files.html` avec votre navigateur habituel pour accéder au listing détaillé et commenté des classes.

3. Exécuter en mode CLI (affichage sur terminal sans faire intervenir les classes Qt)
```
make cli
```

4. Exécuter en mode debug (Valgrind et mem-check)
```
make debug
```

## Précisions

1. La compilation graphique nécessite d'avoir `qmake`, outil de compilation pour les projet Qt.

