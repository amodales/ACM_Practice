#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	double a, b, temp, sin60 = sqrt(3.0)/2.0;
	int n, x, y, count, count1, count2, h1, h2, flag;
	while(scanf("%lf %lf\n", &a, &b)!=EOF){
		if(a < 1 || b < 1){
			printf("0 grid\n");
			continue;
		}
		x = (int) a;
		y = (int) b;
		/*
			count : maximum number of pipes (grid).
		*/
		count = x*y;
		flag = 0;
		/*
			a-1 or b-1 : height of triangle
			h1 or h2 : hypotenuse of triangle
			, also the number of levels there would be.
		*/
		h1 = (int) 1 + (b-1)/sin60;
		h2 = (int) 1 + (a-1)/sin60;
		/*
			If a-x>=0.5, then each number of pipes in all level would be the same.
			Otherwise, half of levels have one pipe less than others.
		*/
		if(a-x>=0.5)	count1 = h1*x;
		else	count1 = h1*x - h1/2;
		if(b-y>=0.5)	count2 = h2*y;
		else	count2 = h2*y - h2/2;
		if(count1 > count){
			count = count1;
			flag = 1;
		}
		if(count2 > count){
			count = count2;
			flag = 1;
		}
		if(flag){
			printf("%d skew\n", count);
		}else{
			printf("%d grid\n", count);
		}
	}
	return 0;
}
