# Project TraceON: Alignment of traces
Le concept est de produire un algorithme d'alignement de traces. Les traces étant des éléments abstraits.  

Les points apparaissant sont les temps, toute les 30" par exemple on aligne.  

Il faut fournir un script de "lancement", un script de test.  

Les noms de fichier de sortie sont à passer en paramètre du programme.  

Il faut générer 20 jeux de données aléatoire avec 20 traces de difficultés différentes.  

Les évènements peuvent ne pas être séquenciel, par exemple E5 avant E3 etc.  

Dans le choix (2-5) par exemple, les évènements sont compris dans les tops (= ".")  

Dans Ea1 <(tr1 - tr2)* >Ea2 : Ea1 et Ea2 ne peuvent pas être dans l'intervale

Exemple de syntaxe de génération de trace:
> E4 < (3-10) E1_3 E2_2 I1 I2 > E5  
> E1, E2, I1 et I2 doivent apparaître qu'une fois

Il faut faire un MakeFile
