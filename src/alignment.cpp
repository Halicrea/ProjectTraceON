/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: alignment.cpp
###########################################*/
#include "alignment.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


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
		cout << M[i][0] << "/";
	}
	cout << endl;
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
	cout << endl;
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
		default: return (to_string(word).length());
	}
}
string word_to_string(int word){
	switch(word){
		case -1: return "_ ";
		case 0: return "- ";
		default: return 'E' + to_string(word);
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
	To calculate the distance between two matrix, and more precisely,
	the difference between D_prec and D.
	The number of paris which we can produce from r elements is: r(r-1)/2
*/
int difference(vector<int>** D,vector<int>** D_prec, int n){
	int distance = 0; // We initialize the distance between the two matrix
	for(int i=0; i<n-1;i++){
		for(int j=i+1;j<n-1;j++){
			distance = distance + pow((*D_prec[i])[j]-(*D[i])[j],2);
		}
	}
	distance = (2*distance)/n*(n-1);
	distance = sqrt(distance);
}
void create_tringular_matrix(vector<int>** tri_matrix, int n){
	for(int i=0;i<n;i++){
		//We go to each row and generate a row the size needed
		tri_matrix[i] = new vector<int>(i+1);
		for(int j=0; j<=i;j++){
			(*tri_matrix[i])[j] = i*j;
		}
	}
}
//############################################################
vector<int>** calcul_dissimilarite(vector<Type_trace> trace_list){
	// Number of sequences:
	int n = trace_list.size();

	// Initialization of a triangular matrix localy before throwing it back.
	vector<int>** tri_matrix = new vector<int>*[n];
	for(int i=0;i<n;i++){
		//We go to each row and generate a row the size needed
		tri_matrix[i] = new vector<int>(i+1);
		for(int j=0; j<=i;j++){
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
			(*tri_matrix[i])[j] = M[n][m];

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

//############################################################
/*
	La méthode utilisée pour calculer la distance entre 2 séquences,
	donne un score d'autant plus élevé que 2 séquences sont
	similaires (les évènements et longues séquences sont favorisés).
*/
void find_maximum(vector<int>** D, const int &n, int &i_min, int &j_min){
	int value = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<(*D[i]).size();j++){
			if(value>(*D[i])[j]){
				value = (*D[i])[j];
				i_min = i; j_min = j;
			}
		}
	}
}
void supprimer_ligne(vector<int>** D, const int &r, int n){
	if (n > r){
		(*D).erase( (*D).begin() + r );
	}
}
void supprimer_colonne(vector<int>** D, const int &r, int n){
	for (int i = 0; i < n; ++i){
		if ((*D)[i].size() > r){
			(*D)[i].erase((*D)[i].begin() + r);
  		}
	}
}

int dissim(vector<int>** D, int i_min, int j_min, int i){
	//TODO Need a lot of work still
	return
}

//TODO Needs to add a way to save the tree and print it
void construire_arbre(vector<int>** D, int &n){
	vector<int>** D_aux = new vector<int>* [n];
	D_aux = D;
	int iter = 1;
	int i_min,j_min = 0;
	int k, r;
	while(iter<n){
		find_maximum(D_aux,n,i_min,j_min);
		k = min(i_min,j_min);
		/*
			Le nouvel item obtenu par agglomération
			i0 et j0 sera positionné à l'indice k
			dans D_aux mis à jour.
		*/
		r = max(i_min,j_min);
		//! Thoses operations will probably broke everything
		supprimer_colonne(D_aux,r,n);
		supprimer_ligne(D_aux,r,n);
		n--;
		/*
			Mettre à jour les valeurs de la colonne k
			et de la ligne k.
		*/
		for(int i=0;i<k-1;i++){
			(*D_aux[i])[k]=dissim(D,i_min,j_min,i);
		}
		for(int j=k+1;j<n;j++){
			if(j!=r){
				(*D_aux[k])[j]=dissim(D,i_min,j_min,j);
			}
		}

	}
}

//############################################################
// TODO FINISH THIS GODDAMN MOTHERFUCKER
// n le nombre de séquences
void Multi_Align::multiple_alignment(float seuil,int n){
	//*** INIT VAR	****
	Type_arbre T,T_prec;
	vector<int>** D = new vector<int>*[n];
	vector<int>** D_prec;
	bool convergence;
	// List of sequences is define in the class
	// type_alignment is a vector of traces define in the class: trace_align

	//*** DEBUT		****
	convergence = false;

	D_prec = new vector<int>* [n];
	int i = 1;
	while(!convergence){
		if(i==1){
			D = calcul_dissimilarite(trace_list);
		} else D = calcul_dissimilarite(projection(trace_align));	// We have already done a multiline alignment
		if(difference(D,D_prec,n) <= seuil){convergence = true; break;}
		// convergence = false
		construire_arbre(D, n);
		trace_align = aligner_sequences_ou_projection(T);
		D_prec = D;
	}
	print_align(trace_align);

	// Deallocate memory
	for (int i = 0; i < n; i++) {
		delete D[i];
	}
	delete[] D;
	for (int i = 0; i < n+1; i++) {
		delete D_prec[i];
	}
	delete[] D_prec;
}

