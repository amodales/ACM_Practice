#include <stdio.h>
#include <stdlib.h>

int grid[10][100];
int path[10][100];
int minm[10][100];

int m, n;

int get_min_index(int, int);

int main(){
	int i, j;
	int index, min;
	while(scanf("%d %d", &m, &n)==2){
		/*
			Receiving matrix.
		*/
		for(i=0; i<m; i++){
			for(j=0; j<n; j++){
				scanf("%d", &grid[i][j]);
			}
		}
		/*
			Building min & path matrix.
		*/
		for(i=0; i<m; i++){
			minm[i][n-1] = grid[i][n-1];
		}
		for(j=n-2; j>=0; j--){
			for(i=0; i<m; i++){
				index = get_min_index(j+1, i);
				minm[i][j] = minm[index][j+1] + grid[i][j];
				path[i][j] = index;
			}
		}
		min = minm[0][0];
		index = 0;
		for(i=1; i<m; i++){
			if(min>minm[i][0]){
				min = minm[i][0];
				index = i;
			}
		}
		printf("%d", index+1);
		for(j=0; j<n-1; j++){
			index = path[index][j];
			printf(" %d", index+1);
		}
		printf("\n%d\n", min);
	}
	return 0;
}

int get_min_index(int x, int y){
	int small, big;
	if(y==0){
		small = y;
		y = (y+1)%m;
		big = m-1;
	}else if(y==m-1){
		small = 0;
		big = y;
		y = y-1;
	}else{
		small = y-1;
		big = y+1;
	}
	if(minm[small][x]>minm[big][x]){
		if(minm[big][x]>minm[y][x]){
			return y;
		}else if(minm[big][x]==minm[y][x]){
			return y;
		}else{
			return big;
		}
	}else if(minm[small][x]==minm[big][x]){
		if(minm[small][x]>minm[y][x]){
			return y;
		}else if(minm[small][x]==minm[y][x]){
			return small;
		}else{
			return (small>big)? big: small;
		}
	}else{
		if(minm[small][x]>minm[y][x]){
			return y;
		}else if(minm[small][x]==minm[y][x]){
			return (y>small)? small: y;
		}else{
			return small;
		}
	}
}
