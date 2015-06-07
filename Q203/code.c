#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926
#define eps 1e-4

typedef struct vec{
	double x, y;
}vec;

typedef struct Ship{
	/*
		x : x-coordinate
		y : y-coordinate
		sp : speed in nautical mile per hour.
		ac : angle measured from true north, course direction
		name : name of ship
		vc : direction vector
	*/
	double ac, x, y, sp, bear, dis;
	vec vc;
	char name[2000];
}Ship;

double cross_product(vec a, vec b){
	return a.x*b.y - a.y*b.x;
}

double cos_between(vec a, vec b){
	double den, num;
	num = a.x * b.x + a.y * b.y;
	den = hypot(a.x, a.y) * hypot(b.x, b.y);
	return num/den;
}

double round_digit(double a, int digit){
	double ret;
	long long int num, sign, i, fac = 1;
	for(i=0; i<digit; i++){
		fac *= 10;
	}
	a *= fac;
	num = (long long int) a;
	if( fabs((double) a - num) >= 0.5 - eps){
		sign = (a>0)? 1: -1;
		ret = (double) (num+sign)/fac;
	}else{
		ret = (double) (num)/fac;
	}
	return ret;
}

int main(){
	char scename[2000];
	int n, i, j;
	vec a;
	double bear, dis, ag;
	Ship own, other[1000];
	while(fgets(scename, 2000, stdin)!=NULL){
		scanf("%d\n", &n);
		fgets(own.name, 2000, stdin);
		scanf("%lf %lf %lf %lf\n", &own.x, &own.y, &own.ac, &own.sp);
		ag = own.ac * PI / 180.0;
		own.vc.x = sin(ag)*own.sp;
		own.vc.y = cos(ag)*own.sp;
		for(i=0; own.name[i]!='\n'; i++);
		own.name[i] = '\0';
		for(i=0; i<n; i++){
			fgets(other[i].name, 2000, stdin);
			scanf("%lf %lf %lf %lf\n", &other[i].x, &other[i].y, &other[i].ac, &other[i].sp);
			ag = other[i].ac * PI / 180.0;
			other[i].vc.x = sin(ag)*other[i].sp;
			other[i].vc.y = cos(ag)*other[i].sp;
			for(j=0; other[i].name[j]!='\n'; j++);
			other[i].name[j] = '\0';
		}
		printf("Scenario: %s\n", scename);
		printf("Boat ID         Bearing      Distance   Lights (left to right)\n");
		printf("---------------------------------------------------------------\n");
		/*
			Print out information of ships.
		*/
		for(i=0; i<n; i++){
			a.x = own.x - other[i].x;
			a.y = own.y - other[i].y;
			other[i].bear = acos(cos_between(a, other[i].vc)) * 180.0 / PI;
			if(cross_product(a, other[i].vc)<0) other[i].bear = 360.0 - other[i].bear;
			other[i].dis = round_digit(hypot(a.x, a.y), 2);
			bear = round_digit(other[i].bear, 2);
			if(fabs(bear-360.0)<=eps) bear = 0.000;
			printf("%-16s%7.2lf%12.2lf     ", other[i].name, bear, other[i].dis);
			if(other[i].dis>10.00+eps){
				printf("Lights not visible\n");
			}else{
				if(other[i].bear <= eps){
					printf("Green Masthead Red\n");
				}else if(other[i].bear > eps && other[i].bear < 2.5 - eps){
					printf("Masthead Green Red\n");
				}else if(other[i].bear >= 2.5 - eps && other[i].bear <= 110.0 + eps){
					printf("Masthead Green\n");
				}else if(other[i].bear > 110.0 + eps && other[i].bear < 115.0 - eps){
					printf("Stern Masthead Green\n");
				}else if(other[i].bear >= 115.0 - eps && other[i].bear < 180.0 - eps){
					printf("Stern Masthead\n");
				}else if(other[i].bear >= 180.0 - eps && other[i].bear <= 245.0 + eps){
					printf("Masthead Stern\n");
				}else if(other[i].bear > 245.0 + eps && other[i].bear < 250.0 - eps){
					printf("Red Masthead Stern\n");
				}else if(other[i].bear >= 250.0 - eps && other[i].bear <= 357.5 + eps){
					printf("Red Masthead\n");
				}else if(other[i].bear > 357.5 + eps && other[i].bear < 360.0 - eps){
					printf("Green Red Masthead\n");
				}
			}
		}
		/*
			Collision Warning.
		*/
		own.x += own.vc.x/20;
		own.y += own.vc.y/20;
		for(i=0; i<n; i++){
			other[i].x += other[i].vc.x/20;
			other[i].y += other[i].vc.y/20;
			a.x = own.x - other[i].x;
			a.y = own.y - other[i].y;
			bear = acos(cos_between(a, other[i].vc)) * 180.0 / PI;
			if(cross_product(a, other[i].vc)<0) bear = 360.0 - bear;
			dis = round_digit(hypot(a.x, a.y), 2);
			bear = round_digit(bear, 2);
			if(fabs(bear-360.0)<=eps) bear = 0.000;
			if(other[i].dis<=10.00+eps){
				if(fabs(other[i].bear - bear)>=358-eps||fabs(other[i].bear - bear)<=2.0+eps&&other[i].dis>dis+eps){
					printf("** Collision warning -->%s:  Distance =  %.2lf\n", other[i].name, dis);
				}
			}
		}
		printf("***************************************************************\n");
	}
	return 0;
}
