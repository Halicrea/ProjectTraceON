/*#########################################
## 26/01/2023
## Par Elyna Bouchereau & Florent Boyer
## Fichier: struct.hpp
###########################################*/
#include <vector>
#include <string>

#ifndef STRUCT_HPP
#define STRUCT_HPP
//***********************  STRUCT DECLARATION *****************************
struct matri{
	std::string header;
	std::vector<float> ligne;
};
struct Type_trace{
	std::string header;
	std::vector<int> sequence;
};
struct cluster_trace{
	Type_trace trace;
	cluster_trace* next;
};

#endif