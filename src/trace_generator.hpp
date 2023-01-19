/*#########################################
## 01/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: trace_generator.hpp
###########################################*/
#include <string>

class bloc{
	private:
		int temps;
		std::string char_fin;
		std::string seq;
		int hache;
		std::string print_temps();
	public:
		void set_temps(int);
		void set_seq(std::string);
		void set_ancre_fin(std::string);
		
		std::string hachage(int,int); // Transforme un temps donné en une trace
		std::string parentheses(); // Gère le cas: (tr - tr)
		void crochets_plus_or_star(int, char); // Gère le cas: <(tr - tr)+> et <(tr - tr)*>
		void crochets_pipe(int, std::string); // Gère le cas: <(tr - tr)E.|..|E.> ou <(tr - tr)E.K.|..|E.K.>
		void crochets_percent(int, std::string); // Gère le cas: <(tr - tr)E.%12|..|E.%42>
		
		std::string get_bloc(); //Nous renvoi le bloc de séquence de longueur semi-aléatoire

};