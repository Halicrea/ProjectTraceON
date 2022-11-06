/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: trace_generator.cpp
###########################################*/
#include <random>
#include <iostream>
#include <string>
#include "trace_generator.hpp"
#include "simple_functions.hpp"
using namespace std;
//###########################################

//###########################################
/*
	Permet d'obtenir la longueur du bloc.
	Elle est choisi de manière aléatoire
*/
void bloc::set_temps(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(0,10);
	temps=distr(gen);
}
//Dans la suite on veut une fonction qui affiche le temps
string bloc::print_temps(){
	string seq_tps = "";
	for (int i=0;i<temps;i++){
		seq_tps+="- ";
	}
	return seq_tps;
}

// Constructeur de sequence
void bloc::set_seq(string sequence){
	seq=sequence;
}

string bloc::parentheses(){
	// On utilise la fonction print_temps() pour obtenir une séquence de taille temps et sans anchors.
	return this -> print_temps();
}

void bloc::crochets_plus_or_star(int first_anchor_value, char etoile_croix){
	// On ajoute à des positions aléatoire des anchors
	string sequence = "";
	int nbr_anchors = 0;
	int val_tempo = 0;
	int val_anchor;
	int j=0;
	bool placing_anchor; 

	random_device rd;
	mt19937 gen(rd());
	if (temps == 0){
		this -> set_seq(sequence);
		return;
	}
	if (etoile_croix=='+'){
		uniform_int_distribution<>distr(1,temps);
		nbr_anchors = distr(gen);
	} else {
		uniform_int_distribution<>distr(0,temps);
		nbr_anchors = distr(gen);
	}
	int anchor_pos[nbr_anchors];

	for (int i=0;i<nbr_anchors;i++){
		val_tempo=uniform_int_distribution<>{0,temps-1}(gen);
		while (find(anchor_pos,val_tempo)){
			val_tempo=uniform_int_distribution<>{0,temps-1}(gen);
		}
		anchor_pos[i]=val_tempo;
	}
	cout << "Temps: " << temps<< endl;
	cout << "Liste non triée: ";
	for (int i=0; i<nbr_anchors;i++){
		cout << anchor_pos[i]<< "/";
	}
	cout << endl;
	quickSort(anchor_pos,0,nbr_anchors-1);
	cout << "Liste triée: ";
	for (int i=0; i<nbr_anchors;i++){
		cout << anchor_pos[i]<< "/";
	}
	cout << endl;
	
	for (int i=0; i<temps;i++){
		if (anchor_pos[j]==i){
			sequence += "E";
			sequence += to_string(uniform_int_distribution<>{first_anchor_value,2*first_anchor_value}(gen));
			sequence += ' ';
			j++;
		} else {
			sequence += "- ";
		}
	}
	this -> set_seq(sequence);
}

/*void crochets_pipe(int first_anchor_value, string anchor_list){
	// On ajoute à des positions aléatoire des anchors
	string sequence = "";
	int nbr_anchors = 0;
	int val_tempo = 0;
	int val_anchor;
	int j=0;
	bool placing_anchor; 

	random_device rd;
	mt19937 gen(rd());
	if (temps == 0){
		this -> set_seq(sequence);
		return;
	}
	
	for (int i;)
	int anchor_pos[nbr_anchors];

	for (int i=0;i<nbr_anchors;i++){
		val_tempo=uniform_int_distribution<>{0,temps-1}(gen);
		while (find(anchor_pos,val_tempo)){
			val_tempo=uniform_int_distribution<>{0,temps-1}(gen);
		}
		anchor_pos[i]=val_tempo;
	}
	quickSort(anchor_pos,0,nbr_anchors-1);
	for (int i=0; i<temps;i++){
		if (anchor_pos[j]==i){
			sequence += "E";
			sequence += to_string(uniform_int_distribution<>{first_anchor_value,2*first_anchor_value}(gen));
			sequence += ' ';
			j++;
		} else {
			sequence += "- ";
		}
	}
	this -> set_seq(sequence);
}*/

// Get sequence finale
string bloc::get_bloc(){
	string sequence=seq;
	return sequence;
}