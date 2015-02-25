#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **, int);

int main(){
	int n, i, j, a, b, sum, max;
	int **matrix, **sum_lu;
	scanf("%d", &n);
	matrix = (int **) malloc( (n+1) * sizeof(int*) );
	sum_lu = (int **) malloc( (n+1) * sizeof(int*) );
	for(i=0; i<=n; i++){
		matrix[i] = (int *) malloc( (n+1) * sizeof(int) );
		sum_lu[i] = (int *) malloc( (n+1) * sizeof(int) );
		for(j=0; j<=n; j++){
			sum_lu[i][j] = 0;
		}
	}
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			scanf("%d", &matrix[i][j]);
		}
	}
	max = matrix[1][1];
	/*
		loop for summation
	*/
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			sum_lu[i][j] = sum_lu[i-1][j] 
				     + sum_lu[i][j-1] 
				     - sum_lu[i-1][j-1] 
				     + matrix[i][j];
		}
	}
	/*
		loop for finding maximum.
	*/
	for(i=1; i<=n; i++){
		for(j=1; j<=n; j++){
			for(a=i; a<=n; a++){
				for(b=j; b<=n; b++){
					sum = sum_lu[a][b]
					    - sum_lu[a][j-1]
					    - sum_lu[i-1][b]
					    + sum_lu[i-1][j-1];
					if(sum > max) max = sum;
				}
			}
		}
	}
	printf("%d\n", max);
	/*
		Free memory
	*/
	for(i=0; i<=n; i++){
		free(matrix[i]);
		free(sum_lu[i]);
	}
	free(matrix);
	free(sum_lu);
	return 0;
}
