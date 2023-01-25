/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: simple_functions.hpp
###########################################*/
#include <string>
/*
	Function which return true if it find a specific value
	in an array.
*/
bool find(int*, int, int);

/*
	Sorting algorithm based on the QuickSort, implemented
	to sort arrays.
*/
void quickSort(int*, int, int);
int partition(int*, int, int);

/**/
int input();
template <typename T> std::string to_str(const T& t);