#for i in $(seq 1 20); do ./main_TraceON ;done

## Compilation du main
main_TraceON: main_TraceON.cpp trace_generator.o simple_functions.o
	g++ main_TraceON.cpp trace_generator.o simple_functions.o -o main_TraceON


## Compilation des fichiers de fonctions
simple_functions.o: simple_functions.cpp
	g++ -c simple_functions.cpp

trace_generator.o: trace_generator.cpp
	g++ -c trace_generator.cpp 



