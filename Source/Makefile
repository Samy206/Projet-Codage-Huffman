### Main

exec: target/TestArbre
	./target/TestArbre


target/TestArbre: target/TestArbre.o target/ArbreB.o target/Sommet.o
	g++ -Wall -g -o target/TestArbre target/TestArbre.o target/ArbreB.o target/Sommet.o


### Représentations intermédiaires


target/TestArbre.o: src/TestArbre.cc headers/ArbreB.h headers/Sommet.h
	g++ -Wall -g -c -o target/TestArbre.o src/TestArbre.cc

target/ArbreB.o: src/ArbreB.cc headers/ArbreB.h headers/Sommet.h
	g++ -Wall -g -c -o target/ArbreB.o src/ArbreB.cc

target/Sommet.o: src/Sommet.cc headers/Sommet.h
	g++ -Wall -g -c -o target/Sommet.o src/Sommet.cc

# ======= #

### Utilitaires

clean:
	rm -f target/*.o
	rm -f target/TestArbre
