#for i in $(seq 1 20); do ./main_TraceON ;done

## Compilation du main
main_TraceON: main_TraceON.cpp trace_generator.o
	g++ main_TraceON.cpp trace_generator.o -o main_TraceON


## Compilation des fichiers de fonctions
trace_generator.o: trace_generator.cpp
	g++ -c trace_generator.cpp 

