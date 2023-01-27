/*#########################################
## 26/01/2023
## Par Elyna Bouchereau & Florent Boyer
## Fichier: clustering.cpp
###########################################*/
#include "struct.hpp"
#include "clustering.hpp"
#include "pairwize_global.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;


//******************************************************************************
template <typename T> string to_str(const T& t) { 
   ostringstream os; 
   os<< t << setprecision(2) ; 
   return os.str(); 
} 
//****************************************************************
// Function for counting gaps
int gap_count(vector<Type_trace> trace_align_sorted) {
    int count = 0;
    for (int i = 0; i < trace_align_sorted.size(); i++){
        if (trace_align_sorted[i].sequence[i]==-1) {
            count++;
        }
    }
    return count;
}

//****************************************************************
/*
	Function to calculate a gap score based on the number of gaps
	and length of the MSA.
*/
float gap_score(vector<Type_trace> trace_align_sorted) {
    int score = gap_count(trace_align_sorted);
    return (float)score / trace_align_sorted.size();
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
	int iter = 0;

	//**** DEBUT ****************

		// If we one of the sequence chosen to pair has been paired before, we had only the new leaf

		for(int i=0;i<seq_prec_vector.size();i++){

			if(D_aux[r].header == seq_prec_vector[i]){
				int cpt=0;
				while(D_aux[k].header != seq_prec_vector[cpt] && cpt < seq_prec_vector.size()){
					cpt++;
				}
				if(cpt < seq_prec_vector.size()){
					// We have found a match for r and k
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = subtrees[i];
					root -> fd = subtrees[cpt];
					subtrees[cpt] = root;
				} else {
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = subtrees[i];
					root -> fd = new TArbreBin<string>(D_aux[k].header);
					subtrees[i] = root;
					subtrees.push_back(root);
					seq_prec_vector.push_back(D_aux[k].header);	
				}
				trouver = true;	break;
			}
			if(D_aux[k].header == seq_prec_vector[i]){
				int cpt=0;
				while(D_aux[r].header != seq_prec_vector[cpt] && cpt < seq_prec_vector.size()){
					cpt++;
				}
				if(cpt < seq_prec_vector.size()){
					// We have found a match for r and k
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = subtrees[cpt];
					root -> fd = subtrees[i];
					subtrees[i] = root;
				} else {
					root =  new TArbreBin<string>(to_str<float>(value));
					root -> fg = new TArbreBin<string>(D_aux[r].header);
					root -> fd = subtrees[i];
					subtrees[i] = root;
				}
				trouver = true;
				break;
			}
		}
		if(!trouver){
			root =  new TArbreBin<string>(to_str<float>(value));
			root -> fg = new TArbreBin<string>(D_aux[k].header);
			root -> fd = new TArbreBin<string>(D_aux[r].header);
			subtrees.push_back(root);
			seq_prec_vector.push_back(D_aux[k].header);		
		}

	return root;
}
//******************************************************************************
void build_final_tree( vector<TArbreBin<string>*> &subtrees,
							vector<string> &seq_prec_vector,
							TArbreBin<string>* pair_copy, TArbreBin<string>* &root,
							string name_remove, string name_kept){
	//*##### INIT VARIABLES #####
	bool trouver = false;
	int iter = 0;

	//*##### DEBUT #####
	// If we one of the sequence chosen to pair has been paired before, we had only the new leaf
	for(int i=0;i<seq_prec_vector.size();i++){
		if(name_remove == seq_prec_vector[i]){
			int cpt=0;
			while(name_kept != seq_prec_vector[cpt] && cpt < seq_prec_vector.size()){
				cpt++;
			}
			if(cpt < seq_prec_vector.size()){
				// We have found a match for both leaves of the pair selected in CAH
				root = pair_copy;
				root -> fg = subtrees[i];
				root -> fd = subtrees[cpt];
				subtrees[cpt] = root;
			} else {
				// Only name_remove was found
				root = pair_copy;
				root -> fg = subtrees[i];
				root -> fd = new TArbreBin<string>(name_kept);
				subtrees[i] = root;
				subtrees.push_back(root);
				seq_prec_vector.push_back(name_kept);
			}
			trouver = true; break;
		}
		if(name_kept == seq_prec_vector[i]){
			int cpt=0;
			while(name_remove != seq_prec_vector[cpt] && cpt < seq_prec_vector.size()){
				cpt++;
			}
			if(cpt < seq_prec_vector.size()){
				// We have found a match for both leaves of the pair selected in CAH
				root = pair_copy;
				root -> fg = subtrees[i];
				root -> fd = subtrees[cpt];
				subtrees[i] = root;
			} else {
				// Only name_kept was found
				root = pair_copy;
				root -> fg = new TArbreBin<string>(name_remove);
				root -> fd = subtrees[i];
				subtrees[i] = root;
			}
			trouver = true; break;
		}
	}
	//*##### IF A MATCH WASN'T FOUND, WE NEED TO ADD A NEW SUBTREE #####
	if(!trouver){
		root = pair_copy;
		subtrees.push_back(root);
		seq_prec_vector.push_back(name_kept);
	}
}

