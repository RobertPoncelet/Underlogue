# Makefile for JustForFun Files

# A few variables

#CC=gcc
#LIBS=-lpanel -lncurses

#SRC_DIR=src
#EXE_DIR=.

#EXES = \
#	${EXE_DIR}/main

#${EXE_DIR}/%: %.o
#	${CC} -o $@ $< ${LIBS}

#%.o: ${SRC_DIR}/%.c
#	${CC} -o $@ -c $<

#all:    ${EXES}


#clean:
#	@rm -f ${EXES}

CC=g++
CFLAGS=-I include/
LIBS=-lpanelw -lncursesw

all: src/ulScriptReader.o src/main.o
	$(CC) -o underlogue src/main.cpp src/ulScriptReader.cpp $(LIBS) $(CFLAGS)
	#g++ -o underlogue src/main.cpp src/ulScriptReader.cpp -lpanelw -lncursesw -I include/

     
     
