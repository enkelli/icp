#
# Course ICP @ FIT VUT Brno, 2016
# ICP 2016 Project - Othello
#
.PHONY: all clean run pack

PROJ=hra2016
PROJ_CLI=$(PROJ)-cli
PROJ_GUI=$(PROJ)-gui
CXX=g++
CFLAGS=-std=c++11 -Wall -Wextra -pedantic -O2
DOXYGEN=doxygen

BOOST_PATH="./boost"
BOOST_LIB_PATH="$(BOOST_PATH)/lib"
SRC_FILES = $(wildcard *.cpp)
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(patsubst %.cpp, %.o, $(SRC_FILES))

all: $(PROJ_CLI)

$(PROJ_CLI): $(OBJ_FILES)
	$(CXX) $(CFLAGS) $^ -L$(BOOST_LIB_PATH) -o $(PROJ_CLI) -lboost_serialization

%.o: %.cpp %.h
	$(CXX) $(CFLAGS) -isystem$(BOOST_PATH) -c $< -o $@

main_cli.o: main_cli.cpp
	$(CXX) $(CFLAGS) -isystem$(BOOST_PATH) -c main_cli.cpp

doxygen:
	$(DOXYGEN) doxyConf

clean:
	rm -f *.o *.h.gch $(PROJ)-cli $(PROJ)-gui
	rm -rf doc/

pack:
	tar -zcvf xplask00-xposto02.tar.gz $(SRC_FILES) $(HEADER_FILES) $(BOOST_PATH) Makefile

run:
	./$(PROJ_CLI)