//******************************************************************************
/*
	The method used to compute the distance bewteen two sequences,
	gives a score the highest when 2 sequences are highly similar
	(events and long sequences are favorised).
*/
void find_maximum(const vector<matri> &D, int &i_min, int &j_min, float &value){
	const int n=D.size();	// Number of sequences
	value = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<D[i].ligne.size();j++){
			if(value<D[i].ligne[j]){
				value = D[i].ligne[j];
				i_min = i; // As the diagonal is not created, column and row number are smaller than 1
				j_min = j;
			}
		}
	}
}
//******************************************************************************
void supprimer_ligne(vector<matri> &D, const int &r){
	const int n=D.size();	// Number of sequences
	if (n > r){
		D.erase( D.begin() + r );
	}
}
//******************************************************************************
void supprimer_colonne(vector<matri> &D, const int &r){
	const int n=D.size();	// Number of sequences
	for (int i = 0; i < n; i++){
		if (D[i].ligne.size() > r){
			D[i].ligne.erase(D[i].ligne.begin() + r);
  		}
	}
}
//******************************************************************************
float dissim_lign(vector<matri> &D, int i_min, int j_min, int i){
	//TODO Add explanation
	const int n=D.size()-1;	// Number of sequences
	float i_val,j_val;
	float result;

	i_val = D[i_min].ligne[i];

	j_val = D[j_min].ligne[i];

	result = (i_val + j_val)/2;

	return result;
}
//******************************************************************************
float dissim_col(vector<matri> &D, int i_min, int j_min, int i, int &i_save){
	//TODO Add explanation
	const int n=D.size()-1;	// Number of sequences
	int index_i, index_j;
	float i_val,j_val;
	float result;
	if((j_min+i) < D[i_min].ligne.size()){
		i_val = D[i_min].ligne[j_min+i];
		index_i = i_min;
		index_j = j_min+i;
	} else{

		i_save++;
		i_val = D[D[i_min].ligne.size()+i_save].ligne[i_min];
		index_i = D[i_min].ligne.size()+i_save;
		index_j = i_min;
	}

	j_val = D[j_min+1+i].ligne[j_min];

	result = (i_val + j_val)/2;
	return result;
}

//******************************************************************************
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
void CAH(vector<matri> D, TArbreBin<string>* &root,
		float &score, string &name_remove, string &name_kept){
	int n=D.size();	// Number of sequences
	vector<matri> D_aux = D;
	int i_min,j_min = 0;
	int k=-1, r;
	int i_save;
	float value;
	score = 0.0;
	TArbreBin<string>* root_prec;
	vector<TArbreBin<string>*> subtrees;
	vector<string> seq_prec_vector;

	while(n>1){
		i_save = 0;
		find_maximum(D_aux,i_min,j_min, value);
		
		k = min(i_min,j_min);
		
		/*
			The new item obtained by agglomeration,
			i0 and j0, will be put a the k index
			and D_aux will be updated.
		*/
		r = max(i_min,j_min);
		if(n == D.size()){
			name_kept = D_aux[k].header;
			name_remove = D_aux[r].header;
			score = value;
		}

		//--------------------------------------------------
		/*
			Building the tree resulting of the hierarchical clustering.
			This tree has value on nodes and trace name on leaves.
		*/
		root = build_tree(D_aux, subtrees, seq_prec_vector,value, k, r);
		//--------------------------------------------------
	
		//D_aux[k].header += '-' + D_aux[r].header;
		/*
			Updating the values of the k column and k
			row.
		*/
		for(int i=1;i<n-k;i++){
			D_aux[i+k].ligne[k]=dissim_col(D_aux,i_min,j_min,i-1,i_save);

		}

		int taille_ligne = D_aux[k].ligne.size();
		for(int j=0;j<D_aux[k].ligne.size();j++){
			if(j!=r){
				D_aux[k].ligne[j]=dissim_lign(D_aux,i_min,j_min,j);
			}
		}
		supprimer_ligne(D_aux,r);
		supprimer_colonne(D_aux,r-1);	
		n--;
	}

	//******* FREE MEMORY *******
	subtrees.clear();subtrees.shrink_to_fit();
	seq_prec_vector.clear();seq_prec_vector.shrink_to_fit();
}