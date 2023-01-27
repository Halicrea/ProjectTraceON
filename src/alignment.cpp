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
//****************		STRUCT				**********************
struct tree_ptr{
	TArbreBin<string>* node;
};


//****************************************************************
/*
	Move a value in a vector to a specific index.
*/
// https://stackoverflow.com/questions/45447361/how-to-move-certain-elements-of-stdvector-to-a-new-index-within-the-vector
template <typename t> void move(vector<t>& v, size_t oldIndex, size_t newIndex)
{
    if (oldIndex > newIndex){
		rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
	} else {
		rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
	}
}
//****************************************************************
/*
	Find a value in a vector and return the index.
*/
template <typename T>
int finder(vector<Type_trace> list, T val){
	int i=0;
	while(i<list.size() && list[i].header != val){
		 if(list[i].header == val) return i;
	}
	return list.size()-1;
}

//#################################################################
/*
	Print a pretty tree.
	└──A
		├──B
		│   ├──R
		│   └──S
		└──C
			└──D

*///****************************************************************
template<typename T>
void TArbreBin<T>::printBTS(){
	this -> printBTS("",false);
}
//****************************************************************
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



//#################################################################
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
	Constructor for the classe Multi_Align.
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
	Problem with this function, making most of the code breaking.
*/
float difference(vector<matri> &D,vector<matri> &D_prec){
	cout << "- Calcul difference\n";
	int distance = 0; // We initialize the distance between the two matrix
	int n = D.size();
	//cout << D[0].ligne[0] << endl;
	for(int i=1; i<n;i++){
		//cout << 'i' << i << '-';
		for(int j=0;j<D[i].ligne.size();j++){
			//cout << D_prec[i].ligne[j] << " % " << D[i].ligne[j];
			//distance = distance + pow(D_prec[i].ligne[j]-D[i].ligne[j],2);
		}
	}
	distance = (2*distance)/n*(n-1);
	distance = sqrt(distance);
	return distance;
}
//****************************************************************
/*
	A simple random generator for making dummy triangular matrix.
*/
float random_val(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1,50);
	return distr(gen);
}
//****************************************************************
/*
	Was used to initialize a triangular matrix.
*/
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
//****************************************************************
/*
	Can be used to print a triangular lower matrix.
*/
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
vector<matri> calcul_dissimilarite(vector<Type_trace> trace_list, int gap_start, int gap_weight){
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
			score = run_align_global_score(trace_list[i],trace_list[j], gap_start, gap_weight);
			tri_matrix[i].ligne[j] = score;
			tri_matrix[i].header = trace_list[i].header;

		}
	}
	return tri_matrix;
}


