/*#########################################
## 01/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: main_TraceON.cpp
###########################################*/
//#include "alignment.hpp"
#include "trace_generator.hpp"
#include <random>
#include <iostream>
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

	string trace_output[20] = {""};
	int trace_length = 20;

	cout << "Bienvenu sur ce générateur de traces.\n";
	cout << "Utilisations des paramètres: " << parameter << endl;
    while(parameter[0] != "S"[0]){
        // We find and take the first anchor by using regex
        regex_search(parameter,trace,regex("(^E[0-9]*)"));
		// For number of trace, we add to each one the first anchor.
		for(int trace_cpt=0;trace_cpt<20;trace_cpt++){
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
			for(int trace_cpt=0;trace_cpt<20;trace_cpt++){
	            a.set_temps();
    	        a.set_seq(a.parentheses());
				trace_output[trace_cpt] += a.get_bloc();
			}
			parameter.erase(0,2);

		//########################	Else we are on case: <()>	##################
        } else {
			if(parameter[3]=='+' || parameter[3]=='*'){
				cout << "Cas +\n";
				for(int trace_cpt=0;trace_cpt<20;trace_cpt++){
					a.set_temps();
					a.crochets_plus_or_star(first_anchor_value,parameter[3]);
					trace_output[trace_cpt] += a.get_bloc();
				}
				//cout << "Add and erase\n";
				parameter.erase(0,5);
			} else {
				regex_search(parameter,cas_1,regex("(E[0-9]*\\|)"));
				test_cas += cas_1.str(1);
				if(test_cas.back()=='|'){
					regex_search(parameter,cas_2,regex("([|E0-9X]*\\|E[0-9X]*)"));
					anchor_list += cas_2.str(1);
					cout << "Cas |: " << anchor_list << endl;
					for(int trace_cpt=0;trace_cpt<20;trace_cpt++){
						a.set_temps();
						a.crochets_pipe(first_anchor_value,anchor_list);
						trace_output[trace_cpt] += a.get_bloc();
					}
					parameter.erase(0,(anchor_list.length()+4));
				} else {
					break;
					
				}
				
			}
		}

        //cout << "Paramètre coupé: " << parameter << endl;
    }
	//########################	At the end we add: S	##########################
    for(int trace_cpt=0;trace_cpt<20;trace_cpt++){
		trace_output[trace_cpt] += "S";
		cout << trace_output[trace_cpt] << endl;
	}
    
    return 0;
}