#!/usr/bin/env python3
#####################################################################
## 08/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: launch_data_generation_toy_example.py
#####################################################################
import subprocess
import sys
import time


start_time = time.perf_counter()

## Greating
print(r"""   ___
  (o,o)	---|Welcome to this trace generator !|
 <  .  >	
---"-"---""")


## Verify if the number of parameter is correct.
if (len(sys.argv) != 2 and len(sys.argv) != 3):
	print("\033[1;31mNeeds at least 1 or 2 parameters:")
	print("- 1st: Difficulty (1 or 2)")
	print("- 2nd: File output for trace generation\033[0m")
	exit(1)


##	Choose diffculty based on paramater either 1 or 2
if sys.argv[1] == "1":
	difficulty = "1) Facile:\n"
else:
	if sys.argv[1] == "2":
		difficulty = "2) Difficile:\n"
	else:
		print("\033[1;31mWrong difficulty, 1 for easy and 2 for hard.\033[0m")
		exit(2)


##	Reading init file:
# 	Opening file and then
#	looping through the file
with open("init.txt","r") as file:
	for line in file:
		if line == difficulty:
			expression=next(file)
		if line == "Nombre_traces:\n":
			nb_trace = next(file)[:-1]
		if line == "Taille:\n":
			size_trace = next(file)
file.close()

print(nb_trace,size_trace)


## Using subprocess to launch the executable C++ creating the traces
if len(sys.argv) == 2:
	subprocess.run(["bin/main_TraceON",expression,"Test.txt",nb_trace,size_trace])
else:
	subprocess.run(["bin/main_TraceON",expression,sys.argv[2],nb_trace,size_trace])


## Using subprocess to launch the alignment of the traces obtained
subprocess.run(["bin/main_traceAlign"])


## Path of the alignment file generate 

#with open("alignment_generate.txt", "w") as file:
#	file.write()
#file.close()


## Path of the scores file generate

#with open("scores_generate.csv", "w") as file:
#	file.write()
#file.close()
	

## Calculation of the execution time of the entire program
end_time = time.perf_counter()
execution_time = end_time - start_time
print("Temps d'exécution: ", execution_time, " secondes.")
