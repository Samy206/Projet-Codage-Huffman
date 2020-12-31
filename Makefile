OUT_DIR = target

final: # gui
	@cmake app/CMakeLists.txt
	@cd app; make
	./app/Partie3Cryptage

# Execution en CLI (Affichage sur terminal)
cli: compil
	./${OUT_DIR}/TestArbre

# Execution via Valgrind (debug)
debug: compil
	valgrind ./${OUT_DIR}/TestArbre

# Execution en GUI (Interface graphique Qt)
gui: 
	@qmake -makefile -o QMakefile app/Partie3Cryptage.pro 
	make -f QMakefile
	@./Partie3Cryptage

# Listing des fichiers
listing:
	doxygen Doxyfile
	firefox doc/html/files.html

# Compilation CLI
compil: ${OUT_DIR} ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o ${OUT_DIR}/Lecteur.o ${OUT_DIR}/Cryptage.o ${OUT_DIR}/Decryptage.o
	g++ -std=c++11 -Wall -g -o ${OUT_DIR}/TestArbre ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o ${OUT_DIR}/Lecteur.o ${OUT_DIR}/Cryptage.o ${OUT_DIR}/Decryptage.o


### Représentations intermédiaires

${OUT_DIR}/TestArbre.o: app/Sources/Partie2/TestArbre.cc app/Headers/Partie2/ArbreB.h app/Headers/Partie2/Sommet.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/TestArbre.o app/Sources/Partie2/TestArbre.cc

${OUT_DIR}/ArbreB.o: app/Sources/Partie2/ArbreB.cc app/Headers/Partie2/ArbreB.h app/Headers/Partie2/Sommet.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/ArbreB.o app/Sources/Partie2/ArbreB.cc

${OUT_DIR}/Sommet.o: app/Sources/Partie2/Sommet.cc app/Headers/Partie2/Sommet.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Sommet.o app/Sources/Partie2/Sommet.cc

${OUT_DIR}/Lecteur.o: app/Sources/Partie2/Lecteur.cc app/Headers/Partie2/Lecteur.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Lecteur.o app/Sources/Partie2/Lecteur.cc

${OUT_DIR}/Cryptage.o: app/Sources/Partie2/Cryptage.cc app/Headers/Partie2/Cryptage.h
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Cryptage.o app/Sources/Partie2/Cryptage.cc

${OUT_DIR}/Decryptage.o: app/Sources/Partie2/Decryptage.cc app/Headers/Partie2/Decryptage.h 
	g++ -std=c++11 -Wall -g -c -o ${OUT_DIR}/Decryptage.o app/Sources/Partie2/Decryptage.cc

# ======= #

### Utilitaires

${OUT_DIR}:
	mkdir -p ${OUT_DIR}

# @rm -f QMakefile
# @rm -f moc_*
clean:
	@rm -f qrc_style.cpp
	@rm -f app/Partie3Cryptage
	@rm -rf app/CMakeFiles
	@rm -rf app/Partie3Cryptage_autogen/
	@rm -f app/CMakeCache.txt
	@rm -f app/cmake_install.cmake
	@rm -f app/Makefile
	@rm -f *.o
	@rm -rf ${OUT_DIR}
	@rm -rf doc/
