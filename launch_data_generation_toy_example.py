#!/usr/bin/env python3
#####################################################################
## 08/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: launch_data_generation_toy_example.py
#####################################################################
import subprocess

# Using subprocess to launch the executable C++
subprocess.run(["./main_TraceON", "E2<()+>E8()E12<()E13X3|E89|E41X5|E14>E46<()*>S"])