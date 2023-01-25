/*#########################################
## 03/11/2022
## Par Elyna Bouchereau & Florent Boyer
## Fichier: simple_functions.cpp
###########################################*/
#include "simple_functions.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//#######################################################################################//
/*
	Finding if a value exist in an array.
*/
bool find(int *table, int val, int nbr_anchors){
	bool trouver = false;
	int table_size;
	
	int i = 0;
	while ((val != table[i]) && (i<nbr_anchors)){
		i++;
	}
	if ((val == table[i])){
		trouver = true;
	}
	return trouver;
}

//#######################################################################################//
/*
	Quick sort Procedure
*/
void quickSort(int table[], int left, int right){
	if(left<right){
		int index_pivot;
		// array partition
		index_pivot = partition(table,left,right);

		//sort recursive
		quickSort(table,left,right-1);
		quickSort(table,left+1,right);
	}
}
//#######################################################################################//
/*
	Partition for Quick sort
*/
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

//##########################################################################
/*
$$$$$$\                                 $$\      $$$\ $$$\   
\_$$  _|                                $$ |    $$  _| \$$\  
  $$ |  $$$$$$$\   $$$$$$\  $$\   $$\ $$$$$$\  $$  /    \$$\ 
  $$ |  $$  __$$\ $$  __$$\ $$ |  $$ |\_$$  _| $$ |      $$ |
  $$ |  $$ |  $$ |$$ /  $$ |$$ |  $$ |  $$ |   $$ |      $$ |
  $$ |  $$ |  $$ |$$ |  $$ |$$ |  $$ |  $$ |$$\\$$\     $$  |
$$$$$$\ $$ |  $$ |$$$$$$$  |\$$$$$$  |  \$$$$  |\$$$\ $$$  / 
\______|\__|  \__|$$  ____/  \______/    \____/  \___|\___/  
                  $$ |                                       
                  $$ |                                       
                  \__|                                       
	Wrapper around cin >>
*/
int input()
{
	string entree = "";
	cin >> entree;
	try{
		stoi(entree);
	} catch(exception &err){
		return 0;
	}
	return stoi(entree);
}

template <typename T> string to_str(const T& t) { 
   ostringstream os; 
   os<<t; 
   return os.str(); 
} 