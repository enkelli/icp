PROJ=othello
PROJ_CLI=$(PROJ)-cli
PROJ_GUI=$(PROJ)-gui
CXX=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -g

all: $(PROJ_CLI)

OBJ_FILES=main.o othello.o table.o

$(PROJ_CLI): $(OBJ_FILES)
	$(CXX) $^ -o $(PROJ_CLI)

$(OBJ_FILES): main.cpp othello.cpp othello.h table.cpp table.h
	$(CXX) $(CFLAGS) -c $^

clean:
	rm -f *.o $(PROJ)-cli $(PROJ)-gui
