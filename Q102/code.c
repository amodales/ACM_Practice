#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int i, x, y, tab;
	int x_index[] = {1, 2, 0};
	int y_index[] = {2, 0, 1};
	char words[3][4];
	char word[] = {'B','G','C'};
	long num[3];
	long bins[4][3];
	long min_num, l, r;
	for(i=0; i<3; i++){
		words[i][3] = '\0';
		words[i][2] = word[i];
	}
	while(scanf("%ld %ld %ld %ld %ld %ld %ld %ld %ld", &bins[0][0], &bins[0][1], &bins[0][2], 
								&bins[1][0], &bins[1][1], &bins[1][2], 
								&bins[2][0], &bins[2][1], &bins[2][2])==9){
		min_num = (1<<31) - 1;
		for(i=0; i<3; i++){
			num[i] = 0;
		}
		for(y=0; y<3; y++){
			for(x=0; x<3; x++){
				num[x] += bins[y][x];
			}
		}		
		for(y=0; y<3; y++){
			for(x=0; x<3; x++){
				bins[y][x] = num[x] - bins[y][x];
			}
		}
		for(i=0; i<3; i++){
			x = x_index[i];
			y = y_index[i];
			l = bins[0][y] + bins[1][x];
			r = bins[0][x] + bins[1][y];
			if(l>r){
				bins[3][i] = r;
				words[i][0] = word[x];
				words[i][1] = word[y];	
			}else if(l==r){
				bins[3][i] = l;
				if(word[x]>word[y]){
					words[i][0] = word[y];
					words[i][1] = word[x];
				}else{
					words[i][0] = word[x];
					words[i][1] = word[y];
				}
			}else{
				bins[3][i] = l;
				words[i][0] = word[y];
				words[i][1] = word[x];
			}
			bins[3][i] += bins[2][i];
			if(min_num>bins[3][i]){
				min_num = bins[3][i];
				tab = i;
			}else if(min_num==bins[3][i]&&strcmp(words[tab], words[i])>0){
				tab = i;
			}
		}
		printf("%s %ld\n", words[tab], min_num);
	}
	return 0;
}
