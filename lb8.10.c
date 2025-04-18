#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 1000000

int compare_ints(const void *a, const void *b){
	return (*(int *)a - *(int*)b);
}

int is_sorted(int *array, size_t size){
	for (size_t i = 1;i < size;i++){
		if (array[i-1] > array[i]){
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
		else if(type == 1){
			array[i] = size - i;
		}
		else{
			array[i] = rand() % size;
		}
	}
}

double time_qsort(int *array, size_t size){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	qsort(array, size, sizeof(int), compare_ints);

	clock_gettime(CLOCK_MONOTONIC, &end);

	return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main(){
	srand(time(NULL));
	int *array = malloc(SIZE * sizeof(int));
	if (!array){
		perror("malloc");
		return 1;
	}

	printf("| Entry data	      | Time	         | Sort result	 |\n");
	printf("|-----------------|--------------|-------------|\n");

	for (int type = 0;type < 3;type++){
		generate_array(array,SIZE,type);

		double time_spent = time_qsort(array, SIZE);

		const char *input_type;
		if (type == 0){
			 input_type = "Sorted";
		}
		else if (type == 1){
			input_type = "Reversed";
		}
		else{
			input_type = "Random";
		}

		printf("| %-20s | %-20.6f | %-20s |\n", input_type, time_spent, is_sorted(array,SIZE) ? "Correct" : "Wrong");
		
	}
	free(array);
	return 0;
}















