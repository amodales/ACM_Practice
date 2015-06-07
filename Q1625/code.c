#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 5001
#define INF 10e7

/*
	color_a[26][2] : Recording the starting and ending positions 
			 of all colors in list A.
	color_b[26][2] : Recording the starting and ending positions
			 of all colors in list B.
	mat[NUM][NUM] : matrix for dynamic programming.
*/
char a[NUM], b[NUM];
int c_a, c_b;
int color_a[26][2], color_b[26][2];
int mat[NUM][NUM];

int main(){
	char ch;
	int i, j, k, res, n, c;
	scanf("%d\n", &n);
	while(n>0){
		/*
			Initialization on parameter.

			Setting the starting positions of all colors be INF
			is for convenience, since if they are INF, we can
			promise that if one color K didn't exist in the list,
			the statement "i >= color[K][0]" would always be false.

			On the other hand, setting the ending positions of all
			colors be 0 is also for convenience, since if they are 0,
			we can promise that if one color K didn't exist in the list,
			the statement "i < color[K][1]" would always be false.
		*/
		c_a = 0;
		c_b = 0;
		for(i=0; i<26; i++){
			color_a[i][0]=color_b[i][0]=INF;
			color_a[i][1]=color_b[i][1]=0;
		}
		/*
			Getting data.
		*/
		ch = fgetc(stdin);
		while(ch!='\n'){
			a[c_a] = ch;
			if(color_a[ch-'A'][0]==INF) color_a[ch-'A'][0] = c_a+1;
			color_a[ch-'A'][1] = ++c_a;
			ch = fgetc(stdin);
		}
		ch = fgetc(stdin);
		while(ch!='\n'){
			b[c_b] = ch;
			if(color_b[ch-'A'][0]==INF) color_b[ch-'A'][0] = c_b+1;
			color_b[ch-'A'][1] = ++c_b;
			ch = fgetc(stdin);
		}
		/*
			Dynamic Programming.
		*/
		for(i=0; i<=c_a; i++){
			for(j=0; j<=c_b; j++){
				res = INF;
				c = 0;
				for(k=0; k<26; k++){
					if((i>=color_a[k][0]||j>=color_b[k][0])&&(i<color_a[k][1]||j<color_b[k][1])) c++;
				}
				if(i>0) res = (res>mat[i-1][j])? mat[i-1][j]: res;
				if(j>0) res = (res>mat[i][j-1])? mat[i][j-1]: res;
				mat[i][j] = (res==INF)? c: c+res;
			}
		}
		/*
			End.
		*/
		printf("%d\n", mat[c_a][c_b]);
		n--;
	}
	return 0;
}
