/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: trace_generator.cpp
###########################################*/
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include "trace_generator.hpp"
#include "simple_functions.hpp"
using namespace std;
//###########################################

//#######################################################################################//
//Get the length of the blocks randomly

void bloc::set_temps(int longueur){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1,longueur);
	temps=longueur;
}

//#######################################################################################//
// Function that display the time
string bloc::print_temps(){
	string seq_tps = "";
	for (int i=0;i<temps;i++){
		seq_tps+="- ";
	}
	return seq_tps;
}

//######################################################################################//
// Building the sequences
void bloc::set_seq(string sequence){
	seq=sequence;
}

//#######################################################################################//
// We use the function print_temps() to get a time-sized sequence and without anchors.
string bloc::parentheses(){
	return this -> print_temps();
}

//######################################################################################//
// Procedure make the dataset with + or *
void bloc::crochets_plus_or_star(int first_anchor_value, char etoile_croix){
	// We add at random positions the anchors
	string sequence = "";
	int nbr_anchors = 0;
	int val_tempo = 0;
	int val_anchor;
	int j=0;
	bool placing_anchor;

	//Random generator initialization.
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
		while (find(anchor_pos,val_tempo,nbr_anchors)){
			val_tempo=uniform_int_distribution<>{0,temps-1}(gen);
		}
		anchor_pos[i]=val_tempo;
	}
	// Sort the sequence with anchors 
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
}

//#######################################################################################//
// Procedure make the dataset with |
void bloc::crochets_pipe(int first_anchor_value, string anchor_list){
	// We add at random positions the anchors
	string sequence = "";
	vector<string> anchors;
	string anchors_tempo = "";
	int anchors_doppelganger = 1;
	
	//Random generator initialization.
	random_device rd;
	mt19937 gen(rd());

	int i=0;
	// Since we need to be find the precedent event if we have a 'X', we use a counter
	// for each time we add an event. We initialize it at -1 
	int cpt_event=-1;
	while (i<anchor_list.length()){
		if (anchor_list[i]=='X'){
			i++;
			anchors_doppelganger = anchor_list[i] - '0'; // - '0' convert char to int
			for (int j=1;j<anchors_doppelganger;j++){
				anchors.push_back(anchors[cpt_event]);
			}
			i++;
			continue;
		}
		if (anchor_list[i]=='|'){
			i++;
			continue;
		}
		while(i<anchor_list.length() && (anchor_list[i]!='X' && anchor_list[i]!='|')){
			anchors_tempo += anchor_list[i];
			i++;
		}
		anchors.push_back(anchors_tempo);
		cpt_event++;
		anchors_tempo="";
	}

	i = 0;
	while(i < anchors.size()) {
		if (uniform_int_distribution<>{0,1}(gen)==1){
			sequence += anchors[i] + " ";
			i++;
		} else {
			sequence += "- ";
		}
	}
	this -> set_seq(sequence);
}


//#######################################################################################//
// Procedure make the dataset with %
void bloc::crochets_percent(int first_anchor_value, string anchor_list){
	// We add at random positions the anchors
	string sequence = "";
	vector<string> anchors;
	string anchors_tempo = "";
	int anchors_doppelganger = 1;

	//Random generator initialization.
	random_device rd;
	mt19937 gen(rd());

	int i = 0;
	int cpt_event=-1;

	while (i<anchor_list.length())
	{

		if (anchor_list[i]=='%'){
		i++;
		anchors_doppelganger = anchor_list[i] - '0'; // - '0' convert char to int
		//cout << anchors_doppelganger << "-" << anchors[cpt_event];
		for (int j=1;j<anchors_doppelganger;j++){
			anchors.push_back(anchors[cpt_event]);
		}
		i++;
		continue;		
		}

		if (anchor_list[i]=='|'){
			i++;
			continue;
		}

		while(i<anchor_list.length() && (anchor_list[i]!='%' && anchor_list[i]!='|')){
			anchors_tempo += anchor_list[i];
			i++;
		}

		anchors.push_back(anchors_tempo);
		anchors_tempo="";
		cpt_event++;
	
	}

	i = 0;
	while(i < anchors.size()) {
    	//cout << anchors[i] << "/" << i << endl;
		if (uniform_int_distribution<>{0,1}(gen)==1){
			sequence += anchors[i] + " ";
			i++;
		} else {
			sequence += "- ";
		}
	}
	this -> set_seq(sequence);
}

//#######################################################################################//
// Get sequence finale
string bloc::get_bloc(){
	string sequence=seq;
	return sequence;
}
