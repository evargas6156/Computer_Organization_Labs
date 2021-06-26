
#include <stdio.h>
#include <malloc.h>

int** matMult(int **a, int **b, int size){
	// (4) Implement your matrix multiplication here. You will need to create a new matrix to store the product.
	int** answer = (int**)malloc(size * sizeof(int*));
	for(int i = 0; i < size; i++){
		*(answer + i) = (int*)malloc(size * sizeof(int));
		for(int j = 0; j < size; j++){
			int sum = 0;
			for(int k = 0; k < size; k++){
				sum = sum + ((*(*(a + i) + k)) * (*(*(b + k) + j)));
			}
			(*(*(answer + i) + j)) = sum;
		}
	}
	return answer;
}

void printArray(int **arr, int n){
	// (2) Implement your printArray function here
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%d   ",(*(*(arr + i) + j)));
			if(j == (n -1 )){
				printf("\n");
			}
		}
	}
	printf("\n");
}

int main() {
	int n = 5;
	int **matA, **matB, **matC;
	// (1) Define 2 n x n arrays (matrices)
	matA = (int**)malloc(n * sizeof(int*));
	matB = (int**)malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++){
		*(matA + i) = (int*)malloc(n * sizeof(int));
		*(matB + i) = (int*)malloc(n * sizeof(int));
		for(int j = 0; j < n; j++){
			*(*(matA + i) + j) = 0;
			*(*(matB + i) + j) = 0;
		}
	}
	**matA = 1;
	*(*(matA + 1) + 1) = 2;
	*(*(matA + 2) + 2) = 3;
	*(*(matA + 3) + 3) = 4;
	*(*(matA + 4) + 4) = 5;

	*((*matB) + 4) = 5;
	*(*(matB + 1) + 3) = 4;
	*(*(matB + 2) + 2) = 3;
	*(*(matB + 3) + 1) = 2;
	*(*(matB + 4) + 0) = 1;


	// (3) Call printArray to print out the 2 arrays here.
	printf("Printing matA: \n");
	printArray(matA, n);
	printf("Printing matB: \n");
	printArray(matB, n);

	//(5) Call matMult to multiply the 2 arrays here.
	matC = matMult(matA, matB, n);

	//(6) Call printArray to print out resulting array here.
	printf("Printing the result of matA * matB: \n");
	printArray(matC, n);


    return 0;
}
