#
# Course ICP @ FIT VUT Brno, 2016
# ICP 2016 Project - Othello
#
.PHONY: all clean run pack

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

SRC_PATH = ./src
BOOST_PATH = $(SRC_PATH)/boost
BOOST_LIB_PATH = $(BOOST_PATH)/lib

GUI_SRC_FILES = $(SRC_PATH)/main.cpp \
								$(SRC_PATH)/mainwindow.cpp\
							 	$(SRC_PATH)/moc_mainwindow.cpp \
								$(SRC_PATH)/qrc_resources.cpp 
GUI_HEADER_FILES = $(SRC_PATH)/mainwindow.h $(SRC_PATH)/ui_mainwindow.h
SRC_FILES = $(wildcard $(SRC_PATH)/*.cpp)
SRC_FILES_CLI = $(filter-out $(GUI_SRC_FILES), $(SRC_FILES))
HEADER_FILES = $(wildcard $(SRC_PATH)/*.h)
HEADER_FILES_CLI = $(filter-out $(GUI_HEADER_FILES), $(HEADER_FILES))
OBJ_FILES_CLI = $(patsubst %.cpp, %.o, $(SRC_FILES_CLI))

INC_PATH = -isystem$(BOOST_PATH)
LIB_PATH = -L$(BOOST_LIB_PATH)
LINK_LIB = -lboost_serialization

#
# Compilation
#
all: $(PROJ_CLI) $(PROJ_GUI)

$(PROJ_CLI): $(OBJ_FILES_CLI)
	$(CXX) $(CFLAGS) $^ $(LIB_PATH) -o $(PROJ_CLI) $(LINK_LIB)

%.o: %.cpp %.h
	$(CXX) $(CFLAGS) $(INC_PATH) -c $< -o $@

$(SRC_PATH)/main_cli.o: $(SRC_PATH)/main_cli.cpp
	$(CXX) $(CFLAGS) $(INC_PATH) -c $^ -o $@

$(PROJ_GUI): $(OBJ_FILES_CLI)
	@cd $(SRC_PATH) && $(QMAKE) && make
	@mv $(SRC_PATH)/$(PROJ_GUI) .

#
# Other stuff
#
doxygen:
	$(DOXYGEN) doxyConf

clean:
	-@cd $(SRC_PATH) && make clean
	rm -f $(SRC_PATH)/*.o $(SRC_PATH)/*.h.gch $(SRC_PATH)/Makefile $(PROJ)-cli $(PROJ)-gui
	rm -rf doc/

pack:
	tar -zcvf xplask00-xposto02.tar.gz $(SRC_PATH) Makefile

run:
	./$(PROJ_CLI)
