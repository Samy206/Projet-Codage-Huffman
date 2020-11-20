exec: compil
	./ProjetPartie1

compil:
	qmake -makefile -o QMakefile app/ProjetPartie1.pro
	make -f QMakefile

listing:
	doxygen Doxyfile
	firefox doc/html/files.html

clean:
	#make -f QMakefile clean
	rm -f *.o
	rm -f moc_predefs.h
	rm -f ProjetPartie1
	rm -f QMakefile
	rm -rf doc/
