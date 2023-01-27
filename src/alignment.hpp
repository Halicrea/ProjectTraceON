/*#########################################
## 17/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: alignment.hpp
###########################################*/
#include "pairwize_global.hpp"
#include "clustering.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP
//***********************  CLASS MULTIPLE ALIGNMENT ***********************
class Multi_Align{
	int number_of_traces;
	vector<Type_trace> trace_list;
	vector<Type_trace> trace_align;
	public:
		Multi_Align(){
			number_of_traces = 0;
			trace_list;
			trace_align;
		}
		void init_trace_list(string file_name);
		void multiple_alignment(float seuil, int gap_start, int gap_weight);
		void print_align(vector<Type_trace> list_aligned);
		void export_align(string file_name);

};

//***********************  FUNCTIONS DECLARATION **************************
void print_Type_trace(Type_trace trace);

int gap_weigth(int gap_initial, int gap_penalty, int& gap_length);

int del(int event, int gap_initial, int gap_penalty, int& gap_length);
int ins(int event, int gap_initial, int gap_penalty, int& gap_length);
int subst(int event, int event2);
void max(int insert, int delet, int substit, char *ptr, int& gap_length, int& result);


/*void Class_align::init_matrix_align(int n, int m,int gap_initial, int gap_penalty);
void  Class_align::print_matrice(int n, int m);
void  Class_align::print_M_match(int n, int m);
void Class_align::alignment_global_pairwize(vector<int> &Alignment1,vector<int> &Alignment2, int gap_initial, int gap_penalty);
*/
int word_length(int word);
string word_to_string(int word);

/*void Class_align::print_Alignment(Type_trace trace1, Type_trace trace2);*/
float difference(vector<matri> &D,vector<matri> &D_prec);
vector<matri> calcul_dissimilarite(vector<Type_trace> trace_list);


vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &root,
													TArbreBin<string>* &copy_pair,
													vector<Type_trace> trace_list,
													vector<Type_trace> &list_aligned,
													float &score_prec,
													string &name_remove, string &name_kept,
													int gap_start, int gap_weight);
vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &pair,
													vector<Type_trace> &trace_list,
													vector<Type_trace> &list_aligned,
													const float &score_prec,
													string &name_remove, string &name_kept,
													int gap_start, int gap_weight);
void build_final_tree( vector<TArbreBin<string>*> &subtrees,
							vector<string> &seq_prec_vector,
							TArbreBin<string>* pair_copy, TArbreBin<string>* &root,
							string name_remove, string name_kept);

//fonction permettant de compter le nombre de gap et d'afficher un score 
int gap_count(vector<Type_trace> trace_align_sorted);
float gap_score(vector<Type_trace> trace_align_sorted, int trace_nb);

#endif