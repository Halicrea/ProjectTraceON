#for i in $(seq 1 20); do ./main_TraceON ;done
#######################################################
#           Editable options   				          #
#######################################################
PROGR_NAME	= main_traceAlign
CREATE_SEQ	= main_TraceON
SUBMIT_NAME	= project_TraceON_ElynaB-FlorentB.tar.gz
#######################################################
#           Folders 					       	      #
#######################################################
SRC_DIR		= ./src
BIN_DIR		= ./bin
OBJECT_DIR	= ./obj

SRC_LIST	= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST	= $(BIN_DIR)/$(notdir $(SRC_LIST:.cpp=.o))

BIN			= bin/$(CREATE_SEQ)
BIN2		= bin/$(PROGR_NAME)
OBJS_GEN	= obj/trace_generator.o obj/simple_functions.o
OBJS_ALIGN	= obj/alignment.o obj/simple_functions.o obj/clustering.o obj/pairwize_global.o

#######################################################
#           Compilation for the different files  	  #
#######################################################


all: $(BIN) $(BIN2)

## Compilation main_align
$(BIN2): src/main_align.cpp $(OBJS_ALIGN)
	g++ -o $@ src/main_align.cpp $(OBJS_ALIGN)

## Compilation du main
$(BIN): src/main_TraceON.cpp $(OBJS_GEN)
	g++ src/main_TraceON.cpp $(OBJS_GEN) -o $@


## Compilation des fichiers de fonctions
obj/%.o: src/%.cpp
	g++ -c $< -o $@

## Cleaning the folders with compiled files
clean:
	rm -r bin/* obj/*

submit:
	rm $(SUBMIT_NAME)
	tar -czvf $(SUBMIT_NAME) *