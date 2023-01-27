/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: alignment.cpp
###########################################*/
#include "struct.hpp"
#include "pairwize_global.hpp"
#include "clustering.hpp"
#include "alignment.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

// https://stackoverflow.com/questions/45447361/how-to-move-certain-elements-of-stdvector-to-a-new-index-within-the-vector
template <typename t> void move(vector<t>& v, size_t oldIndex, size_t newIndex)
{
    if (oldIndex > newIndex){
		rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
	} else {
		rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
	}
}
template <typename T>
int finder(vector<Type_trace> list, T val){
	int i=0;
	while(i<list.size() && list[i].header != val){
		 if(list[i].header == val) return i;
	}
	return list.size()-1;
}
struct tree_ptr{
	TArbreBin<string>* node;
};
//****************************************************************
/*
	Affiche un bel arbre.
	└──A
		├──B
		│   ├──R
		│   └──S
		└──C
			└──D

*/
template<typename T>
void TArbreBin<T>::printBTS(){
	this -> printBTS("",false);
}
template<typename T>
void TArbreBin<T>::printBTS(const string& prefix, bool isLeft){
	if(this != NULL){
		cout << prefix;
		cout << (isLeft ? "├──" : "└──");
		cout << data << endl;
		fg -> printBTS(prefix + (isLeft ? "│   " : "    "), true);
		fd -> printBTS(prefix + (isLeft ? "│   " : "    "), false);
	}
}

//****************************************************************
/*
	Simple procedure for printing a Type_trace.
*/
void print_Type_trace(Type_trace trace){
	cout << trace.header << ' ';
	for(int i=0;i< trace.sequence.size();i++){
		if(trace.sequence[i] == -1){
			cout << "_ ";
		} else if(trace.sequence[i] == 0){
			cout << "- ";
		} else cout << 'E' << trace.sequence[i] << ' ';
	}
	cout << "S\n";
}



//****************************************************************
/*
$$\      $$\           $$\   $$\     $$\         $$$$$$\  $$\ $$\                     
$$$\    $$$ |          $$ |  $$ |    \__|       $$  __$$\ $$ |\__|                    
$$$$\  $$$$ |$$\   $$\ $$ |$$$$$$\   $$\        $$ /  $$ |$$ |$$\  $$$$$$\  $$$$$$$\  
$$\$$\$$ $$ |$$ |  $$ |$$ |\_$$  _|  $$ |       $$$$$$$$ |$$ |$$ |$$  __$$\ $$  __$$\ 
$$ \$$$  $$ |$$ |  $$ |$$ |  $$ |    $$ |       $$  __$$ |$$ |$$ |$$ /  $$ |$$ |  $$ |
$$ |\$  /$$ |$$ |  $$ |$$ |  $$ |$$\ $$ |       $$ |  $$ |$$ |$$ |$$ |  $$ |$$ |  $$ |
$$ | \_/ $$ |\$$$$$$  |$$ |  \$$$$  |$$ |       $$ |  $$ |$$ |$$ |\$$$$$$$ |$$ |  $$ |
\__|     \__| \______/ \__|   \____/ \__|$$$$$$\\__|  \__|\__|\__| \____$$ |\__|  \__|
                                         \______|                 $$\   $$ |          
                                                                  \$$$$$$  |          
                                                                   \______/           
*/
//****************************************************************
/*
	Constructor for the classe
*/
void Multi_Align::init_trace_list(string file_name){
	vector<string> liste_trace;
	ifstream file(file_name);
	string line;
	Type_trace trace_i;
	int n_line = 0;
	while(getline(file,line)){
		liste_trace.push_back(line);
		trace_i = trace_to_dict(line);
		trace_list.push_back(trace_i);
		n_line++;
	}
	number_of_traces = n_line;
}

