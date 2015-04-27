#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check[4][13];

int main(){
	int i, j, y, x;
	srand(time(NULL));
	for(i=0; i<200; i++){
		memset(check, 0, sizeof(check));
		for(j=0; j<52; j++){
			y = rand() % 4;
			x = rand() % 13;
			while(check[y][x]!=0){
				y = rand() % 4;
				x = rand() % 13;
			}
			check[y][x] = 1;
			if(j!=0&&j!=26)		printf(" ");
			switch(x){
				case 0:
					printf("A");
					break;
				case 9:
					printf("T");
					break;
				case 10:
					printf("J");
					break;
				case 11:
					printf("Q");
					break;
				case 12:
					printf("K");
					break;
				default:
					printf("%d", x+1);
			}
			switch(y){
				case 0:
					printf("C");
					break;
				case 1:
					printf("D");
					break;
				case 2:
					printf("H");
					break;
				case 3:
					printf("S");
					break;
			}
			if(j==25||j==51)	printf("\n");
		}
	}
	printf("#\n");
	return 0;
}
