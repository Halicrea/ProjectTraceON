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
	//int gap_initial = 4;
	//int gap_penalty = 1;
	cout << "==================================================\n";
	cout << "                 MULTI ALIGN\n";
	string file_name = "Test.txt";
	Multi_Align alignement_multiple;
	alignement_multiple.init_trace_list(file_name);
	alignement_multiple.multiple_alignment(10);
	return 0;
}