#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int m, n, x, y, c, limit, i, j, ins;
	srand(time(NULL));
	m = rand()%51;
	n = rand()%51;
	printf("%d %d\n", m, n);
	for(i=0; i<20; i++){
		x = rand()%(m+1);
		y = rand()%(n+1);
		c = rand()%4;
		printf("%d %d ", x ,y);
		switch(c){
			case 0:
				printf("N");
				break;
			case 1:
				printf("E");
				break;
			case 2:
				printf("S");
				break;
			case 3:
				printf("W");
				break;
			default:
				break;
		}
		printf("\n");
		limit = rand()%15;
		while(limit==0){
			limit = rand()%15;
		}
		for(j=0; j<limit; j++){
			ins = rand()%3;
			switch(ins){
				case 0:
					printf("R");
					break;
				case 1:
					printf("L");
					break;
				case 2:
					printf("F");
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
	return 0;
}
