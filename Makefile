PROJ=othello-cli
CXX=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g

all: $(PROJ)

$(PROJ): Table.o
	$(CXX) Table.o -o $(PROJ)

Table.o: Table.cpp Table.h
	$(CXX) $(CFLAGS) -c Table.cpp

clean:
	rm -f *.o $(PROJ)