//****************************************************************
/*
	To calculate the distance between two matrix, and more precisely,
	the difference between D_prec and D.
	The number of paris which we can produce from r elements is: r(r-1)/2
*/
float difference(vector<matri> &D,vector<matri> &D_prec){
	cout << "- Calcul difference\n";
	int distance = 0; // We initialize the distance between the two matrix
	int n = D.size();
	//cout << endl;
	//cout << D[0].ligne[0] << endl;
	for(int i=1; i<n;i++){
		//cout << 'i' << i << '-';
		for(int j=0;j<D[i].ligne.size();j++){
			//cout << D_prec[i].ligne[j] << " % " << D[i].ligne[j];
			//distance = distance + pow(D_prec[i].ligne[j]-D[i].ligne[j],2);
		}
		//cout << endl;
	}
	distance = (2*distance)/n*(n-1);
	distance = sqrt(distance);
	return distance;
}
float random_val(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1,50);
	return distr(gen);
}
void create_tringular_matrix(vector<matri> &D){
	int n=D.size();
	D[0].header = "Seq 1";
	for(int i=1;i<n;i++){
		//We go to each row and generate a row the size needed
		D[i].ligne=vector<float>(i);
		//D[i].header = "Seq " + to_str(i+1);
		for(int j=0;j<i;j++){
			D[i].ligne[j]=1;
		}
	}
}
void print_tri_matrix(vector<matri> &D){
	int n=D.size();
	cout << "Affichage matrice: \n";
	for(int i=0;i<n;i++){
		cout << D[i].header << "\t";
		for(int j=0;j<D[i].ligne.size();j++){
			cout << D[i].ligne[j] << "\t";
		}
		cout << endl;
	}
}

//****************************************************************
vector<matri> calcul_dissimilarite(vector<Type_trace> trace_list){
	// Number of sequences:
	int n = trace_list.size();
	int score;
	// Initialization of a triangular matrix localy before throwing it back.
	vector<matri> tri_matrix(n);
	tri_matrix[0].header = trace_list[0].header;
	for(int i=1;i<n;i++){
		//We go to each row and generate a row the size needed
		tri_matrix[i].ligne = vector<float>(i);
		for(int j=0; j<i;j++){
			// For each pair we aligned using the Class_align and it's function. It needed two matrix
			score = run_align_global_score(trace_list[i],trace_list[j]);
			tri_matrix[i].ligne[j] = score;
			tri_matrix[i].header = trace_list[i].header;

		}
	}
	return tri_matrix;
}


