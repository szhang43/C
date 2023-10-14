#include <stdio.h> 
#include <stdlib.h> 



int cmpfunc(const void *a, const void *b){
	return (*(int*)a - *(int*)b ); 
} 

void sort_array( int *array, int N){
	qsort(array, N, sizeof(int), cmpfunc); 
} 

int main(){
	char values[5] = {"This", "prints", "correctly", "or", "not"};

	sort_array(values, 5);

	for(int i = 0; i <  5; i++){
		printf("%d\t", values[i]); 
	} 
} 


