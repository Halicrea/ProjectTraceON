#!/usr/bin/env python3
#####################################################################
## 23/01/2023
## Par Elyna Bouchereau & Florent Boyer
## Fichier: launch_MSA_test.py
#####################################################################
import subprocess
import sys
import time


start_time = time.perf_counter()

## Greating
print(r"""   ___
  (o,o)	---|Welcome to this programm for Multiple Trace Alignment !|
 <  .  /	
---"-"---""")
gap_initial = ""
gap_penalty = ""
seuil = ""
Display_tree = ""

##	Reading init file:
# 	Opening file and then
#	looping through the file
with open("init_MSA.txt","r") as file:
	for line in file:
		if line == "gap_initial:\n":
			gap_initial=next(file)[:-1]
		if line == "gap_penalty:\n":
			gap_penalty = next(file)[:-1]
		if line == "seuil:\n":
			seuil = next(file)[:-1]
		if line == "Display_tree:\n":
			Display_tree = next(file)
file.close()

## Verify if the number of parameter is correct.
## Using subprocess to launch the executable C++ for the multiple alignment
match len(sys.argv):
	case 1:
		subprocess.run(["bin/main_traceAlign", gap_initial, gap_penalty, seuil, Display_tree, "Test.txt","Test_output.txt","Test_Score.csv"])
	case 2:
		subprocess.run(["bin/main_traceAlign", gap_initial, gap_penalty, seuil, Display_tree, sys.argv[1],"Test_output.txt","Test_Score.csv"])
	case 3:
		subprocess.run(["bin/main_traceAlign", gap_initial, gap_penalty, seuil, Display_tree, sys.argv[1], sys.argv[2],"Test_Score.csv"])
	case 4:
		subprocess.run(["bin/main_traceAlign", gap_initial, gap_penalty, seuil, Display_tree, sys.argv[1], sys.argv[2], sys.argv[3]])
	case _:
		print("\033[1;31mWrong paramter. Up to 3 parameters are needed:")
		print("- File for traces to align.")
		print("- File for aligned output traces.")
		print("- File for score computed.\033[0m")
		exit(1)





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