//****************************************************************
/*
$$$$$$$\                                                $$\     $$\                               
$$  __$$\                                               $$ |    \__|                              
$$ |  $$ | $$$$$$\   $$$$$$\  $$\  $$$$$$\   $$$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$$\ 
$$$$$$$  |$$  __$$\ $$  __$$\ \__|$$  __$$\ $$  _____|\_$$  _|  $$ |$$  __$$\ $$  __$$\ $$  _____|
$$  ____/ $$ |  \__|$$ /  $$ |$$\ $$$$$$$$ |$$ /        $$ |    $$ |$$ /  $$ |$$ |  $$ |\$$$$$$\  
$$ |      $$ |      $$ |  $$ |$$ |$$   ____|$$ |        $$ |$$\ $$ |$$ |  $$ |$$ |  $$ | \____$$\ 
$$ |      $$ |      \$$$$$$  |$$ |\$$$$$$$\ \$$$$$$$\   \$$$$  |$$ |\$$$$$$  |$$ |  $$ |$$$$$$$  |
\__|      \__|       \______/ $$ | \_______| \_______|   \____/ \__| \______/ \__|  \__|\_______/ 
                        $$\   $$ |                                                                
                        \$$$$$$  |                                                                
                         \______/                                                                 
*/
void Multi_Align::print_align(vector<Type_trace> list_aligned){
	int word, word_max, length_seq;
	string sequence;
	int word_length_max = 1;
	cout << "Taille: " << list_aligned.size() << endl;
	cout << "NOM SEQ: " << "TAILLE\t" << "SEQUENCE\n";
	for(int n=0;n<list_aligned.size();n++){
		sequence = list_aligned[n].header + ' ';
		length_seq = list_aligned[n].sequence.size();
		sequence += to_str(length_seq) + "\t";
		for(int i=0; i<list_aligned[n].sequence.size();i++){
			for(int j=0;j<list_aligned.size();j++){
				//words.push_back(trace_align[j].sequence[i]);
				word_max = list_aligned[j].sequence[i];
				if(word_length(word_max) > word_length_max){
					word_length_max = word_length(word_max);
				}
			}
			//cout << word_length_max << '/';
			word = list_aligned[n].sequence[i];
			sequence += word_to_string(word) + ' ';
			//sequence += ' '*(word_length_max-word_length(word));
		}
		//cout << endl;
		cout << sequence + 'S' << endl;
		//for(int i=0;i<list_aligned[n].sequence.size();i++) cout << list_aligned[n].sequence[i] << ' ';
		//cout << endl;
	}
}
//****************************************************************
bool node_before_leaf(TArbreBin<string> *node){
	if((node -> fg -> fg == NULL) &&
		(node -> fg -> fd == NULL) &&
		(node -> fd -> fg == NULL) &&
		(node -> fd -> fd == NULL)){
			return true;
		} else return false;
}
//****************************************************************
void find_pair_in_tree(TArbreBin<string> *node, tree_ptr* &pair, float &value_max){
	float value;
	if(node != NULL){
		value = atof((node->data).c_str());
		if (value > value_max && node_before_leaf(node) ){value_max = value; pair -> node = node;}
		find_pair_in_tree(node -> fg, pair, value_max);
		find_pair_in_tree(node -> fd, pair, value_max);
	}
}
//****************************************************************
vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &root,
													TArbreBin<string>* &copy_pair,
													vector<Type_trace> trace_list,
													vector<Type_trace> &list_aligned,
													float score_prec,
													string &name_remove, string &name_kept){
	vector<Type_trace> trace_to_align;
	tree_ptr *pair;
	float value_max = 0.0;
	int score, i = 0;
	bool trouver, trouver1, trouver2;
	trouver = trouver1 = trouver2 = false;
	Type_trace trace_1, trace_2, trace_align_1, trace_align_2, last_trace;
	int index_trace_1, index_trace_2;
	string pair_name;

	//*##### PROTECTION OF LAST TRACE 	#####
	last_trace = trace_list[trace_list.size()-1];

	pair -> node = new TArbreBin<string>("pomme");
	//*##### SEARCHING PAIR 			#####
	find_pair_in_tree(root, pair, value_max);

	//*##### PAIR FOUND: PROJECTION 	#####
	while(i<trace_list.size() && !trouver){
		if(pair -> node -> fg -> data == trace_list[i].header){trace_1 = trace_list[i]; trouver1 = true;}
		if(pair -> node -> fd -> data == trace_list[i].header){trace_2 = trace_list[i]; trouver2 = true;}
		//if(name_remove == trace_list[i].header){trace_1 = trace_list[i]; trouver1 = true;}
		//if(name_kept == trace_list[i].header){trace_2 = trace_list[i]; trouver2 = true;}
		if(trouver1 && trouver2){trouver = true;}
		i++;
	}

	// Because corruption of last trace
	if(trace_1.header == last_trace.header){
		trace_1.sequence = last_trace.sequence;
	} else if ( trace_2.header == last_trace.header){
		trace_2.sequence = last_trace.sequence;
	}
	run_align_global(trace_1,trace_2,trace_align_1,trace_align_2, list_aligned, score);

	for(int i=0;i<trace_list.size();i++){
		if(trace_list[i].header == trace_1.header) {index_trace_1 = i; trace_list[i].sequence = trace_align_1.sequence;}
		if(trace_list[i].header == trace_2.header) {index_trace_2 = i; trace_list[i].sequence = trace_align_2.sequence;}
	}
	move(trace_list,index_trace_2,index_trace_1+1);

	//*##### ADD PAIR TO FINAL_TREE #####
	//copy_pair -> printBTS();
	//cout << " Create pair\n";
	copy_pair = pair -> node;
	//cout << to_str(score) << endl;
	//copy_pair = new TArbreBin<string>(to_str(score));
	//cout << copy_pair -> data << " fzoei,f\n";
	//copy_pair -> fg = new TArbreBin<string>(trace_1.header);
	//copy_pair -> fd = new TArbreBin<string>(trace_2.header);
	//copy_pair -> printBTS();
	
	//print_Type_trace(trace_1);
	trace_align_1.header = trace_1.header;
	//print_Type_trace(trace_align_1);
	/*for(int i=0;i<trace_align_1.sequence.size();i++){
		if(trace_align_1[i] != trace_1){

		}
	}*/

	//*##### RETURN AND DELETE NODE #####
	name_remove = trace_1.header;
	name_kept = trace_2.header;
	pair_name = trace_1.header + trace_2.header;
	//pair -> node -> fg = NULL;
	//pair -> node -> fd = NULL;
	//pair -> node -> data = name_kept;
	//print_Type_trace(trace_list[trace_list.size()-1]);
	return trace_list;
}

vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &pair,
													vector<Type_trace> &trace_list,
													vector<Type_trace> &list_aligned,
													const float &score_prec,
													string &name_remove, string &name_kept){
	vector<Type_trace> trace_to_align;
	float value_max = 0.0;
	int score, i = 0;
	bool trouver, trouver1, trouver2;
	trouver = trouver1 = trouver2 = false;
	Type_trace trace_1, trace_2, trace_align_1, trace_align_2, last_trace;
	int index_trace_1, index_trace_2;
	string pair_name;
	cluster_trace* pair_trace;

	//*##### PROTECTION OF LAST TRACE 	#####
	last_trace = trace_list[trace_list.size()-1];

	//*##### SEARCHING PAIR 			#####
	pair = new TArbreBin<string>(to_str<float>(score_prec));
	pair -> fg = new TArbreBin<string>(name_remove);
	pair -> fd = new TArbreBin<string>(name_kept);

	//*##### PAIR FOUND: PROJECTION 	#####
	cout << name_remove << " - " << name_kept << endl;
	while(i<trace_list.size() && !trouver){
		if(name_remove == trace_list[i].header){trace_1 = trace_list[i]; trouver1 = true;}
		if(name_kept == trace_list[i].header){trace_2 = trace_list[i]; trouver2 = true;}
		if(trouver1 && trouver2){trouver = true;}
		i++;
	}

	pair_trace -> trace = trace_2;
	pair_trace -> next = new cluster_trace;
	pair_trace -> next ->trace =trace_1;
	// Because corruption of last trace
	if(trace_1.header == last_trace.header){
		trace_1.sequence = last_trace.sequence;
	} else if ( trace_2.header == last_trace.header){
		trace_2.sequence = last_trace.sequence;
	}
	run_align_global(trace_1,trace_2,trace_align_1,trace_align_2, list_aligned, score);

	/*print_Type_trace(trace_1);
	print_Type_trace(trace_2);
	print_Type_trace(trace_align_1);
	print_Type_trace(trace_align_2);*/
	for(int i=0;i<trace_list.size();i++){
		if(trace_list[i].header == trace_1.header) {index_trace_1 = i; trace_list[i].sequence = trace_align_1.sequence;}
		if(trace_list[i].header == trace_2.header) {index_trace_2 = i; trace_list[i].sequence = trace_align_2.sequence;}
	}
	move(trace_list,index_trace_2,index_trace_1+1);

	//*##### ADD PAIR TO FINAL_TREE #####
	return trace_list;
}

//****************************************************************
void insert_gap_by_pair(Type_trace &trace_1, Type_trace &trace_2){
	for(int i=0;i<trace_2.sequence.size();i++){
		if(trace_2.sequence[i] == -1){

		}
	}
}

