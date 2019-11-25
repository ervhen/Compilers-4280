all: comp virtmach
comp: main.cpp parser.cpp scanner.cpp testTree.cpp
	g++ -g -std=c++11 -o comp comp.cpp main.cpp parser.cpp staticsam.cpp scanner.cpp testTree.cpp

virtmach: assemblyVirtMach.c
	cc -g -o virtMach assemblyVirtMach.c	
clean:
	rm -f $(OBJ) comp *.sp19 *.asm



