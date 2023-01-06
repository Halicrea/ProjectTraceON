/*#########################################
## 17/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: alignment.hpp
###########################################*/
#include <string>
#include <vector>
using namespace std;

struct Type_arbre{
	char valeur;
	Type_arbre* fg;
	Type_arbre* fd;
};
struct Type_trace{
	string header;
	vector<int> sequence;
};

class Class_align{
	Type_trace trace_align1;
	Type_trace trace_align2;
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
		void init_matrix_align(int n, int m,int gap_initial, int gap_penalty);
		void alignment_global_pairwize(vector<int> &Alignment1,vector<int> &Alignment2, int gap_initial, int gap_penalty);
		void print_matrice(int, int);
		void print_M_match (int, int);
};

class Multi_Align{
	int number_of_traces;
	vector<Type_trace> trace_list;
	vector<Type_trace> trace_align;
	public:
		Multi_Align();
		void init_trace_list(string file_name);
		void multiple_alignment(float seuil,int n);
		void print_align(vector<Type_trace> trace_align);
};


//************************************************************

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