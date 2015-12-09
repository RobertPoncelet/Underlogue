underlogue.tab.c underlogue.tab.h: underlogue.y
	bison -d underlogue.y

lex.yy.c: underlogue.lex underlogue.tab.h
	flex underlogue.lex

underlogue: lex.yy.c underlogue.tab.c underlogue.tab.h
	g++ underlogue.tab.c lex.yy.c -lfl -o underlogueParser
#make underlogue
#bison -d underlogue.y
#flex underlogue.l
#g++ underlogue.tab.c lex.yy.c -lfl -o underlogueParser
