#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int n, i, j, k, max, count=0, stop, mark;
	int matrix[30][30][31];
	while(scanf("%d", &n)!=EOF){
		/*
			Input
		*/
		memset(matrix, 0, sizeof(matrix));
		max = -1;
		for(i=0; i<n; i++){
			scanf("%d %d", &j, &k);
			matrix[j][k][0] = 1;
			if(j>max) max = j;
			if(k>max) max = k;
		}
		/*
			Processing
			Modified Floyd-Warshall Algorithm
			Entry (i,j) means how many paths i to j.
			Modified: If Entry (i,k) > 0 and (k,i) > 0 
					then Entry (i,j) += (i,k) * (k,j)
			After finished, if (i,i) > 0, there is at least a path i to i,
					which means that there is a cycle from i to i.
		*/
		mark = -1;
		stop = 0;
		for(k=0; k<=max&!stop; k++){
			for(i=0; i<=max; i++){
				for(j=0; j<=max; j++){
					if(matrix[i][k][k]*matrix[k][j][k] != 0){
						matrix[i][j][k+1] = matrix[i][j][k] + matrix[i][k][k] * matrix[k][j][k];
					}else{
						matrix[i][j][k+1] = matrix[i][j][k];
					}
				}
			}
		}
		/*
			Modifying parameter of infinite paths.
			The first loop j :
				If both i ~> j != 0 and i ~> i != 0, 
					then let i ~> j = -1 and i ~> i = -1.
			The second loop j :
				If both i ~> j != 0 and j ~> j != 0,
					then let i ~> j = -1.
			The third loop j :
				If i ~> j > 0 , i ~> k = -1, and k ~> j != 0
					then let i ~> j = -1.
		*/
		for(i=0; i<=max; i++){
			if(matrix[i][i][max+1]!=0){
				for(j=0; j<=max; j++){
					if(matrix[i][j][max+1]!=0){
						matrix[i][j][max+1] = -1;
					}
				}
			}else{
				for(j=0; j<=max; j++){
					if(matrix[i][j][max+1]!=0&&matrix[j][j][max+1]!=0){
						matrix[i][j][max+1] = -1;
					}
				}
			}
		}
		for(i=0; i<=max; i++){
			for(j=0; j<=max; j++){
				if(matrix[i][j][max+1]>0){
					for(k=0; k<=max; k++){
						if(matrix[i][k][max+1]==-1&&matrix[k][j][max+1]!=0){
							matrix[i][j][max+1] = -1;
							break;
						}
					}
				}
			}
		}
		/*
			Print out matrix.
		*/
		printf("matrix for city %d\n", count);
		for(i=0; i<=max; i++){
			for(j=0; j<=max; j++){
				printf("%d", matrix[i][j][max+1]);
				if(j!=max)	printf(" ");
			}
			printf("\n");
		}
		count++;
	}
	return 0;
}
