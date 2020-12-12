OUT_DIR = target

final: gui

# Execution en CLI (Affichage sur terminal)
cli: compil
	./${OUT_DIR}/TestArbre

# Execution via Valgrind (debug)
debug: compil
	valgrind ./${OUT_DIR}/TestArbre

# Execution en GUI (Interface graphique Qt)
gui: 
	qmake -makefile -o QMakefile app/Partie2Cryptage.pro
	make -f QMakefile
	./Partie2Cryptage

# Listing des fichiers
listing:
	doxygen Doxyfile
	firefox doc/html/files.html

# Compilation CLI
compil: ${OUT_DIR} ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o ${OUT_DIR}/Lecteur.o ${OUT_DIR}/Cryptage.o
	g++ -Wall -g -o ${OUT_DIR}/TestArbre ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o ${OUT_DIR}/Lecteur.o ${OUT_DIR}/Cryptage.o


### Représentations intermédiaires

${OUT_DIR}/TestArbre.o: app/Sources/TestArbre.cc app/Headers/ArbreB.h app/Headers/Sommet.h
	g++ -Wall -g -c -o ${OUT_DIR}/TestArbre.o app/Sources/TestArbre.cc

${OUT_DIR}/ArbreB.o: app/Sources/ArbreB.cc app/Headers/ArbreB.h app/Headers/Sommet.h
	g++ -Wall -g -c -o ${OUT_DIR}/ArbreB.o app/Sources/ArbreB.cc

${OUT_DIR}/Sommet.o: app/Sources/Sommet.cc app/Headers/Sommet.h
	g++ -Wall -g -c -o ${OUT_DIR}/Sommet.o app/Sources/Sommet.cc

${OUT_DIR}/Lecteur.o: app/Sources/Lecteur.cc app/Headers/Lecteur.h
	g++ -Wall -g -c -o ${OUT_DIR}/Lecteur.o app/Sources/Lecteur.cc

${OUT_DIR}/Cryptage.o: app/Sources/Cryptage.cc app/Headers/Cryptage.h
	g++ -Wall -g -c -o ${OUT_DIR}/Cryptage.o app/Sources/Cryptage.cc

# ======= #

### Utilitaires

${OUT_DIR}:
	mkdir -p ${OUT_DIR}

clean:
	rm -f *.o
	rm -f qrc_style.cpp
	rm -f Partie2Cryptage
	rm -f QMakefile
	rm -rf ${OUT_DIR}
	rm -rf doc/
	rm -f moc_*
