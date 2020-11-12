
OUT_DIR = target

### Main

exec: compil
	./${OUT_DIR}/TestArbre

debug: compil
	valgrind ./${OUT_DIR}/TestArbre


compil: ${OUT_DIR} ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o
	g++ -Wall -g -o ${OUT_DIR}/TestArbre ${OUT_DIR}/TestArbre.o ${OUT_DIR}/ArbreB.o ${OUT_DIR}/Sommet.o


### Représentations intermédiaires

${OUT_DIR}/TestArbre.o: src/TestArbre.cc headers/ArbreB.h headers/Sommet.h
	g++ -Wall -g -c -o ${OUT_DIR}/TestArbre.o src/TestArbre.cc

${OUT_DIR}/ArbreB.o: src/ArbreB.cc headers/ArbreB.h headers/Sommet.h
	g++ -Wall -g -c -o ${OUT_DIR}/ArbreB.o src/ArbreB.cc

${OUT_DIR}/Sommet.o: src/Sommet.cc headers/Sommet.h
	g++ -Wall -g -c -o ${OUT_DIR}/Sommet.o src/Sommet.cc

# ======= #

### Utilitaires

${OUT_DIR}:
	mkdir -p ${OUT_DIR}

clean:
	rm -f ${OUT_DIR}/*.o
	rm -f ${OUT_DIR}/TestArbre
	rm -r ${OUT_DIR}
