/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: simple_functions.cpp
###########################################*/
#include "simple_functions.hpp"
#include <iostream>
using namespace std;
/*
	Finding if a value exist in an array.
*/
bool find(int *table, int val){
	bool trouver = false;
	int table_size;
	
	int i = 0;
	while ((val != table[i]) && (i<sizeof(table)/sizeof(int))){
		i++;
	}
	if ((val == table[i])){
		trouver = true;
	}
	cout << "Trouver : "<< trouver << endl;
	return trouver;
}

//###########################################
/*
	Quick sort
*/
void quickSort(int table[], int left, int right){
	if(left<right){
		int index_pivot;
		//Partition du tableau
		index_pivot = partition(table,left,right);

		//
		quickSort(table,left,right-1);
		quickSort(table,left+1,right);
	}
}

int partition(int table[], int left, int right){
	int pivot = table[left];
	int comp = table[right];
	int low = left;
	int high = right;
	int index_pivot;

	while(low < high){
		if(comp > pivot){
			table[high] = comp;
			high--;
			comp = table[high];
		} else {
			table[low] = comp;
			low++;
			comp = table[low];
		}
	}
	index_pivot = low;
	table[index_pivot] = pivot;
	return index_pivot;
}
