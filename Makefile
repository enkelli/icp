#
# Course ICP @ FIT VUT Brno, 2016
# ICP 2016 Project - Othello
#
.PHONY: 
	all clean run

PROJ=hra2016
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

doxygen:
	@echo "Write some doc please, your code is such an non-readable shit."

clean:
	rm -f *.o $(PROJ)-cli $(PROJ)-gui

run:
	./$(PROJ_CLI)
