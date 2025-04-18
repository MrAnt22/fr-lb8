#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 100000000

int compare_ints(const void *a, const void *b){
	return (*(int *)a - *(int *)b);
}

int is_sorted(int *array, size_t size){
	for (size_t i = 1;i < size;i++){
		if(array[i-1] > array[i]){
			return 0;
		}
	}
	return 1;
}

void generate_array(int *array, size_t size, int type){
	for (size_t i = 0;i < size;i++){
		if (type == 0){
			array[i] = i;
		}
		else if (type == 1){
			array[i] = size - i;
		}
		else{
			array[i] = rand() % size;
		}
	}
}

double time_qsort(int *array, size_t size){
	clock_t start = clock();
	qsort(array,size,sizeof(int),compare_ints);
	clock_t end = clock();
	return (double)(end-start) / CLOCKS_PER_SEC;
}

int main(){
	srand(time(NULL));
	int *array = malloc(SIZE *sizeof(int));
	if(!array){
		perror("malloc");
		return 1;
	}
	
	printf("Test different input qsort\n");
	
	for (int type = 0;type < 3;type++){
		generate_array(array, SIZE, type);

		printf("Test case %d: ", type);
		if (type == 0){
			printf("Already sorted\n");
		}

		else if (type == 1){
			printf("Reversed\n");
		}

		else{
		printf("Random\n");
		}
	
		double time_spent = time_qsort(array, SIZE);
		printf("Time taken: %.6f\n",time_spent);
	
		if (is_sorted(array,SIZE)){
			printf("Array sorted correclty\n");
		}

		else{
			printf("Array sorted uncorreclty\n");
		}
	}
	free(array);
	return 0;
}







	


















