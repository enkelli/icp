PROJ=othello
PROJ_CLI=$(PROJ)-cli
PROJ_GUI=$(PROJ)-gui
CXX=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g

all: $(PROJ_CLI)

OBJ_FILES=main.o Othello.o Table.o

$(PROJ_CLI): $(OBJ_FILES)
	$(CXX) $^ -o $(PROJ_CLI)

$(OBJ_FILES): main.cpp Othello.cpp Table.cpp
	$(CXX) $(CFLAGS) -c Main.cpp Othello.cpp Table.cpp

clean:
	rm -f *.o $(PROJ)-cli $(PROJ)-gui
