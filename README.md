# Project TraceON: Alignement multiple de traces d'évènements

Ce projet a pour but de création d'un programme en C++ qui va créer des séquences aléatoires selon une difficulté demandée, aligner ses séquences et obtenir le score des alignements obtenus.

Le concept est de produire un algorithme d'alignement de traces. Les traces étant des éléments abstraits.

## Pour commencer

Pour pouvoir utiliser ce programme vous aurez besoin d'un terminal des bibliothèques string ,iostream, fstream, sstream, vector, cmath ,algorithm, random en C++ ainsi que de le dernière version de Python3 avec les bibliothèques subprocess, sys et time. 

### Pré-requis 

Pour pouvoir utiliser notre programme vous aurez besoin:

- launch_data_generation_toy_example.py
- launch_MSA_test.py
- init.txt
- init_MSA.txt
- Test.txt
- Test_output.txt
- Test_Score.csv
- un fichier bin contenant les executable de main_traceAlign et de mainTraceON
- un fichier obj contenant les fichiers alignment.o, clustering.o, pairwize_global.o, simple_functions.o er trace_generator.o
- un fichier src  contenant les fichiers alignment.cpp, aligment.hpp, clutering.cpp, clustering.hpp, main_align.cpp, main_TraceON.cpp, pairwize_global.cpp, pairwize_global.hpp, simple_functions.cpp, simple_functions.hpp struct.hpp, trace_generator.cpp et trace_generator.hpp

## Installation, démarrage et utilisation

Pour lancer le programme, il vous suffit d'executer dans le répertoire courant le script Python "launch_data_generation_toy_example.py" attention à bien spécifier quel niveau de difficulté de données vous voulez obtenir après avoir écrit: ./launch_data_generation_toy_example.py dans votre terminal ("1" pour facile et "2" pour difficile).

Il est possible de modifier la génaration de données aléatoire en modifiant le fichier init.txt tout en gardant les mêmes conventions  

Les évènements peuvent ne pas être séquenciel, par exemple E5 avant E3 etc.  

Dans le choix (2-5) par exemple, les évènements sont compris dans les tops (= "."), dans Ea1 <(tr1 - tr2)* >Ea2 : Ea1 et Ea2 ne peuvent pas être dans l'intervale

Exemple de syntaxe de génération de trace:
> E4 < (3-10) E1_3 E2_2 I1 I2 > E5  
> E1, E2, I1 et I2 doivent apparaître qu'une fois

Une fois la génération de données effectué vous devrez lancer le deuxième script Python: "launch_MSA_test.py" dans le répertoire courant, et c'est celui-ci qui lancera l'alignement des séquences ainsi générées.

L'alignement des séquences se créera dans le fichier "Test_output.txt" et les scores obtenus après alignement dans le fichier "Test_Score.csv".

Pour avoir un fichier pat alignment et un score par fichier, il vous suffit de lancer en premier le script  "lauch_data_generation_ty_example.py [niveau de difficulté] [nom du fichier] [nombre de fichier voulu]" suivi par le lencement du script "lauch_MSA_test.py [nom du fichier précédement rentré] [nom du fichier output] [nom du fichier des scores] [nombre de fichier voulu].

## Auteurs

- Elyna Bouchereau
- Florent Boyer

## Licence

Ce projet est sous licence de le Faculté des sciences et Techniques de l'université de Nantes, Master 2e année Bioinformatique pour les biologistes. 



