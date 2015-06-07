#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int n, x, y, i, j;
	n = rand()%20+1;
	printf("%d\n", n);
	for(i=0; i<n; i++){
		x = rand()%5000+1;
		for(j=0; j<x; j++){
			printf("%c", 'A'+rand()%26);
		}
		printf("\n");
		y = rand()%5000+1;
		for(j=0; j<y; j++){
			printf("%c", 'A'+rand()%26);
		}
		printf("\n");
	}
	return 0;
}
