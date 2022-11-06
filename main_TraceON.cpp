/*#########################################
## 01/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: main_TraceON.cpp
###########################################*/
//#include "alignment.hpp"
#include "trace_generator.hpp"
#include <iostream>
#include <regex>
using namespace std;

int main(){
    string parameter="E2<()+>E8()E12<()E13|E89|E41%4|E14%8>E46<()*>S";
	//string parameter;
	//parameter+=argv[1];
    smatch trace;
    smatch cas;
	string anchor_list = "";
	string test_cas = "";
    string sequence = "";
	string temporary_anchor = "";
	int first_anchor_value;
    bloc a;

    //cout << "Pomme de terre ! \\(@_@)/"<< endl;
	cout << "Bienvenu sur ce générateur de traces. Utilisations des paramètres: " << parameter << endl;

    while(parameter[0] != "S"[0]){

        // On prend la 1ère trace
        regex_search(parameter,trace,regex("(^E[0-9]*)"));
		sequence += trace.str(1) + ' ';

		temporary_anchor=trace.str(1);
		first_anchor_value = atoi(temporary_anchor.substr(1,temporary_anchor.length()-1).c_str());
        // On test le cas
		parameter.erase(0,trace.str(1).length());

        if(parameter[0]=='('){
            a.set_temps();
            a.set_seq(a.parentheses());
			sequence += a.get_bloc();
			parameter.erase(0,2);
        } else {		// Sinon on est sur le cas <()>
			if(parameter[3]=='+' || parameter[3]=='*'){
				cout << "Cas +\n";
				a.set_temps();

				a.crochets_plus_or_star(first_anchor_value,parameter[3]);
				sequence += a.get_bloc();
				cout << "Add and erase\n";
				parameter.erase(0,5);
			} else {
				regex_search(parameter,cas,regex("(E[0-9]*\\|)"));
				test_cas += cas.str(1);
				if(test_cas.back()=='|'){
					regex_search(parameter,cas,regex("([|E0-9%]*\\|E[0-9%]*)"));
					anchor_list += cas.str(1);
					cout << "Cas |: " << anchor_list << endl;
					a.set_temps();
					//a.crochets_pipe(first_anchor_value,);
					parameter.erase(0,(anchor_list.length()+4));
				} else {break;}
				
			}
		}

        //cout << "Paramètre coupé: " << parameter << endl;
    }
    sequence += "S";
    cout << sequence << endl;
    return 0;
}