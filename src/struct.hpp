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

/*
	matri fo MatriceTriangulaire, with trace name on line to follow
	which sequence is removed or kept.
*/
struct matri{
	std::string header;
	std::vector<float> ligne;
};

/*
	A trace is a chain to a name or a vector of int representing the
	trace sequence.
*/
struct Type_trace{
	std::string header;
	std::vector<int> sequence;
};
struct cluster_trace{
	Type_trace trace;
	cluster_trace* next;
};

#endif