/*#########################################
## 26/01/2023
## Par Elyna Bouchereau & Florent Boyer
## Fichier: clustering.hpp
###########################################*/
#include "pairwize_global.hpp"
#include "struct.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

//***********************  CLASS BINARY TREE ******************************
template <typename T>
class TArbreBin{
	public:
		TArbreBin* fg;
		TArbreBin* fd;
		T data;
		TArbreBin(T val){
			data = val;
			fg = NULL;
			fd = NULL;
		}
		void delete_tree(TArbreBin* &root, string &pair_name){
			if (this != NULL) {
				// Delete recursively left children.
				this -> delete_tree(root, pair_name);
				// Delete recursively right children.
				this -> delete_tree(root, pair_name);
				
				// Deletion of the node
				if(this != root) {
            		this = NULL;
         		}  else {
					root -> data = pair_name;
				}
			}
		}
		void afficher_arbre(){
			if(this != NULL){
				cout << this -> data << '/';
				this -> fg -> afficher_arbre();
				this -> fg -> afficher_arbre();
			}
		}
		void printBTS(const string&, bool);
		void printBTS();
};
//***********************  FUNCTIONS DECLARATION **************************
TArbreBin<string>* build_tree(vector<matri> &D_aux, vector<TArbreBin<string>*> &subtrees,
							vector<string> &seq_prec_vector,
							float value, int k, int r);
void build_final_tree( vector<TArbreBin<string>*> &subtrees,
							vector<string> &seq_prec_vector,
							TArbreBin<string>* pair_copy, TArbreBin<string>* &root,
							string name_remove, string name_kept);

void CAH(vector<matri> D, TArbreBin<string>* &root,
		float &score, string &name_remove, string &name_kept);

void find_pair_in_tree(TArbreBin<string> *node, TArbreBin<string>* &pair, double &value_max);
vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &root,
													TArbreBin<string>* &copy_pair,
													vector<Type_trace> trace_list,
													float &score,
													string &name_trace_to_remove);


//function to count the number of gaps and display a score 
int gap_count(vector<Type_trace> trace_align_sorted);
float gap_score(vector<Type_trace> trace_align_sorted);
//***********************  STRUCT DECLARATION *****************************

#endif