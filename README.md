## Project TraceON: Alignement multiple de traces d'évènements

Ce projet est une tentatives de création d'un programme en C++ qui va créer des séquences aléatoires selon une difficulté demandée, 
aligner ses séquences et obtenir le score des alignements obtenus.

Le concept est de produire un algorithme d'alignement de traces. Les traces étant des éléments abstraits.

Les points apparaissant sont les temps, toute les 30" par exemple on aligne.  

Il faut fournir un script de "lancement", un script de test.  

Les noms de fichier de sortie sont à passer en paramètre du programme.  

Il faut générer 20 jeux de données aléatoire avec 30 traces de difficultés différentes.  

Les évènements peuvent ne pas être séquenciel, par exemple E5 avant E3 etc.  

Dans le choix (2-5) par exemple, les évènements sont compris dans les tops (= ".")  

Dans Ea1 <(tr1 - tr2)* >Ea2 : Ea1 et Ea2 ne peuvent pas être dans l'intervale

Exemple de syntaxe de génération de trace:
> E4 < (3-10) E1_3 E2_2 I1 I2 > E5  
> E1, E2, I1 et I2 doivent apparaître qu'une fois


## Génération de données
# launch_data_generation_toy_example.py
Pour générer un jeu de données aléatoire vous devez lancer dans un terminal le fichier python suivant:
launch_data_generation_toy_example.py

Le tout doit être suivi par le chiffre 1 ou 2 en fonction de la difficulté des données que vous souhaitez obtenir. 
Avec 1 pour facile et 2 pour difficile. Puis en fonction de ses paramètre le script va lire dans le fichier Init.txt et renvoie ses informations au fichier main_TraceON.cpp

# Init.txt
Ce fichier texte sert d'initialisation au script Python vu au dessus, et va le renseigner sur le type de données voulus, leur nombres et leur tailles. 

Il peut être modifiable à volonté par l'ulitisateur pour adapter le programme à ses besoins:
A la condition que ses modifications s'applique sur le niveau de difficulté de la génération de données et non sur les lignes "1) facile:" (ligne 4) et "2) difficile" (ligne 6).
Attention la syntaxe de génération de trace doit être respecté.
L'utilisateur peut aussi modifier le nombre et la longueur des séquences voulus sur la ligne 10 et 12 et non sur les lignes "Nombres_traces:" (ligne 9) et "Taille:" (ligne 11).

# main_TraceON.cpp
Fichier principal de la génération de trace en C++, qui après avoir obtenus les informations envoyés par le fichier launch_data_generation_toy_example.py détecte les différentes ancres, leur nombres ainsi que leur position et fait appel à des fonctions présentent dans le fichier trace_generator.cpp en fonction des informations envoyés par le pichier Python 
et les mets dans un fichier texte "Test.txt".

# trace_generator.cpp
Fichier C++ qui contient toutes les fonctions utile à main_TraceON.cpp pour la création des données aléatoire.

# trace_generator.hpp
Fichier d'en-tête de trace_generator.cpp

# simple_functions.cpp
Fichier C++ contenant des fonctions et procédure simple mais utiles au fonctionnement de trace_generator.cpp

# simple_functions.hpp
Fichier d'en-tête de simple_functions.cpp

# Test.txt
Ce fichier texte est le fichier de résultats des séquences obtenus aléatoirement.


## Alignement des séquences
# main_align.cpp
Fichier principal d'alignement des séquences en C++, il va aligner les séquences obtenus avec le fichier main_Trace_ON.cpp grace à des fonctions et procédure présente dans le fichier alignement.cpp

# alignement.cpp
Fichier C++ contenant toutes les fonctions et procédure nécesaire  à l'alignement multiple, à la création de matrice triangulaire et d'arbre binaire.

# alignement.hpp
Fichier d'en-tête de alignement.cpp
