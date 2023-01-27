/*#########################################
## 17/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: main_align.cpp
###########################################*/
#include "struct.hpp"
#include "alignment.hpp"
#include "simple_functions.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
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
int main(int argc, char *argv[]){
	//string file_parameter = argv[1];
	/*string file_traces = argv[5];
	string file_MSA_output = argv[6];
	string file_score_output = argv[7];
	string line;
	string s_gap_initial, s_gap_penalty, s_seuil;
	int gap_initial = stoi(argv[1]);
	int gap_penalty = stoi(argv[2]);
	int seuil = stoi(argv[3]);;
	
	bool display_tree = false;
	if(argv[4] == "Yes") display_tree = true;

	//*########################	At the end we add S and print to file	##########
	
	// We check the number of sequences and this length
	cout << "Utilisations des paramètres: " << file_traces << ", " << file_MSA_output << ", " << file_score_output << endl;
	cout << "Init: " << gap_initial << " / " << gap_penalty << " / " << display_tree << endl;*/
	cout << "==================================================\n";
	cout << "                 MULTI ALIGN\n";
	Multi_Align alignement_multiple;
	string file_traces = "Test.txt";
	int seuil = 10, gap_initial = 10, gap_penalty = 1;
	alignement_multiple.init_trace_list(file_traces);
	alignement_multiple.multiple_alignment(seuil, gap_initial, gap_penalty);



	

	return 0;
}