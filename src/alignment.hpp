/*#########################################
## 17/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: alignment.hpp
###########################################*/
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//***********************  STRUCT DECLARATION *****************************
struct Type_trace{
	string header;
	vector<int> sequence;
};
struct matri{
	string header;
	vector<float> ligne;
};

//***********************  CLASS ALIGNMENT ********************************
class Class_align{
	Type_trace trace_align1;
	Type_trace trace_align2;
	int gap_initial = 4;
	int gap_penalty = 1;
	int** M;
	char** M_match;
	public:
		Class_align(Type_trace seq1, Type_trace seq2, int** matrice, char** matrice_fil_de_fer){
			trace_align1 = seq1;
			trace_align2 = seq2;
			M = matrice;
			M_match = matrice_fil_de_fer;
		}
		void print_Alignment(Type_trace, Type_trace);
		void init_matrix_align(int n, int m);
		void alignment_global_pairwize(vector<int> &Alignment1,vector<int> &Alignment2);
		void print_matrice(int, int);
		void print_M_match (int, int);
};
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
		//vector<int>** calcul_dissimilarite(vector<Type_trace> trace_list);
		void multiple_alignment(float seuil);
		void print_align(vector<Type_trace> list_aligned);

};

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

struct tree_ptr{
	TArbreBin<string>* node;
};

//***********************  FUNCTIONS DECLARATION **************************

Type_trace trace_to_dict(string seq);

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
TArbreBin<string>* build_tree(vector<matri> &D_aux, vector<TArbreBin<string>*> &subtrees,
							vector<string> &seq_prec_vector,
							float value, int k, int r);
void CAH(vector<matri> &D, TArbreBin<string>* &root);

void find_pair_in_tree(TArbreBin<string> *node, TArbreBin<string>* &pair, double &value_max);
vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string>* &root,
													vector<Type_trace> trace_list,
													float &score,
													string &name_trace_to_remove);