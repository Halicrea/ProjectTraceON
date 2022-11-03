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
    string parameter="E2<()+>E8()E96()S";
    string parameter_cut=parameter;
    smatch trace;
    smatch cas;
    string sequence = "";
	string temporary_anchor = "";
    bloc a;

    //cout << "Pomme de terre ! \\(@_@)/"<< endl;

    while(parameter_cut[0] != "S"[0]){
        

        // On prend la 1ère trace
        regex_search(parameter_cut,trace,regex("(^E[0-9]*)"));
        //trace="E1";
		sequence += trace.str(1);
        parameter_cut.erase(0,trace.str(1).length());
        //sequence += trace.str(1);
		temporary_anchor=trace.str(1);
        // On test le cas
        //regex_search(parameter_cut,cas,regex("(<\()"));
        if(parameter_cut[0]=='('){
            a.set_temps();
            a.set_seq(a.print_temps());
			sequence += a.get_bloc();
			parameter_cut.erase(0,2);
        } else {		// Sinon on est sur le cas <()>
			if(parameter_cut[3]=='+'){
				a.set_temps();
				a.crochets_plus(temporary_anchor,parameter_cut{4,5})
				sequence += a.get_bloc;
				parameter_cut.erase(0,5);
			} else {break;}
		}

        //cout << "Paramètre coupé: " << parameter_cut << endl;
    }
    sequence += "S";
    cout << sequence << endl;
    //regex rgx("^E[0-9]*");
    return 0;
}