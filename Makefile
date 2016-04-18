#
# Course ICP @ FIT VUT Brno, 2016
# ICP 2016 Project - Othello
#
.PHONY: all clean run

PROJ=hra2016
PROJ_CLI=$(PROJ)-cli
PROJ_GUI=$(PROJ)-gui
CXX=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -O2
DOXYGEN=doxygen

SRC_FILES = $(wildcard *.cpp)
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES))

all: $(PROJ_CLI)

$(PROJ_CLI): $(OBJ_FILES)
	$(CXX) $(CFLAGS) $^ -o $(PROJ_CLI) -lboost_serialization

%.o: %.cpp %.h
	$(CXX) $(CFLAGS) -c $< -o $@

main_cli.o: main_cli.cpp
	$(CXX) $(CFLAGS) -c main_cli.cpp

doxygen:
	$(DOXYGEN) doxyConf

clean:
	rm -f *.o *.h.gch $(PROJ)-cli $(PROJ)-gui
	rm -rf doc/

run:
	./$(PROJ_CLI)
