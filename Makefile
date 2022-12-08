#for i in $(seq 1 20); do ./main_TraceON ;done

## Compulation main_align
main_align: main_align.cpp alignment.o
	g++ -o main_align main_align.cpp alignment.o
## Compilation align
alignment.o: alignment.cpp alignment.hpp
	g++ -c alignment.cpp

## Compilation du main
main_TraceON: main_TraceON.cpp trace_generator.o simple_functions.o
	g++ main_TraceON.cpp trace_generator.o simple_functions.o -o main_TraceON


## Compilation des fichiers de fonctions
simple_functions.o: simple_functions.cpp
	g++ -c simple_functions.cpp

trace_generator.o: trace_generator.cpp
	g++ -c trace_generator.cpp 



