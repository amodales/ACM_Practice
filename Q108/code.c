#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **, int);

int main(){
	int n, i, j, a, b, sum, max;
	int **matrix, **sum_lu;
	scanf("%d", &n);
	matrix = (int **) malloc( n * sizeof(int*) );
	sum_lu = (int **) malloc( n * sizeof(int*) );
	for(i=0; i<n; i++){
		matrix[i] = malloc( n * sizeof(int) );
		sum_lu[i] = malloc( n * sizeof(int) );
		for(j=0; j<n; j++){
			scanf("%d", &matrix[i][j]);
			sum_lu[i][j] = 0;
		}
	}
	max = matrix[0][0];
	/*
		loop for sum
	*/
	for(i=0; i<n ;i++){
		for(j=0; j<n; j++){
			sum_lu[i][j] = ((i>0)? sum_lu[i-1][j] : 0) 
				     + ((j>0)? sum_lu[i][j-1] : 0) 
				     - ((i>0&&j>0)? sum_lu[i-1][j-1] : 0) 
				     + matrix[i][j];
		}
	}
	/*
		loop for finding
	*/
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			for(a=i; a<n; a++){
				for(b=j; b<n; b++){
					sum = sum_lu[a][b]
					    - ((j>0)? sum_lu[a][j-1] : 0)
					    - ((i>0)? sum_lu[i-1][b] : 0)
					    + ((i>0&&j>0)? sum_lu[i-1][j-1] : 0);
					if(sum > max) max = sum;
					/* Debug
					printf("A(%d,%d,%d,%d)= %d ", i, j, a, b, sum);
					printf("[%d,%d,%d,%d]\n", sum_lu[a][b] 
								, ((j>0)? sum_lu[a][j-1] : 0)
								, ((i>0)? sum_lu[i-1][b] : 0)
								, ((i>0&&j>0)? sum_lu[i-1][j-1] : 0));
					*/
				}
			}
		}
	}
	printf("%d\n", max);
	/*
		Free memory
	*/
	for(i=0; i<n; i++){
		free(matrix[i]);
		free(sum_lu[i]);
	}
	free(matrix);
	free(sum_lu);
	/* Debug
	printf("Original Matrix:\n");
	print_matrix(matrix, n);
	printf("Sum of Matrix:\n");	
	print_matrix(sum_lu, n);
	*/
	return 0;
}

void print_matrix(int **matrix, int n){
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}
