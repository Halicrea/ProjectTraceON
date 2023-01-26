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


//##################################################################################
template <typename T> string to_str(const T& t) { 
   ostringstream os; 
   os<< t << setprecision(2) ; 
   return os.str(); 
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
	//cout << "---------------------------\n# " << D_aux.size() << endl;
		// If we one of the sequence chosen to pair has been paired before, we had only the new leaf
		//cout << "---------------------Size vector prec : " << seq_prec_vector.size() << endl;
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
				trouver = true;	break;
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
//******************************************************************************
void build_final_tree( vector<TArbreBin<string>*> &subtrees,
							vector<string> &seq_prec_vector,
							TArbreBin<string>* pair_copy, TArbreBin<string>* &root,
							string name_remove, string name_kept){
	//##### INIT VARIABLES #####
	bool trouver = false;
	int iter = 0;

	//##### DEBUT #####
	// If we one of the sequence chosen to pair has been paired before, we had only the new leaf
	pair_copy ->printBTS();
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
	//##### IF A MATCH WASN'T FOUND, WE NEED TO ADD A NEW SUBTREE #####
	if(!trouver){
		root = pair_copy;
		subtrees.push_back(root);
		seq_prec_vector.push_back(name_kept);
	}
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
	int k=-1, r;
	int i_save;
	float value;
	TArbreBin<string>* root_prec;
	vector<TArbreBin<string>*> subtrees;
	vector<string> seq_prec_vector;

	//cout << "# Construire Arbre\n";
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
		supprimer_ligne(D_aux,r);
		supprimer_colonne(D_aux,r-1);	
		n--;
	}

	//******* FREE MEMORY *******
	subtrees.clear();subtrees.shrink_to_fit();
	seq_prec_vector.clear();seq_prec_vector.shrink_to_fit();
}