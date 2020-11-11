### Main

exec: TestArbre
	./TestArbre

TestArbre: TestArbre.o ArbreB.o Sommet.o
	g++ -Wall -g -o TestArbre TestArbre.o ArbreB.o Sommet.o


### Représentations intermédiaires


TestArbre.o: TestArbre.cc ArbreB.h Sommet.h
	g++ -Wall -g -c TestArbre.cc

ArbreB.o: ArbreB.cc ArbreB.h Sommet.h
	g++ -Wall -g -c ArbreB.cc

Sommet.o: Sommet.cc Sommet.h
	g++ -Wall -g -c Sommet.cc

# ======= #

### Utilitaires

clean:
	rm -f *.o
	rm -f TestArbre
