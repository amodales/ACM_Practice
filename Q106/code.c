#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int list[1000004];

int gcd(int, int);

int main(){
	int n, r, s, m, i, top, total, tri, x, y, z;
	memset(list, 0, sizeof(list));
	while(scanf("%d", &n)!=EOF){
		total = 0;
		tri = 0;
		m = (int) sqrt(n);
		if(m*m<n)	m++;
		for(r=1; r<=m; r++){
			top = (n-r*r>r-1)? r-1: n-r*r;
			for(s=1; s<=top; s++){
				x = r*r - s*s;
				y = 2*r*s;
				z = r*r + s*s;
				if(x*x + y*y == z*z && z <= n){
					if(gcd(x,y)==1){
						tri++;
						for(i=1; i*z<=n; i++){
							list[x*i-1] = 1;
							list[y*i-1] = 1;
							list[z*i-1] = 1;
						}
					}
				}
			}
		}
		for(i=0; i<n; i++){
			if(list[i]==0)	total++;
			list[i] = 0;
		}
		printf("%d %d\n", tri, total);
	}
	return 0;
}

int gcd(int a, int b){
	return (b==0)? a: gcd(b, a%b);
}
