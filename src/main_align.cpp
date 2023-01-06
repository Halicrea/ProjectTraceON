/*#########################################
## 17/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: main_align.cpp
###########################################*/
#include "alignment.hpp"
#include "simple_functions.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//################################################################################## Doh, Calligraphy, Broadway, Fraktur, Poison
/*                                                                                                                   
     *****   **    **           **                *****  *      ***** *     **    
  ******  ***** *****        *****             ******  *     ******  **    **** * 
 **   *  *  ***** *****     *  ***            **   *  *     **   *  * **    ****  
*    *  *   * **  * **         ***           *    *  *     *    *  *  **    * *   
    *  *    *     *           *  **              *  *          *  *    **   *     
   ** **    *     *           *  **             ** **         ** **    **   *     
   ** **    *     *          *    **            ** **         ** **     **  *     
   ** **    *     *          *    **          **** **         ** **     **  *     
   ** **    *     *         *      **        * *** **         ** **      ** *     
   ** **    *     **        *********           ** **         ** **      ** *     
   *  **    *     **       *        **     **   ** **         *  **       ***     
      *     *      **      *        **    ***   *  *             *        ***     
  ****      *      **     *****      **    ***    *          ****          **     
 *  *****           **   *   ****    ** *   ******          *  *****              
*     **                *     **      **      ***          *     **               
*                       *                                  *                      
 **                      **                                 **                    
*/
int main(){
	int gap_initial = 4;
	int gap_penalty = 1;
	string seq1 = "Trace_1| E1 E2 E8 - - - - - E8 E13 - E13 E13 - E89 E14 E15 E26 E22 E24 - E28 - - - E53 - - - - E31 - E49 - - E33 - - E52 E48 - S";
	Type_trace seq1_sub = trace_to_dict(seq1);
	string seq2 = "Trace_2| E1 E2 - - E2 E2 - - E2 E2 - E8 - - - E8 E13 E13 E13 E89 - E14 E15 E30 - - E24 - E28 E40 E55 E31 E43 E42 - E61 E35 - E59 E61 E42 E58 S";
	Type_trace seq2_sub = trace_to_dict(seq2);
	print_Type_trace(seq1_sub);
	print_Type_trace(seq2_sub);

	int n = seq1_sub.sequence.size();
	int m = seq2_sub.sequence.size();
	int** M = new int* [n+1];
	for(int i=0; i< n+1; i++){
		M[i] = new int [m+1];
	}
	char** M_match = new char* [n+1];
	for(int i=0; i< n+1; i++){
		M_match[i] = new char [m+1];
	}

	Class_align align_pairwize(seq1_sub,seq2_sub, M, M_match);

	align_pairwize.init_matrix_align(n ,m,gap_initial,gap_penalty);
	cout << "==================================================\n";
	cout << "Voulez vous afficher la matrice ?(non:0 oui:1) ";
	if(input() == 1){
		align_pairwize.print_matrice(n ,m);
		align_pairwize.print_M_match(n ,m);
	}
	vector<int> Alignment1;
	vector<int> Alignment2;
	align_pairwize.alignment_global_pairwize(Alignment1,Alignment2,gap_initial,gap_penalty);
	cout << "## Score: " << M[n][m] << endl;
	Type_trace Seq_align1;
	Seq_align1.header = seq1_sub.header;
	Seq_align1.sequence = Alignment1;
	Type_trace Seq_align2;
	Seq_align2.header = seq2_sub.header;
	Seq_align2.sequence = Alignment2;
	// On affiche l'alignement
	align_pairwize.print_Alignment(Seq_align1,Seq_align2);
	return 0;
}