#for i in $(seq 1 20); do ./main_TraceON ;done
#######################################################
#           Editable options   				          #
#######################################################
PROGR_NAME	= traceAlign
CREATE_SEQ	= main_TraceON

#######################################################
#           Folders 					       	      #
#######################################################
SRC_DIR		= ./src
BIN_DIR		= ./bin
OBJECT_DIR	= ./obj

SRC_LIST	= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST	= $(BIN_DIR)/$(notdir $(SRC_LIST:.cpp=.o))

BIN			= bin/$(CREATE_SEQ)
OBJS_GEN	= obj/trace_generator.o obj/simple_functions.o
OBJS_ALIGN	= obj/alignment.o obj/simple_functions.o

#######################################################
#           Compilation for the different files  	  #
#######################################################


all: $(BIN)

## Compilation main_align
#main_align: main_align.cpp $(OBJS_ALIGN)
#	g++ -o main_align main_align.cpp $(OBJS_ALIGN)
## Compilation align
#alignment.o: alignment.cpp alignment.hpp
#	g++ -c alignment.cpp

## Compilation du main
$(BIN): src/main_TraceON.cpp $(OBJS_GEN)
	g++ src/main_TraceON.cpp $(OBJS_GEN) -o $@


## Compilation des fichiers de fonctions
obj/%.o: src/%.cpp
	g++ -c $< -o $@

clean:
	rm -r bin/* obj/*


