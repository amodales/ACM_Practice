#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float matrix[20][20][20];
int pre[20][20][20];

void Print_Out_Sequence(int, int, int);

int main(){
	int n, row, col, inter, step, found, mark_row, mark_step;
	float result;
	while(scanf("%d", &n)!=EOF){
		memset(matrix, 0, sizeof(matrix));
		memset(pre, 0, sizeof(pre));
		found = 0;
		for(row=0; row<n; row++){
			for(col=0; col<n; col++){
				if(row==col){
					matrix[row][col][0] = 1;
				}else{
					scanf("%f", &matrix[row][col][0]);
				}
				pre[row][col][0] = row;
			}
		}
		for(step=1; step<n&&!found; step++){
			for(inter=0; inter<n; inter++){
				for(row=0; row<n; row++){
					for(col=0; col<n; col++){
						result = matrix[row][inter][step-1] * matrix[inter][col][0];
						if(result>matrix[row][col][step]){
							matrix[row][col][step] = result;
							pre[row][col][step] = inter;
						}
					}
				}
			}
			for(row=0; row<n&&!found; row++){
				if(matrix[row][row][step]>1.01){
					found = 1;
					mark_row = row;
					mark_step = step;
				}
			}
		}
		if(found){
			Print_Out_Sequence(mark_row, mark_row, mark_step);
			printf("%d\n", mark_row+1);
		}else{
			printf("no arbitrage sequence exists\n");
		}
	}
	return 0;
}

void Print_Out_Sequence(int row, int col, int step){
	if(step>=0){
		Print_Out_Sequence(row, pre[row][col][step], step-1);
		printf("%d ", pre[row][col][step]+1);
	}
}
