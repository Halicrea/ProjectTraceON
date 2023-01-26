/*#########################################
## 26/01/2023
## Par Elyna Bouchereau & Florent Boyer
## Fichier: pairwize_global.hpp
###########################################*/
#include "struct.hpp"
#include <vector>
#include <string>

#ifndef PAIRWIZE_GLOBAL_HPP
#define PAIRWIZE_GLOBAL_HPP
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
		void alignment_global_pairwize(std::vector<int> &Alignment1,std::vector<int> &Alignment2);
		template<typename T>
		void print_matrice(int n, int m, T** matrix);
		void run_align_pairwize(Type_trace, Type_trace);
};

//***********************  FUNCTIONS DECLARATION **************************
Type_trace trace_to_dict(std::string seq);

void print_Type_trace(Type_trace trace);

int gap_weigth(int gap_initial, int gap_penalty, int& gap_length);

int del(int event, int gap_initial, int gap_penalty, int& gap_length);
int ins(int event, int gap_initial, int gap_penalty, int& gap_length);
int subst(int event, int event2);
void max(int insert, int delet, int substit, char *ptr, int& gap_length, int& result);

template <typename T> std::string to_str(const T& t);

void run_align_global(Type_trace &trace_1, Type_trace &trace_2);
void run_align_global(Type_trace trace_1, Type_trace trace_2, Type_trace &trace_align_1, Type_trace &trace_align_2, int &score);
int run_align_global_score(Type_trace trace_1, Type_trace trace_2);

#endif