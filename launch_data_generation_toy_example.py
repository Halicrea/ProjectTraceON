#!/usr/bin/env python3
#####################################################################
## 08/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: launch_data_generation_toy_example.py
#####################################################################
import subprocess
import sys

##	Choose diffculty based on paramater either 1 or 2
if sys.argv[1] == "1":
	difficulty = "1) Facile:\n"
else:
	difficulty = "2) Difficile:\n"

##	Reading init file:
# 	Opening file and then
#	looping through the file
with open("init.txt","r") as file:
	for line in file:
		if line == difficulty:
			expression=next(file)
file.close()

## Using subprocess to launch the executable C++ creating the traces
subprocess.run(["./main_TraceON",expression,sys.argv[2]])