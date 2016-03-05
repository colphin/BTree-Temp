CXX = g++

CXXFLAGS = -std=c++11 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

BINARIES=main

all: ${BINARIES}

main: main.o btree.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o
