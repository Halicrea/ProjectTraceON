/*#########################################
## 01/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: trace_generator.cpp
###########################################*/
#include <random>
#include <iostream>
#include <string>
#include "trace_generator.hpp"
using namespace std;

/*
	Permet d'obtenir la longueur du bloc.
	Elle est choisi de manière aléatoire
*/
void bloc::set_temps(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1,10);
	temps=distr(gen);
}
//Dans la suite on veut une fonction qui affiche le temps
string bloc::print_temps(){
	string seq_tps = "";
	for (int i=0;i<temps;i++){
		seq_tps+='-';
	}
	return seq_tps;
}

// Constructeur de sequence
void bloc::set_seq(string sequence){
	seq=sequence;
}

string bloc::parentheses(string cas1){
	// On utilise la fonction print_temps() pour obtenir une séquence de taille temps et sans anchors.
	this -> set_seq(this -> print_temps());
	return this -> get_bloc();
}

void bloc::crochets_plus(string anchor1, string anchor2){
	// On ajoute à des positions aléatoire des anchors
	string seq = "";
	int nbr_anchors;
	int num_anchor1 = anchor1[1];
	int num_anchor2 = anchor2[1];
	bool placing_anchor; 


	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<>distr(num_anchor1,num_anchor2);
	nbr_anchors = distr(gen);
	//auto gen_bool = bind(uniform_int_distribution<>(0,1),default_random_engine());

	for (int i=0;i<temps;i++){	
		placing_anchor=uniform_int_distribution<>{0,1}(gen);
		if (placing_anchor){
			seq += 'E';
			seq += distr(gen);
		} else {
			seq += '-';
		}
	} 
	this -> set_seq(sequence);
	
}

// Get sequence finale
string bloc::get_bloc(){
	string sequence=seq;
	return sequence;
}



/*
	Pour parcourir l'expression de génération de traces.
*/
/*
while (arg[i]!=S){
	if (arg[i] == "("){
		for (i=i;i<i_max;i++){
			cout << " ";
		}
	} else {

	}
}
*/

/*
	Generateur au fur et a mesure
*/
/*
for (i=0;i<(length_trace-1);i++){
	cout << word[par_i];
	word++;
	if (word[par_i]=="("){
		for (i=i;i<(length_trace-1);i++){
			cout << " "; 
		}
	} else {

	}
}
cout << "S" << endl;
*/
/*
bloc::hachage(int tps, string *hache){
	return (hache[tps])
}*/

