#include <stdio.h>
#include <stdlib.h>

typedef struct Coordinate{
	int x, y;
}Coordinate;

typedef struct Kingdom{
	Coordinate *array;
	int size;
	int capacity;
	int flag;
}Kingdom;

void add_point(Kingdom *, int, int);
void construct_convexhull(Kingdom *);
void draw_graph(Kingdom);
int is_lesser(Coordinate, int, int);
int is_cck(Coordinate, Coordinate, Coordinate);
int is_inside_kingdom(Kingdom, int, int);

int main(){
	Kingdom k[20];
	int x, y, n, i, num=0;
	while(scanf("%d", &n)==1&&n!=-1){
		/*
			Initialize a new array(Kingdom).
		*/
		k[num].capacity = n;
		k[num].size = 0;
		k[num].array = (Coordinate*) malloc( n*sizeof(Coordinate) );
		k[num].flag = 1;
		/*
			Accept all the points from users.
		*/
		for(i=0; i<n; i++){
			scanf("%d %d", &x, &y);
			add_point(&k[num], x, y);
		}
		construct_convexhull(&k[num]);
		num++;
	}
	/*
		Accept locations of all missiles.
	*/
	while(scanf("%d %d"), &x, &y)==2){
		for(i=0; i<num; i++){
			if(is_inside_kingdom(k[num], x, y)>0){
				k[num].flag = 0;
			}
		}	
	}
	/*
		Calculate the area of remaining kingdom.
	*/
	for(i=0; i<num; i++){
		if(k[num].flag==1){
			
		}
	}	
	/*
		Release memory.
	*/
	for(i=0; i<num; i++){
		free(k[i].array);
	}
}

/*
	Insert point(house & power station) into array(Kingdom) in ascending order according to x.
*/
void add_point(Kingdom *k, int x, int y){
	int index = 0, i;
	Coordinate temp;
	while(index<k->size&&is_lesser(k->array[index], x, y)==1){
		index++;	
	}
	if(index<k->size){
		for(i=k->size; i>index; i--){
			temp = k->array[i];
			k->array[i] = k->array[i-1];
			k->array[i-1] = temp;
		}
	}
	k->array[index].x = x;
	k->array[index].y = y;
	k->size++;	
}

/*
	Construct a convexhull of Kingdom.
	Set size to be the number of vertices of convexhull.
*/
void construct_convexhull(Kingdom *k){
	int size_upper = 0, size_bottom = 0, i;
	Coordinate *list_upper, *list_bottom;
	list_upper = (Coordinate*) malloc( k->capacity * sizeof(Coordinate) );
	list_bottom = (Coordinate*) malloc( k->capacity * sizeof(Coordinate) );
	/*
		Construct upper convexhull.
	*/
	for(i=k->capacity-1; i>=0; i--){
		while(size_upper>=2&&is_cck(list_upper[size_upper-1], list_upper[size_upper-2], k->array[i])>=0){
			size_upper--;
		}
		list_upper[size_upper] = k->array[i];
		size_upper++;
	}
	/*
		Construct bottom convexhull.
	*/
	for(i=0; i<k->capacity; i++){
		while(size_bottom>=2&&is_cck(list_bottom[size_bottom-1], list_bottom[size_bottom-2], k->array[i])>=0){
			size_bottom--;
		}
		list_bottom[size_bottom] = k->array[i];
		size_bottom++;
	}
	/*
		Merge two list into one list, and save into the original kingdom.
	*/
	k->capacity = size_upper + size_bottom -2;
	k->size = 0;
	for(i=0; i<size_upper-1; i++){
		k->array[k->size] = list_upper[i];
		k->size++;
	}
	for(i=0; i<size_bottom-1; i++){
		k->array[k->size] = list_bottom[i];
		k->size++;
	}
	/*
		Free memory
	*/
	free(list_upper);
	free(list_bottom);
}

/*
	Draw a simple graph.
*/
void draw_graph(Kingdom k){
	int matrix[51][51];
	int i, j;
	for(i=0; i<51; i++){
		for(j=0; j<51; j++){
			matrix[i][j] = 0;
		}
	}
	for(i=0; i<k.size; i++){
		matrix[k.array[i].y][k.array[i].x] = 1;
	}
	for(i=0; i<51; i++){
		for(j=0; j<51; j++){
			switch(matrix[i][j]){
				case 0:	printf(" "); break;
				case 1: printf("*"); break;
				default: break;
			}
		}
		printf("\n");
	}
	printf("\n\n\n");
}

/*
	Return 1 if Cord < (x,y)
	Otherwise, return 0.
*/
int is_lesser(Coordinate a, int x, int y){
	if(x>a.x){
		return 1;
	}else if(x==a.x){
		if(y>a.y){
			return 1;
		}else if(y==a.y){
			/*
				This condition shouldn't happen.
				Just list it in case.
			*/
			return 0;
		}else{
			return -1;
		}
	}else{
		return -1;
	}
}

/*
	Return value = 0 if three points are colinear.
	Return value > 0 if three points are clockwise.
	Return value < 0 if three points are counterclockwise.
	i.e. Return cross product of three points.
	     A(x1,y1), B(x2,y2), C(x3,y3)
	| x1 y1 1|   | x1    y1    1|
	| x2 y2 1| = | x2-x1 y2-y1 0| = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1)
	| x3 y3 1|   | x3-x1 y3-y1 0|
*/
int is_cck(Coordinate a, Coordinate b, Coordinate c){
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

/*
	Return value > 0 if the point is inside the kingdom.
	Return value = 0 if the point lies on the boundary of the kingdom.
	Reutrn value < 0 if the point is outside the kingdom. 
*/
int is_inside_kingdom(Kingdom k, int x, int y){

}
