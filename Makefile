comp: main.o fsa_table.o scanner.o parser.o treePrint.o semstack.o testSemStack.o
	g++ main.o scanner.o fsa_table.o parser.o treePrint.o semstack.o testSemStack.o -o comp
main.o: main.cpp token.h fsa_table.h scanner.h parser.h node.h treePrint.h semstack.h
	g++ -c main.cpp
scanner.o: scanner.cpp scanner.h token.h fsa_table.h
	g++ -c scanner.cpp
fsa_table.o: fsa_table.cpp fsa_table.h
	g++ -c fsa_table.cpp
parser.o: parser.cpp parser.h scanner.h token.h node.h
	g++ -c parser.cpp
semstack.o: semstack.cpp semstack.h
	g++ -c semstack.cpp
treePrint.o: treePrint.cpp treePrint.h node.h
	g++ -c treePrint.cpp
testSemStack.o: testSemStack.cpp testSemStack.h semstack.h node.h token.h parser.h
	g++ -c testSemStack.cpp
clean: 
	rm comp *.o
