/*#########################################
## 01/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: main_TraceON.cpp
###########################################*/
//#include "alignment.hpp"
#include "trace_generator.hpp"
#include <random>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;
//#######################################################################################//
int main(int argc, char *argv[]){ // Use argv to pass the expression as parameter
	string parameter;
	parameter = argv[1];
    smatch trace, cas_1, cas_2;
	string anchor_list;
	string test_cas;
    string sequence;
	string temporary_anchor;
	int first_anchor_value;
    bloc a;

	int trace_nb = 20;
	string trace_output[trace_nb] = {""};
	int trace_length = 20;

	// Create and open a text file
 	ofstream Trace_file(argv[2]);

	cout << "Utilisations des paramètres: " << parameter << endl;

	// We verify if the first anchor exist (\033[1;31m is used to print error in red)
	if(!regex_search(parameter,trace,regex("(^E[0-9]*)"))){
			cout << "\033[1;31m Error, expression doesn't start with an anchor (ex: E1)\033[0m\n";
			return 1;
	}
    while(parameter[0] != "S"[0]){
        // We find and take the first anchor by using regex
		regex_search(parameter,trace,regex("(^E[0-9]*)"));

		// For number of trace, we add to each one the first anchor.
		for(int trace_cpt=0;trace_cpt<trace_nb;trace_cpt++){
			trace_output[trace_cpt] += trace.str(1) + ' ';
		}

		// To pass the anchor if needed in cases +, *, |... and then take it's value
		temporary_anchor=trace.str(1);
		first_anchor_value = atoi(temporary_anchor.substr(1,temporary_anchor.length()-1).c_str());
        
		// We remove the anchor from the expression string
		parameter.erase(0,trace.str(1).length());

		// We test the different cases
		//########################	The first case: ()	##########################
        if(parameter[0]=='('){
			for(int trace_cpt=0;trace_cpt<trace_nb;trace_cpt++){
	            a.set_temps();
    	        a.set_seq(a.parentheses());
				trace_output[trace_cpt] += a.get_bloc();
			}
			parameter.erase(0,2);

		//########################	Else we are on case: <()>	##################
        } else {
			if(parameter[3]=='>'){
				cout << "\033[1;31mError in case expression\n";
				cout << parameter[3] << " instead of +, * or E..|E..\033[0m\n" ;
				break;
			}
			if(parameter[3]=='+' || parameter[3]=='*'){
				cout << "Cas +\n";
				for(int trace_cpt=0;trace_cpt<trace_nb;trace_cpt++){
					a.set_temps();
					a.crochets_plus_or_star(first_anchor_value,parameter[3]);
					trace_output[trace_cpt] += a.get_bloc();
				}
				//cout << "Add and erase\n";
				parameter.erase(0,5);
			} else {
				regex_search(parameter,cas_1,regex("(E[0-9X]*[>\\|])"));
				test_cas += cas_1.str(1);
				switch(test_cas.back()){
					case '>':{
						anchor_list += cas_1.str(1); // To stock the match ()
						anchor_list.pop_back(); 	 // and remove the '>'
						cout << "Cas |: " << anchor_list << endl;
						for(int trace_cpt=0;trace_cpt<trace_nb;trace_cpt++){
							a.set_temps();
							a.crochets_pipe(first_anchor_value,anchor_list);
							trace_output[trace_cpt] += a.get_bloc();
						}
						parameter.erase(0,(anchor_list.length()+4));
					}
						break;
					case '|':{
						regex_search(parameter,cas_2,regex("([|E0-9X]*\\|E[0-9X]*)"));
						anchor_list += cas_2.str(1);
						cout << "Cas |: " << anchor_list << endl;
						for(int trace_cpt=0;trace_cpt<trace_nb;trace_cpt++){
							a.set_temps();
							a.crochets_pipe(first_anchor_value,anchor_list);
							trace_output[trace_cpt] += a.get_bloc();
						}
						parameter.erase(0,(anchor_list.length()+4));
					}
						break;
					default:
						cout << "\033[1;31mError in case expression\033[0m\n";
						return 1;
				}
				
			}
		}

        //cout << "Paramètre coupé: " << parameter << endl;
    }

	//########################	At the end we add S and print to file	##########
    for(int trace_cpt=0;trace_cpt<20;trace_cpt++){
		trace_output[trace_cpt] += "S";
		Trace_file << "Trace_" << trace_cpt+1 << "| " << trace_output[trace_cpt] << endl;
	}
    
	Trace_file.close();
    return 0;
}