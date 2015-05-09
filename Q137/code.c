#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define eps 1e-4

typedef struct Point{
	double x, y;
}Point;

int is_cck(Point, Point, Point);
double area(Point [], int);
double max(double, double);
double min(double, double);

void Quicksort(Point [], int, int);

int Construct_Convexhull(Point [], Point [], int);
int Point_Compare(Point, Point);
int is_inside(Point [], Point, int);
int Partition(Point [], int, int);
int On_Line(Point, Point, Point);

int main(){
	Point first[1200], second[1200], third[1200];
	Point ch_first[1200], ch_second[1200], ch_third[1200];
	int a, b, c, i, j, m, n;
	int det, dx, dy, a1, a2, b1, b2, c1, c2;
	double sum;
	while(scanf("%d", &a)!=EOF){
		if(a==0)	break;
		for(i=0; i<a; i++){
			scanf("%lf %lf", &first[i].x, &first[i].y);
		}
		scanf("%d", &b);
		for(i=0; i<b; i++){
			scanf("%lf %lf", &second[i].x, &second[i].y);
		}
		c = 0;
		for(i=0, j=a-1; i<a; j=i++){
			for(m=0, n=b-1; m<b; n=m++){
				a1 = (int)first[i].y - (int)first[j].y;
				a2 = (int)second[m].y - (int)second[n].y;
				b1 = (int)first[j].x - (int)first[i].x;
				b2 = (int)second[n].x - (int)second[m].x;
				det = a1*b2 - a2*b1;
				if(det==0)	continue;
				c1 = a1*(int)first[j].x + b1*(int)first[j].y;
				c2 = a2*(int)second[n].x + b2*(int)second[n].y;
				dx = b2*c1 - b1*c2;
				dy = a1*c2 - a2*c1;
				third[c].x = (double)dx/(double)det;
				third[c].y = (double)dy/(double)det;
				if(On_Line(first[i], first[j], third[c])&&On_Line(second[m], second[n], third[c]))	c++;
			}
		}	
		for(i=0; i<a; i++){
			if(is_inside(second, first[i], b)){
				third[c++] = first[i];
			}
		}
		for(i=0; i<b; i++){
			if(is_inside(first, second[i], a)){
				third[c++] = second[i];
			}
		}
		c = Construct_Convexhull(ch_third, third, c);
		sum = area(first, a) + area(second, b) - 2.0*area(ch_third, c);
		printf("%8.2lf", sum);
	}
	printf("\n");
	return 0;
}

int Construct_Convexhull(Point copy[], Point source[], int size){
	Point upper[1200], lower[1200];
	int i, count, size_upper=0, size_lower=0;
	Quicksort(source, 0, size-1);
	for(i=0; i<size; i++){
		while(size_upper>=2&&is_cck(upper[size_upper-2], upper[size_upper-1], source[i])<=0){
			size_upper--;
		}
		upper[size_upper++] = source[i];
	}
	for(i=size-1; i>=0; i--){
		while(size_lower>=2&&is_cck(lower[size_lower-2], lower[size_lower-1], source[i])<=0){
			size_lower--;
		}
		lower[size_lower++] = source[i];
	}
	count = 0;
	for(i=0; i<size_upper-1; i++){
		copy[count++] = upper[i];
	}
	for(i=0; i<size_lower-1; i++){
		copy[count++] = lower[i];
	}
	return count;
}

int Point_Compare(Point a, Point b){
	if(fabs(a.x-b.x)<eps){
		if(fabs(a.y-b.y)<eps){
			return 0;
		}else if(a.y < b.y){
			return -1;
		}else{
			return 1;
		}
	}else if(a.x < b.x){
		return -1;
	}else{
		return 1;
	}
}

int On_Line(Point a, Point b, Point c){
	int left, right;
	left = min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x);
	right = min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
	return left && right;
}

double min(double a, double b){
	return (a<b)? a: b;
}

double max(double a, double b){
	return (a<b)? b: a;
}

void Quicksort(Point poly[], int left, int right){
	int m;
	if(left<right){
		m = Partition(poly, left, right);
		Quicksort(poly, left, m-1);
		Quicksort(poly, m+1, right); 
	}
}

int Partition(Point poly[], int left, int right){
	int i = left - 1, j;
	Point temp;
	for(j=left; j<right; j++){
		if(Point_Compare(poly[j], poly[right])<=0){
			i++;
			temp = poly[i];
			poly[i] = poly[j];
			poly[j] = temp;
		}
	}
	i++;
	temp = poly[i];
	poly[i] = poly[right];
	poly[right] = temp;
	return i;
}

int is_inside(Point poly[], Point p, int size){
	int i, j;
	for(i=0, j=size-1; i<size; j=i++){
		if(is_cck(p, poly[j], poly[i])>0)	return 0;
	}
	return 1;
}

/*
	counterclockwise if value > 0
	clockwise if value < 0
	collinear if value = 0
*/
int is_cck(Point a, Point b, Point c){
	double ret = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
	if(fabs(ret)<eps)	return 0;
	if(ret>eps)	return 1;
	if(ret<-eps)	return -1;
}

double area(Point poly[], int size){
	int i, j;
	double sum=0;
	for(i=0, j=size-1; i<size; j=i++){
		sum += ((poly[j].x*poly[i].y) - (poly[i].x*poly[j].y));
	}
	sum = fabs(sum)/2;
	return sum;
}
