/*#########################################
## 01/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: trace_generator.hpp
###########################################*/
#include <string>
using namespace std;

class bloc{
	private:
		int temps;
		string char_fin;
		string seq;
		int hache;
	public:
		void set_temps();
		string print_temps();
		void set_seq(string);
		void set_ancre_fin(string);
		
		string hachage(int,int); // Transforme un temps donné en une trace
		string parentheses(string); // Gère le cas: (tr - tr)
		string crochets_star(string, string); // Gère le cas: <(tr - tr)*>
		void crochets_plus(string, string); // Gère le cas: <(tr - tr)+>
		string crochets_pipe(string, string); // Gère le cas: <(tr - tr)E.|..|E.> ou <(tr - tr)E.%12|..|E.%42>
		string crochets_pipeX(string, string); // Gère le cas: <(tr - tr)E.K.|..|E.K.>
		
		string get_bloc(); //Nous renvoi le bloc de séquence de longueur semi-aléatoire

};