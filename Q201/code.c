#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int right, down;
}Node;

int main(){
	int i, j, k, l, m, n;
	int count, time = 1, ans, has;
	char ch;
	Node dot[10][10];
	while(scanf("%d\n", &n)!=EOF){
		if(time>1)	printf("\n**********************************\n\n");
		scanf("%d\n", &m);
		memset(dot, 0, sizeof(dot));
		for(k=0; k<m; k++){
			scanf("%c %d %d\n", &ch, &i, &j);
			if(ch=='V'){
				dot[j][i].down = 1;
			}else{
				dot[i][j].right = 1;
			}
		}
		/*
			Find square.
		*/
		printf("Problem #%d\n\n", time);
		has = 0;
		for(k=1; k<=n; k++){
			count = 0;
			for(i=1; i<=n; i++){
				for(j=1; j<=n; j++){
					if((i+k)<=n&&(j+k)<=n){
						for(l=0; l<k; l++){
							ans = dot[i+l][j].down
								&&dot[i][j+l].right
								&&dot[i+l][j+k].down
								&&dot[i+k][j+l].right;
							if(!ans){
								break;
							}
						}
						if(l==k)	count++;
					}
				}
			}
			if(count!=0){
				printf("%d square (s) of size %d\n", count, k);
				has++;
			}
		}
		if(has==0)	printf("No completed squares can be found.\n");
		time++;
	}
	return 0;
}