//################################################################
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
//****************************************************************
/*
	Translate the vector of aligned traces to print it in a file
	or to the terminal.
*/
string Multi_Align::print_align(vector<Type_trace> list_aligned, float score_final){
	int word, word_max, length_seq;
	string sequence = "";
	int word_length_max = 1;
	sequence += "Taille: " + to_str<int>(list_aligned.size()) + '\n';
	sequence += "NOM SEQ: ";
	sequence += "TAILLE\t";
	sequence += "SEQUENCE\n";
	for(int n=0;n<list_aligned.size();n++){
		sequence += list_aligned[n].header + ' ';
		length_seq = list_aligned[n].sequence.size();
		sequence += to_str(length_seq) + "\t";
		for(int i=0; i<list_aligned[n].sequence.size();i++){
			for(int j=0;j<list_aligned.size();j++){
				//words.push_back(trace_align[j].sequence[i]); --> To align properly words, but tendance for corruption
				word_max = list_aligned[j].sequence[i];
				if(word_length(word_max) > word_length_max){
					word_length_max = word_length(word_max);
				}
			}
			word = list_aligned[n].sequence[i];
			sequence += word_to_string(word) + ' ';
			//sequence += ' '*(word_length_max-word_length(word));   --> To align properly words, but tendance for corruption
		}
		sequence += "S\n";

	}
	sequence += "== Score: " + to_str<float>(score_final) + '\n';
	return sequence;
}
//****************************************************************
/*
	Check if the node is before two leaves.
*/
bool node_before_leaf(TArbreBin<string> *node){
	if((node -> fg -> fg == NULL) &&
		(node -> fg -> fd == NULL) &&
		(node -> fd -> fg == NULL) &&
		(node -> fd -> fd == NULL)){
			return true;
		} else return false;
}
//****************************************************************
/*
	Searching for the best pair in a tree.
*/
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
/*
	The role of this function is to find the pair to project, align
	correctly and keep in memory the score (for the score final) as
	well as a subtree. This subtree will be used to build the final
	"phylogenetic" tree. This version work by searching in the tree
	produced by CAH.
*/
vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &root,
													TArbreBin<string>* &copy_pair,
													vector<Type_trace> trace_list,
													vector<Type_trace> &list_aligned,
													float &score_prec,
													string &name_remove, string &name_kept,
													int gap_start, int gap_weight){
	vector<Type_trace> trace_to_align;
	tree_ptr *pair;
	float value_max = 0.0;
	int score, i = 0;
	bool trouver, trouver1, trouver2;
	trouver = trouver1 = trouver2 = false;
	Type_trace trace_1, trace_2, trace_align_1, trace_align_2, last_trace;
	int index_trace_1, index_trace_2;
	string pair_name;
	cout << "------------------\n";
	//*##### PROTECTION OF LAST TRACE 	#####
	last_trace = trace_list[trace_list.size()-1];

	pair -> node = new TArbreBin<string>("pomme");

	cout << "------------------\n";
	//*##### SEARCHING PAIR 			#####
	find_pair_in_tree(root, pair, value_max);

	//*##### PAIR FOUND: PROJECTION 	#####
	while(i<trace_list.size() && !trouver){
		if(pair -> node -> fg -> data == trace_list[i].header){trace_1 = trace_list[i]; trouver1 = true;}
		if(pair -> node -> fd -> data == trace_list[i].header){trace_2 = trace_list[i]; trouver2 = true;}
		if(trouver1 && trouver2){trouver = true;}
		i++;
	}

	if(trace_1.header == last_trace.header){
		trace_1.sequence = last_trace.sequence;
	} else if ( trace_2.header == last_trace.header){
		trace_2.sequence = last_trace.sequence;
	}
	cout << "------------------\n";
	run_align_global(trace_1,trace_2,trace_align_1,trace_align_2, list_aligned, score, gap_start, gap_weight);

	for(int i=0;i<trace_list.size();i++){
		if(trace_list[i].header == trace_1.header) {index_trace_1 = i; trace_list[i].sequence = trace_align_1.sequence;}
		if(trace_list[i].header == trace_2.header) {index_trace_2 = i; trace_list[i].sequence = trace_align_2.sequence;}
	}
	move(trace_list,index_trace_2,index_trace_1+1);

	//*##### ADD PAIR TO FINAL_TREE #####
	copy_pair = pair -> node;

	trace_align_1.header = trace_1.header;

	score_prec += score;
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

//****************************************************************
/*
	The role of this function is to find the pair to project, align
	correctly and keep in memory the score (for the score final) as
	well as a subtree. This subtree will be used to build the final
	"phylogenetic" tree.
*/
vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &pair,
													vector<Type_trace> &trace_list,
													vector<Type_trace> &list_aligned,
													const float &score_prec,
													string &name_remove, string &name_kept,
													int gap_start, int gap_weight){
	vector<Type_trace> trace_to_align;
	float value_max = 0.0;
	int score, i = 0;
	bool trouver, trouver1, trouver2;
	trouver = trouver1 = trouver2 = false;
	Type_trace trace_1, trace_2, trace_align_1, trace_align_2, last_trace;
	int index_trace_1, index_trace_2;
	string pair_name;

	

	//*##### SEARCHING PAIR 			#####
	pair = new TArbreBin<string>(to_str<float>(score_prec));
	pair -> fg = new TArbreBin<string>(name_remove);
	pair -> fd = new TArbreBin<string>(name_kept);

	//cout << "# TEST " << trace_list.size() << endl;
	if(trace_list.size() == 2){
		print_Type_trace(trace_list[0]);
		print_Type_trace(trace_list[1]);
		//cout << "LAST PAIR \n";
		//cout << "-";
		index_trace_1 = 0;
		index_trace_2 = 1;
		//cout << "-";
		trace_1 = trace_list[index_trace_1];
		trace_2 = trace_list[index_trace_2];
		//cout << "-";
		run_align_global(trace_1,trace_2,trace_align_1,trace_align_2, list_aligned, score, gap_start, gap_weight);
		//cout << "-";
		
		trace_list[index_trace_1].sequence = trace_align_1.sequence;
		trace_list[index_trace_2].sequence = trace_align_2.sequence;
		//cout << "-";
		return trace_list;
	}
	//*##### PROTECTION OF LAST TRACE 	#####
	last_trace = trace_list[trace_list.size()-1];

	//*##### PAIR FOUND: PROJECTION 	#####
	while(i<trace_list.size() && !trouver){
		if(name_remove == trace_list[i].header){trace_1 = trace_list[i]; trouver1 = true;}
		if(name_kept == trace_list[i].header){trace_2 = trace_list[i]; trouver2 = true;}
		if(trouver1 && trouver2){trouver = true;}
		i++;
	}

	// Because corruption of last trace
	if(trace_1.header == last_trace.header){
		trace_1.sequence = last_trace.sequence;
	} else if ( trace_2.header == last_trace.header){
		trace_2.sequence = last_trace.sequence;
	}
	run_align_global(trace_1,trace_2,trace_align_1,trace_align_2, list_aligned, score, gap_start, gap_weight);

	/*print_Type_trace(trace_1);
	print_Type_trace(trace_2);
	print_Type_trace(trace_align_1);
	print_Type_trace(trace_align_2);*/
	for(int i=0;i<trace_list.size();i++){
		if(trace_list[i].header == trace_1.header) {index_trace_1 = i; trace_list[i].sequence = trace_align_1.sequence;continue;}
		if(trace_list[i].header == trace_2.header) {index_trace_2 = i; trace_list[i].sequence = trace_align_2.sequence;continue;}
	}

	//cout << trace_list.size() << endl;
	if(trace_list.size()> 2){
		//cout << index_trace_1 << " - " << index_trace_2 << endl;
		move(trace_list,index_trace_2,index_trace_1);
	}

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

//##################################################################
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
//****************************************************************
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
void Multi_Align::multiple_alignment(string file_traces, string file_MSA_output,
						string file_score_output,
						float seuil, int gap_start, int gap_weight){
	//*##### INIT VAR	#####
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
	/* 
		Loop on the number of traces, but for the last loop it break
		so the last one isn't align for now.
	*/
	while(i < number_of_traces-1){ 
		if(i==1){
			D = calcul_dissimilarite(trace_list, gap_start, gap_weight);
		} else { // We have already done a multiline alignment
			D = calcul_dissimilarite(trace_align, gap_start, gap_weight);
			if(i==number_of_traces-1){
				trace_align[trace_align.size()-1] = trace_list[number_of_traces-1];
			}
		}	
		//if(difference(D,D_prec) <= seuil){convergence = true; break;}
		// convergence = false

		// Hierarchical clustering
		CAH(D, T, score, name_remove, name_kept);
		if(i<2){
			T_prec = T;
		}

		// Use the CAH for projection of the best pair
		trace_align = aligner_sequences_ou_projection(copy_pair, trace_align, list_aligned, score, name_remove, name_kept, gap_start, gap_weight);
		//*##### BUILD FINAL TREE #####

		build_final_tree(subtrees, seq_prec_vector, copy_pair, tree_final, name_remove, name_kept);

		//*##### REMOVE ONE TRACE OF THE PAIR WHICH WAS PROJECTED #####
		//trace_list = trace_align;
		int cpt = 0;
		while(trace_align[cpt].header != name_remove){
			cpt++;
		}

		list_aligned.push_back(trace_align[cpt]);
		trace_align.erase(trace_align.begin() + cpt);
		D_prec = D;
		score_final += score;
		cout << "----------- FIN TOUR " << i << endl;
		i++;
	}

	// We add the final trace to the list of aligned traces.
	list_aligned.push_back(trace_align[0]);

	//*###### PRINTING THE MULTIPLE TRACES ALIGNEMENT ######
	cout << "================= Affichage arbre complet ===\n";
	T_prec -> printBTS();
	//tree_final -> printBTS();
	sort_trace_list(T_prec, list_aligned, trace_align_sorted);

	cout << "================= Affichage alignment multiple ===\n";
	cout << print_align(trace_align_sorted, score_final);
	trace_align = trace_align_sorted;

	//*###### PRINTING THE MULTIPLE TRACES ALIGNEMENT ######
	this -> root = tree_final;
	this -> export_align(file_traces, file_MSA_output, file_score_output, trace_align_sorted, score_final);
}

//****************************************************************
/*
	Export the alignment in a file with it's metadata.
*/
void Multi_Align::export_align(string file_traces, string file_MSA_output,
				string file_score_output, vector<Type_trace> trace_align_sorted,
				float score_final){
	// Create and open a text file
 	ofstream MSA_output(file_MSA_output);
	MSA_output << print_align(trace_align_sorted, score_final);
	MSA_output.close();

	float score_gap;
	score_gap = gap_score(trace_align_sorted);
	ofstream score_ouput(file_score_output);
	score_ouput << "Input file;" << "score_nw;" << "score_gap\n";
	score_ouput << file_traces << ';' << to_str<float>(score_final) << ';' << to_str<float>(score_gap);

	score_ouput.close();
}