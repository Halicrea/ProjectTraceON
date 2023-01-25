/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: alignment.cpp
###########################################*/
#include "alignment.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;

template <typename T> string to_str(const T& t) { 
   ostringstream os; 
   os<< t << setprecision(2) ; 
   return os.str(); 
} 

// https://stackoverflow.com/questions/45447361/how-to-move-certain-elements-of-stdvector-to-a-new-index-within-the-vector
template <typename t> void move(vector<t>& v, size_t oldIndex, size_t newIndex)
{
    if (oldIndex > newIndex){
		rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
	} else {
		rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
	}
}
//##########################################################################
/*
$$$$$$$$\                                  $$\                                            
\__$$  __|                                 $$ |                                           
   $$ |$$\   $$\  $$$$$$\   $$$$$$\      $$$$$$\    $$$$$$\  $$$$$$\   $$$$$$$\  $$$$$$\  
   $$ |$$ |  $$ |$$  __$$\ $$  __$$\     \_$$  _|  $$  __$$\ \____$$\ $$  _____|$$  __$$\ 
   $$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |      $$ |    $$ |  \__|$$$$$$$ |$$ /      $$$$$$$$ |
   $$ |$$ |  $$ |$$ |  $$ |$$   ____|      $$ |$$\ $$ |     $$  __$$ |$$ |      $$   ____|
   $$ |\$$$$$$$ |$$$$$$$  |\$$$$$$$\       \$$$$  |$$ |     \$$$$$$$ |\$$$$$$$\ \$$$$$$$\ 
   \__| \____$$ |$$  ____/  \_______|$$$$$$\\____/ \__|      \_______| \_______| \_______|
       $$\   $$ |$$ |                \______|                                             
       \$$$$$$  |$$ |                                                                     
        \______/ \__|                                                                     
	This function is used to transform a trace, which is a string, into
	a struct composed of a header, the trace ID, and a sequence, which
	is a vector of event.
*/
Type_trace trace_to_dict(string seq){
	Type_trace trace;
	string event;
	int i=0;
	while(seq[i] != ' '){
		trace.header += seq[i];
		i++;
	}
	while(i < seq.length()-1){
		string event = "";
		if(seq[i] == ' '){
		} else {
			if(seq[i] == '-'){
				trace.sequence.push_back(0);
			} else {
				if(seq[i] == 'E'){
				} else {
					while(seq[i] != ' '){
						event += seq[i];
						i++;
					}
					int event_num = stoi(event);
					trace.sequence.push_back(event_num);
				}
			}
		}
		i++;
	}
	return(trace);
}

//##########################################################################
/*
	Simple procedure for printing a Type_trace.
*/
void print_Type_trace(Type_trace trace){
	cout << trace.header << ' ';
	for(int i=0;i< trace.sequence.size();i++){
		if(trace.sequence[i] == -1){
			cout << "_ ";
		} else if(trace.sequence[i] == 0){
			cout << "- ";
		} else cout << 'E' << trace.sequence[i] << ' ';
	}
	cout << "S\n";
}


