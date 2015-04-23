#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	double n, p;
	while(scanf("%lf %lf", &n, &p)!=EOF){
		printf("%.0lf\n", exp(log(p)/n));
	}
	return 0;
}
