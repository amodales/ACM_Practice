#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Coordinate{
	int x, y;
}Coordinate;

void Quicksort(Coordinate [], int, int);

int Partition(Coordinate [], int ,int);
int Build_ConvexHull(Coordinate [], Coordinate [], int);
int Compare_Coordinate(Coordinate, Coordinate);
int is_cck(Coordinate, Coordinate, Coordinate);
int is_between(Coordinate, Coordinate, Coordinate);
int On_Line(Coordinate, Coordinate, Coordinate);

int main(){
	char name[22];
	Coordinate gp, Origin[1500], Copy[1500], CHull[1500], ret;
	int count, x, y, m, min, size, i, j, k, l;
	while(fgets(name, 22, stdin)!=NULL){
		/*
			Input.
		*/
		if(name[0]=='#')	break;
		count = 0;
		scanf("%d %d", &gp.x, &gp.y);
		while(scanf("%d %d", &x, &y)==2){
			if(x==0&&y==0)	break;
			ret.x = x;
			ret.y = y;
			Origin[count] = Copy[count] = ret;
			count++;
		}
		fgetc(stdin);
		/*
			Calculating
		*/
		size = Build_ConvexHull(CHull, Copy, count);
		min = count+1;
		for(i=0, j=size-1; i<size; i++){
			if(is_between(CHull[i], CHull[j], gp)){
				m = -1;
				for(k=0; k<count; k++){
					if(On_Line(CHull[i], CHull[j], Origin[k])){
						if(k>m)	m = k; 
					}
				}
				if(m<min)	min = m;
			}
			j = i;
		}
		/*
			Output
		*/
		i = 0;
		while(name[i]!='\n'){
			printf("%c", name[i]);
			i++;
		}
		while(i<20){
			printf(" ");
			i++;
		}
		printf("%2d\n", min+1);
	}
	return 0;
}

void Quicksort(Coordinate points[], int left, int right){
	int m;
	if(left<=right){
		m = Partition(points, left, right);
		Quicksort(points, left, m-1);
		Quicksort(points, m+1, right);
	}
}

int Partition(Coordinate points[], int left, int right){
	int i=left-1, j;
	Coordinate temp;
	for(j=left; j<right; j++){
		if(Compare_Coordinate(points[j], points[right])<=0){
			i++;
			temp = points[i];
			points[i] = points[j];
			points[j] = temp;
		}
	}
	i++;
	temp = points[i];
	points[i] = points[right];
	points[right] = temp;
	return i;
}

int Build_ConvexHull(Coordinate ch[], Coordinate points[], int count){
	Coordinate upper[1500], lower[1500];
	int i, size_upper, size_lower, ret;
	Quicksort(points, 0, count-1);
	for(i=0, size_upper=0; i<count; i++){
		while(size_upper>=2&&is_cck(upper[size_upper-2], upper[size_upper-1], points[i])<=0){
			size_upper--;
		}
		upper[size_upper++] = points[i];
	}
	for(i=count-1, size_lower=0; i>=0; i--){
		while(size_lower>=2&&is_cck(lower[size_lower-2], lower[size_lower-1], points[i])<=0){
			size_lower--;
		}
		lower[size_lower++] = points[i];
	}
	ret = 0;
	for(i=0; i<size_upper-1; i++){
		ch[ret++] = upper[i]; 
	}
	for(i=0; i<size_lower-1; i++){
		ch[ret++] = lower[i];
	}
	return ret;
}

int Compare_Coordinate(Coordinate a, Coordinate b){
	if(a.x>b.x){
		return 1;
	}else if(a.x<b.x){
		return -1;
	}else{
		if(a.y>b.y){
			return 1;
		}else if(a.y<b.y){
			return -1;
		}else{
			return 0;
		}
	}
}

int is_cck(Coordinate a, Coordinate b, Coordinate c){
	return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}

int is_between(Coordinate a, Coordinate b, Coordinate g){
	int dot_a, dot_b;
	dot_a = (b.x-a.x)*(g.x-a.x) + (b.y-a.y)*(g.y-a.y);
	dot_b = (a.x-b.x)*(g.x-b.x) + (a.y-b.y)*(g.y-b.y);
	if(dot_a>=0&&dot_b>=0)	return 1;
	else 	return 0;
}

int On_Line(Coordinate a, Coordinate b, Coordinate c){
	int cp = is_cck(a, b, c);
	if(cp==0&&is_between(a, b, c))	return 1;
	else 	return 0;
}
