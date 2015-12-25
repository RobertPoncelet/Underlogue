all: test.out

test.out: ul-driver.o ul-parser.o ul-scanner.o test.o

	g++ -o test.out ul-driver.o ul-parser.o ul-scanner.o test.o

ul-driver.o: ul-driver.cc ul-driver.hh ul-parser.hh

	g++ -c ul-driver.cc

ul-parser.o: ul-parser.cc ul-parser.hh ul-driver.hh

	g++ -c ul-parser.cc

ul-parser.cc ul-parser.hh: ul-parser.yy

	bison --defines=ul-parser.hh -o ul-parser.cc ul-parser.yy

ul-scanner.o: ul-scanner.cc ul-parser.hh ul-driver.hh

	g++ -c ul-scanner.cc

ul-scanner.cc: ul-scanner.ll

	flex -o ul-scanner.cc ul-scanner.ll

test.o: test.cc

	g++ -c test.cc

.PHONY: clean

clean:

	-rm *.o ul-parser.hh ul-parser.cc ul-scanner.cc location.hh position.hh stack.hh test.out
