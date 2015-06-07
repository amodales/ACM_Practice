#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926
#define eps 1e-7

typedef struct vec{
	double x, y;
}vec;

typedef struct Bullet{
	/*
		x : x-coordinate.
		y : y-coordinate.
		sp : speed of the bullet.
		ag : initial angle at the moment it is fired.
		dir : velocity.
	*/
	double x, y, sp, ag;
	vec dir;
}Bullet;

int main(){
	int times = 1;
	Bullet a, b;
	while(scanf("%lf %lf %lf %lf\n", &a.x, &a.y, &a.ag, &a.sp)!=EOF){
		scanf("%lf %lf %lf %lf\n", &b.x, &b.y, &b.ag, &b.sp);
		a.dir.x = a.sp * cos(a.ag * PI / 180);
		a.dir.y = a.sp * sin(a.ag * PI / 180);
		b.dir.x = b.sp * cos(b.ag * PI / 180);
		b.dir.y = b.sp * sin(b.ag * PI / 180);
		while(a.x < b.x - eps){
			for(){

			}
		}
		printf("Robot Problem #%d: ", times);
		times++;
	}
	return 0;
}
