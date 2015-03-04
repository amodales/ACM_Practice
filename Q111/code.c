#include <stdio.h>
#include <stdlib.h>

int *ans, *res;

int check(int, int, int, int);

int main(){
	int i, n, temp;
	scanf("%d", &n);
	ans = (int*) malloc( sizeof(int)*n );
	res = (int*) malloc( sizeof(int)*n );
	for(i=0; i<n; i++){
		scanf("%d", &temp);
		ans[temp-1] = i;
	}
	while(scanf("%d", &temp)==1){
		res[temp-1] = 0;
		for(i=1; i<n; i++){
			scanf("%d", &temp);
			res[temp-1] = i;
		}
		printf("%d\n", check(0, 0, n, 0));
	}
	return 0;
}

int check(int first, int second, int n, int depth){
	int i, j, length, val;
	length = depth;
	for(i=first; i<n; i++){
		for(j=second; j<n; j++){
			if(ans[i]==res[j]){
				val = check(i+1, j+1, n, depth+1);
				if(val > length)	length = val;
			}
		}
	}
	return length;
}
