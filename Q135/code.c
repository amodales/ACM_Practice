#include <stdio.h>
#include <stdlib.h>

int main(){
	int m, i, j, k, num, limit, count=0;
	while(scanf("%d", &m)!=EOF){
		if(count!=0)	printf("\n");
		for(i=1; i<=m; i++){
			printf("1");
			for(j=2; j<=m; j++){
				printf(" %d", j+(i-1)*(m-1));
			}
			printf("\n");
		}
		for(i=2; i<=m; i++){
			for(j=m+1; j<=2*m-1; j++){
				printf("%d", i);
				for(k=0; k<m-1; k++){
					limit = 2 + (k+1)*(m-1);
					num = k*(i-2) + (j-m-1);
					printf(" %d", num%(m-1)+limit);
				}
				printf("\n");
			}
		}
		count++;
	}
	return 0;
}
