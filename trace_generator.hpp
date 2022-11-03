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
		string print_temps();
	public:
		void set_temps();
		void set_seq(string);
		void set_ancre_fin(string);
		
		string hachage(int,int); // Transforme un temps donné en une trace
		string parentheses(); // Gère le cas: (tr - tr)
		void crochets_star(); // Gère le cas: <(tr - tr)*>
		void crochets_plus(); // Gère le cas: <(tr - tr)+>
		void crochets_pipe(string, string); // Gère le cas: <(tr - tr)E.|..|E.> ou <(tr - tr)E.%12|..|E.%42>
		void crochets_pipeX(string, string); // Gère le cas: <(tr - tr)E.K.|..|E.K.>
		
		string get_bloc(); //Nous renvoi le bloc de séquence de longueur semi-aléatoire

};