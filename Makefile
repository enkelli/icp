#
# Course ICP @ FIT VUT Brno, 2016
# ICP 2016 Project - Othello
#
.PHONY: all cli gui clean run pack

#
# Env
#

PROJ = hra2016
PROJ_CLI = $(PROJ)-cli
PROJ_GUI = $(PROJ)-gui
QMAKE = qmake # more specific path??? check task
CXX = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2
DOXYGEN = doxygen

SRC_PATH = $(shell pwd)/src
COMMON_PATH = $(SRC_PATH)/common
CLI_PATH = $(SRC_PATH)/cli
GUI_PATH = $(SRC_PATH)/gui

BOOST_PATH = $(SRC_PATH)/boost
BOOST_LIB_PATH = $(BOOST_PATH)/lib

COMMON_SRC_FILES = $(wildcard $(COMMON_PATH)/*.cpp)
COMMON_HEADER_FILES = $(wildcard $(COMMON_PATH)/*.h)
COMMON_OBJ_FILES = $(patsubst %.cpp, %.o, $(COMMON_SRC_FILES))

CLI_SRC_FILES = $(wildcard $(CLI_PATH)/*.cpp)
CLI_HEADER_FILES = $(wildcard $(CLI_PATH)/*.h)
CLI_OBJ_FILES = $(patsubst %.cpp, %.o, $(CLI_SRC_FILES))

GUI_SRC_FILES = $(wildcard $(GUI_PATH)/*.cpp)
GUI_HEADER_FILES = $(wildcard $(GUI_PATH)/*.h)
GUI_OBJ_FILES = $(patsubst %.cpp, %.o, $(GUI_SRC_FILES))

INC_PATH = -isystem$(BOOST_PATH) -I$(COMMON_PATH)
LIB_PATH = -L$(BOOST_LIB_PATH)
LINK_LIB = -lboost_serialization

#
# Compilation
#
all: $(PROJ_CLI) $(PROJ_GUI)

cli: $(PROJ_CLI)

gui: $(PROJ_GUI)

$(PROJ_CLI): $(COMMON_OBJ_FILES) $(CLI_OBJ_FILES)
	$(CXX) $(CFLAGS) $^ $(LIB_PATH) -o $(PROJ_CLI) $(LINK_LIB)

$(PROJ_GUI): $(COMMON_OBJ_FILES)
	@cd $(GUI_PATH) && $(QMAKE) && make
	@mv $(GUI_PATH)/$(PROJ_GUI) .

$(CLI_PATH)/main.o: $(CLI_PATH)/main.cpp
	$(CXX) $(CFLAGS) $(INC_PATH) -c $< -o $@

%.o: %.cpp %.h
	$(CXX) $(CFLAGS) $(INC_PATH) -c $< -o $@


#
# Other stuff
#
doxygen:
	$(DOXYGEN) $(SRC_PATH)/doxyConf

clean:
	-@cd $(GUI_PATH) && make clean
	rm -f $(CLI_PATH)/*.o $(PROJ_CLI) $(PROJ_GUI)
	rm -rf doc/

pack:
	tar -zcvf xplask00-xposto02.tar.gz $(SRC_PATH) Makefile

run:
	./$(PROJ_CLI)