//##################################################################################
int gap_weigth(int gap_initial, int gap_penalty, int& gap_length){
	int gap_value = - gap_initial + (gap_penalty * gap_length);
	return gap_value;
}
//##################################################################################
/*
$$\      $$\            $$\               $$\              $$$$$$$$\                  
$$$\    $$$ |           $$ |              $$ |             $$  _____|                 
$$$$\  $$$$ | $$$$$$\ $$$$$$\    $$$$$$$\ $$$$$$$\         $$ |   $$\   $$\ $$$$$$$\  
$$\$$\$$ $$ | \____$$\\_$$  _|  $$  _____|$$  __$$\        $$$$$\ $$ |  $$ |$$  __$$\ 
$$ \$$$  $$ | $$$$$$$ | $$ |    $$ /      $$ |  $$ |       $$  __|$$ |  $$ |$$ |  $$ |
$$ |\$  /$$ |$$  __$$ | $$ |$$\ $$ |      $$ |  $$ |       $$ |   $$ |  $$ |$$ |  $$ |
$$ | \_/ $$ |\$$$$$$$ | \$$$$  |\$$$$$$$\ $$ |  $$ |       $$ |   \$$$$$$  |$$ |  $$ |
\__|     \__| \_______|  \____/  \_______|\__|  \__|$$$$$$\\__|    \______/ \__|  \__|
                                                    \______|                          
*/
int del(int event, int gap_initial, int gap_penalty, int& gap_length){
	return gap_weigth(gap_initial, gap_penalty, gap_initial);
}
int ins(int event, int gap_initial, int gap_penalty, int& gap_length){
	return gap_weigth(gap_initial, gap_penalty, gap_initial);
}
int subst(int event, int event2){
	int result_subst = 0;
	if(event == 0 || event2 == 0){
		if(event == event2){
			return 1;
		}
		return -1;
	}
	result_subst = abs(event - event2);
	if (result_subst == 0){
		return (2);
	} else return - result_subst;
}
void max(int insert, int delet, int substit, char *ptr, int& gap_length, int& result){
	// Need to take in account the length of consecutiv gap
	if(insert > delet && insert > substit){
		result = insert;
		*ptr = '-';
		gap_length++;
	} else {
		if(delet >= insert && delet > substit){
			result = delet;
			*ptr = '|';
			gap_length++;
		} else {
			result = substit;
			*ptr= '\\';
			gap_length = 0;
		}
	}
}
//##################################################################################
/*
$$$$$$\           $$\   $$\           $$\      $$\            $$\               $$\           
\_$$  _|          \__|  $$ |          $$$\    $$$ |           $$ |              \__|          
  $$ |  $$$$$$$\  $$\ $$$$$$\         $$$$\  $$$$ | $$$$$$\ $$$$$$\    $$$$$$\  $$\ $$\   $$\ 
  $$ |  $$  __$$\ $$ |\_$$  _|        $$\$$\$$ $$ | \____$$\\_$$  _|  $$  __$$\ $$ |\$$\ $$  |
  $$ |  $$ |  $$ |$$ |  $$ |          $$ \$$$  $$ | $$$$$$$ | $$ |    $$ |  \__|$$ | \$$$$  / 
  $$ |  $$ |  $$ |$$ |  $$ |$$\       $$ |\$  /$$ |$$  __$$ | $$ |$$\ $$ |      $$ | $$  $$<  
$$$$$$\ $$ |  $$ |$$ |  \$$$$  |      $$ | \_/ $$ |\$$$$$$$ | \$$$$  |$$ |      $$ |$$  /\$$\ 
\______|\__|  \__|\__|   \____/$$$$$$\\__|     \__| \_______|  \____/ \__|      \__|\__/  \__|
                               \______|                                                       
	Initialise and complete scoring.
*/
void Class_align::init_matrix_align(int n, int m){
	M[0][0] = 0;
	M_match[0][0] = 'n';
	char ptr;
	int gap_length = 0;
	int result = 0;

	for(int i=1;i<=n;i++){
		M[i][0] = - ( gap_initial + ( gap_penalty * (i - 1) ) );
		M_match[i][0] = '-';
	}
	for(int j=1;j<=m;j++){
		M[0][j] = - ( gap_initial + ( gap_penalty * (j - 1) ) );
		M_match[0][j] = '|';
		for(int i=1;i<=n;i++){
			max(
				M[i][j-1]+del(trace_align1.sequence[i-1],gap_initial,gap_penalty,gap_length),
				M[i-1][j]+ins(trace_align2.sequence[j-1],gap_initial,gap_penalty,gap_length),
				M[i-1][j-1]+subst(trace_align1.sequence[i-1],trace_align2.sequence[j-1]),&ptr,gap_length,result);
			M[i][j]=result;
			M_match[i][j] = ptr;
		}
	}
}
//##########################################################################
/*
$$$$$$$\            $$\            $$\                                    $$\               $$\           
$$  __$$\           \__|           $$ |                                   $$ |              \__|          
$$ |  $$ | $$$$$$\  $$\ $$$$$$$\ $$$$$$\         $$$$$$\$$$$\   $$$$$$\ $$$$$$\    $$$$$$\  $$\ $$\   $$\ 
$$$$$$$  |$$  __$$\ $$ |$$  __$$\\_$$  _|        $$  _$$  _$$\  \____$$\\_$$  _|  $$  __$$\ $$ |\$$\ $$  |
$$  ____/ $$ |  \__|$$ |$$ |  $$ | $$ |          $$ / $$ / $$ | $$$$$$$ | $$ |    $$ |  \__|$$ | \$$$$  / 
$$ |      $$ |      $$ |$$ |  $$ | $$ |$$\       $$ | $$ | $$ |$$  __$$ | $$ |$$\ $$ |      $$ | $$  $$<  
$$ |      $$ |      $$ |$$ |  $$ | \$$$$  |      $$ | $$ | $$ |\$$$$$$$ | \$$$$  |$$ |      $$ |$$  /\$$\ 
\__|      \__|      \__|\__|  \__|  \____/$$$$$$\\__| \__| \__| \_______|  \____/ \__|      \__|\__/  \__|
                                          \______|                                                        
https://mvdsman.github.io/blog/Simple-pairwise-alignment/*/
void  Class_align::print_matrice(int n, int m){
    cout << "        ";
    for( int i = 0; i < n; i++ ){
        cout << trace_align1.sequence[i] << "   ";
    }
    cout << "\n  ";

    for( int j = 0; j <= m; j++ ){
        if( j > 0 ){
            cout << trace_align2.sequence[j-1] << " ";
        }
        for( int i = 0; i <= n; i++ ){
            cout.width( 3 );
            cout << this -> M[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// Print the traceback matrix
void  Class_align::print_M_match(int n, int m){
    cout << "        ";
    for( int i = 0; i < n; i++ ){
        cout << trace_align1.sequence[i] << "   ";
    }
    cout << "\n  ";

    for( int j = 0; j <= m; j++ ){
        if( j > 0 ){
            cout << trace_align2.sequence[j-1] << " ";
        }
        for( int i = 0; i <= n; i++ ){
            cout.width( 3 );
            cout << this -> M_match[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//################################################################################## Alligator2, Big Money-nw, Gradient, Katana
/*
 $$$$$$\  $$\ $$\                                                 $$\           
$$  __$$\ $$ |\__|                                                \__|          
$$ /  $$ |$$ |$$\  $$$$$$\  $$$$$$$\           $$$$$$\   $$$$$$\  $$\  $$$$$$\  
$$$$$$$$ |$$ |$$ |$$  __$$\ $$  __$$\         $$  __$$\  \____$$\ $$ |$$  __$$\ 
$$  __$$ |$$ |$$ |$$ /  $$ |$$ |  $$ |        $$ /  $$ | $$$$$$$ |$$ |$$ |  \__|
$$ |  $$ |$$ |$$ |$$ |  $$ |$$ |  $$ |        $$ |  $$ |$$  __$$ |$$ |$$ |      
$$ |  $$ |$$ |$$ |\$$$$$$$ |$$ |  $$ |        $$$$$$$  |\$$$$$$$ |$$ |$$ |      
\__|  \__|\__|\__| \____$$ |\__|  \__|$$$$$$\ $$  ____/  \_______|\__|\__|      
                  $$\   $$ |          \______|$$ |                              
                  \$$$$$$  |                  $$ |                              
                   \______/                   \__|                              
*/
void Class_align::alignment_global_pairwize(vector<int> &Alignment1,vector<int> &Alignment2){
	//vector<int> Alignment1;
	//vector<int> Alignment2;
	int i = trace_align1.sequence.size();
	int j = trace_align2.sequence.size();
	cout << i << "-"<< j << endl;
	for(int cpt=0;cpt<trace_align1.sequence.size();cpt++) cout << trace_align1.sequence[cpt] << ' ';
	cout << endl;
	for(int cpt=0;cpt<trace_align2.sequence.size();cpt++) cout << trace_align2.sequence[cpt] << ' ';
	cout << endl;
	while(i > 0 || j > 0){
		if(i>0 && j>0 && (M_match[i][j] == '\\')){
			Alignment1.push_back(trace_align1.sequence[i-1]);
			Alignment2.push_back(trace_align2.sequence[j-1]);
			i--;
			j--;
		} else if(i>0 && M_match[i][j] == '|'){
				Alignment1.push_back(trace_align1.sequence[i-1]);
				Alignment2.push_back(-1);
				i--;
			} else {
				Alignment1.push_back(-1);
				Alignment2.push_back(trace_align2.sequence[j-1]);
				j--;
		}
	}
	for(int cpt=0;cpt<Alignment1.size();cpt++) cout << Alignment1[cpt] << ' ';
	cout << endl;
	for(int cpt=0;cpt<Alignment2.size();cpt++) cout << Alignment2[cpt] << ' ';
	cout << endl;
	//cout << "k " << Alignment1 << endl;
	//cout << "  " << Alignment2 << endl;
}

//##################################################################################
/*
$$$$$$$\            $$\            $$\                    $$\ $$\                     
$$  __$$\           \__|           $$ |                   $$ |\__|                    
$$ |  $$ | $$$$$$\  $$\ $$$$$$$\ $$$$$$\         $$$$$$\  $$ |$$\  $$$$$$\  $$$$$$$\  
$$$$$$$  |$$  __$$\ $$ |$$  __$$\\_$$  _|        \____$$\ $$ |$$ |$$  __$$\ $$  __$$\ 
$$  ____/ $$ |  \__|$$ |$$ |  $$ | $$ |          $$$$$$$ |$$ |$$ |$$ /  $$ |$$ |  $$ |
$$ |      $$ |      $$ |$$ |  $$ | $$ |$$\      $$  __$$ |$$ |$$ |$$ |  $$ |$$ |  $$ |
$$ |      $$ |      $$ |$$ |  $$ | \$$$$  |     \$$$$$$$ |$$ |$$ |\$$$$$$$ |$$ |  $$ |
\__|      \__|      \__|\__|  \__|  \____/$$$$$$\\_______|\__|\__| \____$$ |\__|  \__|
                                          \______|                $$\   $$ |          
                                                                  \$$$$$$  |          
                                                                   \______/           
*/
int word_length(int word){
	switch(word){
		case -1: return 1;
		case 0: return 1;
		default: return (to_str<int>(word).length());
	}
}
string word_to_string(int word){
	switch(word){
		case -1: return "_ ";
		case 0: return "- ";
		default: return 'E' + to_str<int>(word);
	}
}
void Class_align::print_Alignment(Type_trace trace1, Type_trace trace2){
	string alignement1_out = "";
	string alignement2_out = "";
	string matching = "";
	int word_seq1, word_seq2;
	for(int i=0;i < trace1.sequence.size(); i++){
		word_seq1 = word_length(trace1.sequence[i]);
		word_seq2 = word_length(trace2.sequence[i]);
		if(word_seq1 < word_seq2){
			alignement1_out += word_to_string(trace1.sequence[i]) + ' ';
			alignement1_out += ' '*(word_seq2-word_seq1);
			alignement2_out += word_to_string(trace2.sequence[i]) + ' ';
		} else {
			alignement1_out += word_to_string(trace1.sequence[i]) + ' ';
			alignement2_out += word_to_string(trace2.sequence[i]) + ' ';
			alignement2_out += ' '*(word_seq1-word_seq2);
		}
	}
	int length_id = trace1.header.length();
	cout << trace1.header << ' ' << alignement1_out + "S" << endl;
	cout << trace2.header << ' ' << alignement2_out + "S" << endl;
}

//##################################################################################
/*
$$\      $$\           $$\   $$\     $$\         $$$$$$\  $$\ $$\                     
$$$\    $$$ |          $$ |  $$ |    \__|       $$  __$$\ $$ |\__|                    
$$$$\  $$$$ |$$\   $$\ $$ |$$$$$$\   $$\        $$ /  $$ |$$ |$$\  $$$$$$\  $$$$$$$\  
$$\$$\$$ $$ |$$ |  $$ |$$ |\_$$  _|  $$ |       $$$$$$$$ |$$ |$$ |$$  __$$\ $$  __$$\ 
$$ \$$$  $$ |$$ |  $$ |$$ |  $$ |    $$ |       $$  __$$ |$$ |$$ |$$ /  $$ |$$ |  $$ |
$$ |\$  /$$ |$$ |  $$ |$$ |  $$ |$$\ $$ |       $$ |  $$ |$$ |$$ |$$ |  $$ |$$ |  $$ |
$$ | \_/ $$ |\$$$$$$  |$$ |  \$$$$  |$$ |       $$ |  $$ |$$ |$$ |\$$$$$$$ |$$ |  $$ |
\__|     \__| \______/ \__|   \____/ \__|$$$$$$\\__|  \__|\__|\__| \____$$ |\__|  \__|
                                         \______|                 $$\   $$ |          
                                                                  \$$$$$$  |          
                                                                   \______/           
*/
//############################################################
/*
	Constructor for the classe
*/
void Multi_Align::init_trace_list(string file_name){
	vector<string> liste_trace;
	ifstream file(file_name);
	string line;
	Type_trace trace_i;
	int n_line = 0;
	while(getline(file,line)){
		liste_trace.push_back(line);
		trace_i = trace_to_dict(line);
		trace_list.push_back(trace_i);
		n_line++;
	}
	number_of_traces = n_line;
}

//############################################################
/*
	To calculate the distance between two matrix, and more precisely,
	the difference between D_prec and D.
	The number of paris which we can produce from r elements is: r(r-1)/2
*/
float difference(vector<matri> &D,vector<matri> &D_prec){
	cout << "- Calcul difference\n";
	int distance = 0; // We initialize the distance between the two matrix
	int n = D.size();
	//cout << endl;
	//cout << D[0].ligne[0] << endl;
	for(int i=1; i<n;i++){
		//cout << 'i' << i << '-';
		for(int j=0;j<D[i].ligne.size();j++){
			//cout << D_prec[i].ligne[j] << " % " << D[i].ligne[j];
			//distance = distance + pow(D_prec[i].ligne[j]-D[i].ligne[j],2);
		}
		//cout << endl;
	}
	distance = (2*distance)/n*(n-1);
	distance = sqrt(distance);
	return distance;
}
float random_val(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1,50);
	return distr(gen);
}
void create_tringular_matrix(vector<matri> &D){
	int n=D.size();
	D[0].header = "Seq 1";
	for(int i=1;i<n;i++){
		//We go to each row and generate a row the size needed
		D[i].ligne=vector<float>(i);
		//D[i].header = "Seq " + to_str(i+1);
		for(int j=0;j<i;j++){
			D[i].ligne[j]=1;
		}
	}
}
void print_tri_matrix(vector<matri> &D){
	int n=D.size();
	cout << "Affichage matrice: \n";
	for(int i=0;i<n;i++){
		cout << D[i].header << "\t";
		for(int j=0;j<D[i].ligne.size();j++){
			cout << D[i].ligne[j] << "\t";
		}
		cout << endl;
	}
}

//############################################################
vector<matri> calcul_dissimilarite(vector<Type_trace> trace_list){
	// Number of sequences:
	int n = trace_list.size();
	// Initialization of a triangular matrix localy before throwing it back.
	vector<matri> tri_matrix(n);
	tri_matrix[0].header = trace_list[0].header;
	for(int i=1;i<n;i++){
		//We go to each row and generate a row the size needed
		tri_matrix[i].ligne = vector<float>(i);
		for(int j=0; j<i;j++){
			// For each pair we aligned using the Class_align and it's function. It needed two matrix
			int n = trace_list[i].sequence.size();
			int m = trace_list[j].sequence.size();
			int** M = new int* [n+1];
			for(int i=0; i< n+1; i++){
				M[i] = new int [m+1];
			}
			char** M_match = new char* [n+1];
			for(int i=0; i< n+1; i++){
				M_match[i] = new char [m+1];
			}

			Class_align align_pairwize(trace_list[i],trace_list[j],M, M_match);
			align_pairwize.init_matrix_align(n,m);
			// The alignment score is the last score of the matrix.
			tri_matrix[i].ligne[j] = M[n][m];
			tri_matrix[i].header = trace_list[i].header;

			// We can then deallocate memory
			for(int i=0; i<n; i++){
				delete M[i];
				delete M_match[i];
			}
			delete[] M;
			delete[] M_match;
			
		}
	}
	return tri_matrix;
}

//******************************************************************************
/*
	La méthode utilisée pour calculer la distance entre 2 séquences,
	donne un score d'autant plus élevé que 2 séquences sont
	similaires (les évènements et longues séquences sont favorisés).
*/
void find_maximum(const vector<matri> &D, int &i_min, int &j_min, float &value){
	//cout << "# Chercher maximum\n";
	const int n=D.size();	// Number of sequences
	value = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<D[i].ligne.size();j++){
			if(value<D[i].ligne[j]){
				value = D[i].ligne[j];
				//cout << value;
				i_min = i; // Comme la diagonale n'est pas modélisée, les numéros de colonnes sont plus petit de 1
				j_min = j;
			}
		}
	}
	//cout << "Value : " << value << "|i-" << i_min << " j-" << j_min <<endl;
}
void supprimer_ligne(vector<matri> &D, const int &r){
	//cout << "# Supprimer ligne\n";
	const int n=D.size();	// Number of sequences
	if (n > r){
		D.erase( D.begin() + r );
	}
}
void supprimer_colonne(vector<matri> &D, const int &r){
	//cout << "# Supprimer colonne\n";
	const int n=D.size();	// Number of sequences
	for (int i = 0; i < n; i++){
		if (D[i].ligne.size() > r){
			D[i].ligne.erase(D[i].ligne.begin() + r);
  		}
	}
}

float dissim_lign(vector<matri> &D, int i_min, int j_min, int i){
	//TODO Add explanation
	const int n=D.size()-1;	// Number of sequences
	float i_val,j_val;
	float result;
	//cout << "| Dissim lign" << i+1 << endl;
	i_val = D[i_min].ligne[i];
	//cout << " -> i_val " << i_val;
	j_val = D[j_min].ligne[i];
	//cout << " -> j_val " << j_val;
	//cout << endl;
	result = (i_val + j_val)/2;
	//cout << "Result: " << result << "(i"<< i_min << '.' << i <<":" << i_val << ") (j" << j_min << '.' << i << ":" << j_val << ")\n";
	return result;
}
float dissim_col(vector<matri> &D, int i_min, int j_min, int i, int &i_save){
	//TODO Add explanation
	const int n=D.size()-1;	// Number of sequences
	int index_i, index_j;
	float i_val,j_val;
	float result;
	//cout << "| Dissim col" << i+1 << endl;
	if((j_min+i) < D[i_min].ligne.size()){
		i_val = D[i_min].ligne[j_min+i];
		index_i = i_min;
		index_j = j_min+i;
	} else{
		//if(i_save==0) {i_save = i+2;} // On récupère la valeur de i du tour d'avant, c'est le nombre de chiffre qu'il reste à changer
		//cout << "----------" << i_save << endl;
		i_save++;
		i_val = D[D[i_min].ligne.size()+i_save].ligne[i_min];
		index_i = D[i_min].ligne.size()+i_save;
		index_j = i_min;
	}
	//cout << " -> i_val " << i_val;
	j_val = D[j_min+1+i].ligne[j_min];
	//cout << " -> j_val " << j_val;
	//cout << endl;
	result = (i_val + j_val)/2;
	//cout << "Result: " << result << "(i"<< index_i << '.' << index_j <<":" << i_val << ") (j" << j_min+1+i << '.' << j_min << ":" << j_val << ")\n";
	return result;
}

//********************************************************************************
/*
$$$$$$$$\                                   $$$$$$\                                 $$\               
\__$$  __|                                 $$  __$$\                                $$ |              
   $$ | $$$$$$\   $$$$$$\   $$$$$$\        $$ /  \__| $$$$$$\   $$$$$$\   $$$$$$\ $$$$$$\    $$$$$$\  
   $$ |$$  __$$\ $$  __$$\ $$  __$$\       $$ |      $$  __$$\ $$  __$$\  \____$$\\_$$  _|  $$  __$$\ 
   $$ |$$ |  \__|$$$$$$$$ |$$$$$$$$ |      $$ |      $$ |  \__|$$$$$$$$ | $$$$$$$ | $$ |    $$$$$$$$ |
   $$ |$$ |      $$   ____|$$   ____|      $$ |  $$\ $$ |      $$   ____|$$  __$$ | $$ |$$\ $$   ____|
   $$ |$$ |      \$$$$$$$\ \$$$$$$$\       \$$$$$$  |$$ |      \$$$$$$$\ \$$$$$$$ | \$$$$  |\$$$$$$$\ 
   \__|\__|       \_______| \_______|$$$$$$\\______/ \__|       \_______| \_______|  \____/  \_______|
                                     \______|                                                         
*/
TArbreBin<string>* build_tree(vector<matri> &D_aux, vector<TArbreBin<string>*> &subtrees,
								vector<string> &seq_prec_vector,
								float value, int k, int r){
	//***** INIT VARIABLES ******
	TArbreBin<string>* root;

	bool trouver = false;

	//**** DEBUT ****************
	//cout << "---------------------------\n# " << D_aux.size() << endl;
	trouver = false;
		// If we one of the sequence chosen to pair has been paired before, we had only the new leaf
		//cout << "---------------------Size vector prec : " << seq_prec_vector.size() << endl;
		int iter = 0;
		//cout << "r: " << D_aux[r].header << "    " << "k: " << D_aux[k].header << endl;

		for(int i=0;i<seq_prec_vector.size();i++){
			//cout << seq_prec_vector[i] << "_" << i << "/";
			if(D_aux[r].header == seq_prec_vector[i]){
				int cpt=0;
				while(D_aux[k].header != seq_prec_vector[cpt] && cpt < seq_prec_vector.size()){
					cpt++;
				}
				if(cpt < seq_prec_vector.size()){
					// We have found a match for r and k
					//cout << "# Trouver r and k\n";
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = subtrees[i];
					root -> fd = subtrees[cpt];
					subtrees[cpt] = root;
				} else {
					//cout << "# Trouver r\n";
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = subtrees[i];
					root -> fd = new TArbreBin<string>(D_aux[k].header);
					subtrees[i] = root;
					subtrees.push_back(root);
					seq_prec_vector.push_back(D_aux[k].header);	
				}
				trouver = true;
				break;
			}
			if(D_aux[k].header == seq_prec_vector[i]){
				int cpt=0;
				while(D_aux[r].header != seq_prec_vector[cpt] && cpt < seq_prec_vector.size()){
					cpt++;
				}
				if(cpt < seq_prec_vector.size()){
					// We have found a match for r and k
					//cout << "# Trouver k and r\n";
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = subtrees[cpt];
					root -> fd = subtrees[i];
					subtrees[i] = root;
				} else {
					//cout << "# Trouver k\n";
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = new TArbreBin<string>(D_aux[r].header);
					root -> fd = subtrees[i];
					subtrees[i] = root;
				}
				trouver = true;
				break;
			}
		}
		//cout << endl;
		if(!trouver){
			//cout << "# Nouvel arbre\n";
			root =  new TArbreBin<string>(to_str<float>(value));
			root -> fg = new TArbreBin<string>(D_aux[k].header);
			root -> fd = new TArbreBin<string>(D_aux[r].header);
			subtrees.push_back(root);
			seq_prec_vector.push_back(D_aux[k].header);		
		}
		//for(int i=0;i<seq_prec_vector.size();i++) cout << seq_prec_vector[i] << "_" << i << "/";
		//cout << endl;

	//cout << "---------------------------\n";
	return root;
}
//####################################################################################
/*
 $$$$$$\   $$$$$$\  $$\   $$\ 
$$  __$$\ $$  __$$\ $$ |  $$ |
$$ /  \__|$$ /  $$ |$$ |  $$ |
$$ |      $$$$$$$$ |$$$$$$$$ |
$$ |      $$  __$$ |$$  __$$ |
$$ |  $$\ $$ |  $$ |$$ |  $$ |
\$$$$$$  |$$ |  $$ |$$ |  $$ |
 \______/ \__|  \__|\__|  \__|                         
*/
//TODO Needs to add a way to save the tree and print it
void CAH(vector<matri> &D, TArbreBin<string>* &root){
	int n=D.size();	// Number of sequences
	vector<matri> D_aux = D;
	int i_min,j_min = 0;
	//float i_minf,j_minf;
	int k=-1, r;
	int i_save;
	float value;
	TArbreBin<string>* root_prec;
	vector<TArbreBin<string>*> subtrees;
	vector<string> seq_prec_vector;
	
	//print_tri_matrix(D_aux);
	cout << "# Construire Arbre\n";
	//supprimer_ligne(D_aux,0);
	while(n>1){
		i_save = 0;
		find_maximum(D_aux,i_min,j_min, value);
		
		k = min(i_min,j_min);
		//cout << "k: " << k << endl;
		/*
			Le nouvel item obtenu par agglomération
			i0 et j0 sera positionné à l'indice k
			dans D_aux mis à jour.
		*/
		r = max(i_min,j_min);
		//cout << "r: " << r << endl;
		//cout << "& Nom de séquence: " << D_aux[k].header << " et " << D_aux[r].header << endl;
		//--------------------------------------------------
		/*
			Faisons des arbres :D
		*/
		root = build_tree(D_aux, subtrees, seq_prec_vector,value, k, r);
		//--------------------------------------------------
	
		//D_aux[k].header += '-' + D_aux[r].header;
		/*
			Mettre à jour les valeurs de la colonne k
			et de la ligne k.
		*/
		for(int i=1;i<n-k;i++){
			//cout << "# Dissim truc colonne " << n-k-1 << " en " << D_aux[i+k].ligne[k] << endl;
			D_aux[i+k].ligne[k]=dissim_col(D_aux,i_min,j_min,i-1,i_save);
			//cout << i << '/';
		}
		//cout << endl;
		//print_tri_matrix(D_aux);
		int taille_ligne = D_aux[k].ligne.size();
		for(int j=0;j<D_aux[k].ligne.size();j++){
			//cout << "# Dissim truc ligne (size: " << D_aux[k].ligne.size() << ")\n";
			if(j!=r){
				//cout << "- Pos " << D_aux[k].ligne[j] << endl;
				D_aux[k].ligne[j]=dissim_lign(D_aux,i_min,j_min,j);
				//print_tri_matrix(D_aux);
			}
			//cout << j << '/';
		}
		//cout << endl;
		//print_tri_matrix(D_aux);

		supprimer_ligne(D_aux,r);
		supprimer_colonne(D_aux,r-1);	
		n--;
		//print_tri_matrix(D_aux);
	}
	//root->printBTS();

	//******* FREE MEMORY *******
	subtrees.clear();subtrees.shrink_to_fit();
	seq_prec_vector.clear();seq_prec_vector.shrink_to_fit();
}

//############################################################
/*
$$$$$$$\                                                $$\     $$\                               
$$  __$$\                                               $$ |    \__|                              
$$ |  $$ | $$$$$$\   $$$$$$\  $$\  $$$$$$\   $$$$$$$\ $$$$$$\   $$\  $$$$$$\  $$$$$$$\   $$$$$$$\ 
$$$$$$$  |$$  __$$\ $$  __$$\ \__|$$  __$$\ $$  _____|\_$$  _|  $$ |$$  __$$\ $$  __$$\ $$  _____|
$$  ____/ $$ |  \__|$$ /  $$ |$$\ $$$$$$$$ |$$ /        $$ |    $$ |$$ /  $$ |$$ |  $$ |\$$$$$$\  
$$ |      $$ |      $$ |  $$ |$$ |$$   ____|$$ |        $$ |$$\ $$ |$$ |  $$ |$$ |  $$ | \____$$\ 
$$ |      $$ |      \$$$$$$  |$$ |\$$$$$$$\ \$$$$$$$\   \$$$$  |$$ |\$$$$$$  |$$ |  $$ |$$$$$$$  |
\__|      \__|       \______/ $$ | \_______| \_______|   \____/ \__| \______/ \__|  \__|\_______/ 
                        $$\   $$ |                                                                
                        \$$$$$$  |                                                                
                         \______/                                                                 
*/
void Multi_Align::print_align(){
	int word, word_max;
	string sequence;
	int word_length_max = 1;
	for(int n=0;n<trace_align.size();n++){
		sequence = trace_align[n].header + "\t";
		for(int i=0; i<trace_align[n].sequence.size();i++){
			for(int j=0;j<trace_align.size();j++){
				//words.push_back(trace_align[j].sequence[i]);
				word_max = trace_align[j].sequence[i];
				if(word_length(word_max) > word_length_max){
					word_length_max = word_length(word_max);
				}
			}
			//cout << word_length_max << '/';
			word = trace_align[n].sequence[i];
			sequence += word_to_string(word) + ' ';
			//sequence += ' '*(word_length_max-word_length(word));
		}
		//cout << endl;
		cout << sequence + 'S' << endl;
	}
}
void find_pair_in_tree(TArbreBin<string> *node, TArbreBin<string>* &pair, float &value_max){
	float value;
	if(node != NULL){
		value = atof((node->data).c_str());
		//cout << value << "/";
		if (value > value_max){value_max = value; pair=node;}
		find_pair_in_tree(node -> fg, pair, value_max);
		find_pair_in_tree(node -> fd, pair, value_max);
	}
}
vector<Type_trace> aligner_sequences_ou_projection(TArbreBin<string> *root,
													vector<Type_trace> trace_list,
													float &score){
	vector<Type_trace> trace_to_align;
	TArbreBin<string> *pair;
	float value_max = 0.0;
	int i = 0;
	bool trouver, trouver1, trouver2;
	trouver = trouver1 = trouver2 = false;
	Type_trace trace_1, trace_2, trace_align_1, trace_align_2;
	int index_trace_1, index_trace_2;

	cout << "========================\n";
	cout << "Find pair: ";
	find_pair_in_tree(root, pair, value_max);
	cout << endl;
	pair -> printBTS();

	//******* PAIR FOUND: PROJECTION *******
	while(i<trace_list.size() && !trouver){
		if(pair -> fg -> data == trace_list[i].header){trace_1 = trace_list[i]; trouver1 = true;}
		if(pair -> fd -> data == trace_list[i].header){trace_2 = trace_list[i]; trouver2 = true;}
		if(trouver1 && trouver2){trouver = true;}
		i++;
	}
	int n = trace_1.sequence.size();
	int m = trace_2.sequence.size();
	int** M = new int* [n+1];
	for(int i=0; i< n+1; i++){
		M[i] = new int [m+1];
	}
	char** M_match = new char* [n+1];
	for(int i=0; i< n+1; i++){
		M_match[i] = new char [m+1];
	}
	Class_align pair_align(trace_1, trace_2, M, M_match);
	pair_align.init_matrix_align(n,m);
	pair_align.print_Alignment(trace_1,trace_2);	
	pair_align.alignment_global_pairwize(trace_align_1.sequence, trace_align_2.sequence);
	score += M[n][m];
	// We can then deallocate memory
	for(int i=0; i<n; i++){
		delete M[i];
		delete M_match[i];
	}
	delete[] M;
	delete[] M_match;

	for(int i=0;i<trace_list.size();i++){
		if(trace_list[i].header == trace_1.header) {index_trace_1 = i, trace_list[i].sequence = trace_align_1.sequence;}
		if(trace_list[i].header == trace_2.header) {index_trace_2 = i; trace_list[i].sequence = trace_align_2.sequence;}
	}
	move(trace_list,index_trace_2,index_trace_1+1);

	return trace_list;
}

/*
 $$$$$$\                                       $$\      $$\  $$$$$$\   $$$$$$\  
$$  __$$\                                      $$$\    $$$ |$$  __$$\ $$  __$$\ 
$$ /  \__| $$$$$$\   $$$$$$\   $$$$$$\         $$$$\  $$$$ |$$ /  \__|$$ /  $$ |
$$ |      $$  __$$\ $$  __$$\ $$  __$$\        $$\$$\$$ $$ |\$$$$$$\  $$$$$$$$ |
$$ |      $$ /  $$ |$$ |  \__|$$$$$$$$ |       $$ \$$$  $$ | \____$$\ $$  __$$ |
$$ |  $$\ $$ |  $$ |$$ |      $$   ____|       $$ |\$  /$$ |$$\   $$ |$$ |  $$ |
\$$$$$$  |\$$$$$$  |$$ |      \$$$$$$$\        $$ | \_/ $$ |\$$$$$$  |$$ |  $$ |
 \______/  \______/ \__|       \_______|$$$$$$\\__|     \__| \______/ \__|  \__|
                                        \______|                                
                                                                                
*/
// TODO FINISH THIS GODDAMN MOTHERFUCKER
// n le nombre de séquences
void Multi_Align::multiple_alignment(float seuil){
	//*** INIT VAR	****
	TArbreBin<string> *T,*T_prec;
	trace_align = trace_list;
	vector<matri> D(trace_list.size());
	vector<matri> D_prec(trace_list.size());
	bool convergence;
	float score = 0;
	// List of sequences is define in the class
	// type_alignment is a vector of traces define in the class: trace_align

	//*** DEBUT		****
	convergence = false;
	create_tringular_matrix(D_prec);
	cout << "- Number of sequences: " << number_of_traces << endl;

	int i = 1;
	cout << "# Début boucle\n";
	while(!convergence){
		if(i==1){
			cout << "# Dissimilarity\n";
			D = calcul_dissimilarite(trace_list);
			cout << "- Calcul réussi\n";
		} else D = calcul_dissimilarite(trace_align);	// We have already done a multiline alignment
		//if(difference(D,D_prec) <= seuil){convergence = true; break;}
		// convergence = false
		CAH(D, T);
		//T ->printBTS();
		trace_align = aligner_sequences_ou_projection(T, trace_align, score);
		trace_list = trace_align;
		trace_align.erase(trace_align.begin());
		D_prec = D;
		i++;
		convergence = true;
	}
	cout << "================= Affichage alignment multiple ===\n";
	print_align();
	cout << "== Score: " << score << endl;
}

//#################################################################
/*
	Affiche un bel arbre.
	└──A
		├──B
		│   ├──R
		│   └──S
		└──C
			└──D

*/
template<typename T>
void TArbreBin<T>::printBTS(){
	this -> printBTS("",false);
}
template<typename T>
void TArbreBin<T>::printBTS(const string& prefix, bool isLeft){
	if(this != NULL){
		cout << prefix;
		cout << (isLeft ? "├──" : "└──");
		cout << data << endl;
		fg -> printBTS(prefix + (isLeft ? "│   " : "    "), true);
		fd -> printBTS(prefix + (isLeft ? "│   " : "    "), false);
	}
}