//****************************************************************
/*
 $$$$$$\                                       $$\      $$\  $$$$$$\   $$$$$$\  
$$  __$$\                                      $$$\    $$$ |$$  __$$\ $$  __$$\ 
$$ /  \__| $$$$$$\   $$$$$$\   $$$$$$\         $$$$\  $$$$ |$$ /  \__|$$ /  $$ |
$$ |      $$  __$$\ $$  __$$\ $$  __$$\        $$\$$\$$ $$ |\$$$$$$\  $$$$$$$$ |
$$ |      $$ /  $$ |$$ |  \__|$$$$$$$$ |       $$ \$$$  $$ | \____$$\ $$  __$$ |
$$ |  $$\ $$ |  $$ |$$ |      $$   ____|       $$ |\$  /$$ |$$\   $$ |$$ |  $$ |
\$$$$$$  |\$$$$$$  |$$ |      \$$$$$$$\        $$ | \_/ $$ |\$$$$$$  |$$ |  $$ |
 \______/  \______/ \__|       \_______|$$$$$$\\__|     \__| \______/ \__|  \__|
                                        \______|                                
                                                                                
*/
void sort_trace_list(TArbreBin<string>* node,
					vector<Type_trace> trace_align,
					vector<Type_trace> &trace_align_sorted){
	if(node != NULL){
		int i=0;
		while(node -> data != trace_align[i].header && i < trace_align.size()){
			i++;
		}
		if(i < trace_align.size()){
			trace_align_sorted.push_back(trace_align[i]);
		}
		sort_trace_list(node ->fg, trace_align, trace_align_sorted);
		sort_trace_list(node ->fd, trace_align, trace_align_sorted);
	}
}
//****************************************************************
// TODO FINISH THIS GODDAMN MOTHERFUCKER
// le nombre de séquences
void Multi_Align::multiple_alignment(float seuil){
	//##### INIT VAR	#####
	TArbreBin<string> *T,*T_prec, *tree_final, *copy_pair;
	vector<TArbreBin<string>*> subtrees;
	vector<string> seq_prec_vector;
	trace_align = trace_list;
	vector<Type_trace> list_aligned, trace_align_sorted;
	vector<matri> D(trace_list.size()); vector<matri> D_prec(trace_list.size());
	bool convergence;
	float score, score_final = 0.0;
	string name_remove, name_kept;
	// List of sequences is define in the class
	// type_alignment is a vector of traces define in the class: trace_align

	//*##### DEBUT		#####
	convergence = false;
	create_tringular_matrix(D_prec);
	cout << "- Number of sequences: " << number_of_traces << endl;

	int i = 1;
	cout << "# Début boucle\n";
	while(i < number_of_traces){ 
		if(i==1){
			cout << "# Dissimilarity\n";
			D = calcul_dissimilarite(trace_list);
			cout << "- Calcul réussi\n";
		} else { // We have already done a multiline alignment
			D = calcul_dissimilarite(trace_align);
			if(i==number_of_traces-1){
				trace_align[trace_align.size()-1] = trace_list[number_of_traces-1];
			}
		}	
		//if(difference(D,D_prec) <= seuil){convergence = true; break;}
		// convergence = false
		CAH(D, T, score, name_remove, name_kept);
		cout << "##CAH" << name_remove << " - " << name_kept << endl;
		if(i<2){
			T_prec = T;
			//cout << "================= Affichage alignment multiple ===\n";
			//T_prec -> printBTS();
		}
		//T ->printBTS();
		//trace_align = aligner_sequences_ou_projection(T, copy_pair, trace_align, list_aligned, score, name_remove, name_kept);

		trace_align = aligner_sequences_ou_projection(copy_pair, trace_align, list_aligned, score, name_remove, name_kept);
		//T -> printBTS();
		//*##### BUILD FINAL TREE #####
		//cout << "================= Affichage arbre ===\n";
		//copy_pair -> printBTS();	
		//T ->printBTS();
		build_final_tree(subtrees, seq_prec_vector, copy_pair, tree_final, name_remove, name_kept);
		tree_final -> printBTS();
		//*##### REMOVE ONE TRACE OF THE PAIR WHICH WAS PROJECTED #####
		//trace_list = trace_align;
		int cpt = 0;
		while(trace_align[cpt].header != name_remove){
			cpt++;
		}
		cout << cpt << " : " << trace_align.size() << endl;
		list_aligned.push_back(trace_align[cpt]);
		cout << "   dz  \n";


		trace_align.erase(trace_align.begin() + cpt);
		trace_align.shrink_to_fit();
		cout << " ngizenfg \n";
		D_prec = D;
		print_Type_trace(trace_align[trace_align.size()-1]);
		cout << "qeonfq ze\n";
		score_final += score;
		cout << "----------- FIN TOUR " << i << endl;
		i++;
	}

	// We add the final trace to the list of aligned traces.
	list_aligned.push_back(trace_align[0]);

	//###### PRINTING THE MULTIPLE TRACES ALIGNEMENT ######
	cout << "================= Affichage arbre complet ===\n";
	T_prec -> printBTS();
	//tree_final -> printBTS();
	sort_trace_list(T_prec, list_aligned, trace_align_sorted);

	cout << "================= Affichage alignment multiple ===\n";
	print_align(list_aligned);
	cout << "== Score: " << score_final << endl;
}