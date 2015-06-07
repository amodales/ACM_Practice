#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-6

typedef struct Point{
	double x, y;
}Point;

double min(double a, double b){
	return (a>b)? b: a;
}

double max(double a, double b){
	return (a>b)? a: b;
}

int equal(Point a, Point b){
	return (fabs(a.x - b.x)<eps) && (fabs(a.y - b.y)<eps);
}

double cross_product(Point a, Point b, Point c){
	return (c.x - a.x)*(b.y - a.y) - (b.x - a.x)*(c.y - a.y);
}

int main(){
	int i, j, ans;
	int left_x, left_y, right_x, right_y;
	Point a, b, c, p, low, high;
	double x1, y1, x2, y2, x3, y3;
	double low_x, low_y, high_x, high_y;
	double total_area, area;
	while(scanf("%lf %lf %lf %lf %lf %lf\n", &x1, &y1, &x2, &y2, &x3, &y3)!=EOF){
		if(fabs(x1)<eps&&fabs(y1)<eps
				&&fabs(x2)<eps&&fabs(y2)<eps
					&&fabs(x3)<eps&&fabs(y3)<eps)	break;
		ans = 0;
		low_x = min( min(x1, x2), x3);
		low_y = min( min(y1, y2), y3);
		high_x = max( max(x1, x2), x3);
		high_y = max( max(y1, y2), y3);
		low.x = low_x, low.y = low_y;
		high.x = high_x, high.y = high_y;
		left_x = (int) max( 1.0, floor(low_x));
		left_y = (int) max( 1.0, floor(low_y));
		right_x = (int) min( 99.0, floor(high_x)+1);
		right_y = (int) min( 99.0, floor(high_y)+1);
		a.x = x1, a.y = y1;
		b.x = x2, b.y = y2;
		c.x = x3, c.y = y3;
		total_area = fabs(cross_product(a, b, c));
		for(i=left_x; i<=right_x; i++){
			for(j=left_y; j<=right_y; j++){
				p.x = i, p.y = j;
				if(equal(p, a)||equal(p, b)||equal(p, c)){
					ans++;
				}else if(total_area < eps){
					if(fabs(cross_product(p, low, high))<eps){
						if(low.x<=p.x&&p.x<=high.x&&low.y<=p.y&&p.y<=high.y){
							ans++;
						}
					}
				}else{
					area = fabs(cross_product(p, a, b));
					area += fabs(cross_product(p, b, c));
					area += fabs(cross_product(p, a, c));
					if(fabs(total_area - area) < eps){
						ans++;
					}
				}
			}
		}
		printf("%4d\n", ans);
	}
	return 0;
}
