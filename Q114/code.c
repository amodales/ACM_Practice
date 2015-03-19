#include <stdio.h>
#include <stdlib.h>

/*
	Direction Numbers
	0 : right
	1 : up
	2 : left
	3 : down
	When a ball hits a bumper, it will turn right (clockwise) 90 degrees,
	which means that the direction number will minus one.
*/
int dir_x[] = {1, 0, -1,  0};
int dir_y[] = {0, 1,  0, -1};
int grid[50][50];

typedef struct Ball{
	int x, y;
	int life;
	int dir;
	int score;
}Ball;

typedef struct Bumper{
	int cost;
	int val;
}Bumper;

int main(){
	int m, n, cost, p;
	int i, j, total_score=0;
	int x, y;
	Bumper *bumpers;
	Ball obj;
	scanf("%d %d", &m, &n);
	scanf("%d", &cost);
	scanf("%d", &p);
	bumpers = (Bumper*) malloc( sizeof(Bumper)*p );
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			grid[j][i] = -1;
		}
	}
	for(i=0; i<p; i++){
		scanf("%d", &x);
		scanf("%d", &y);
		scanf("%d", &bumpers[i].val);
		scanf("%d", &bumpers[i].cost);
		grid[y-1][x-1] = i;
	}
	while(scanf("%d %d %d %d", &obj.x, &obj.y, &obj.dir, &obj.life)==4){
		obj.score = 0;
		obj.x -= 1;
		obj.y -= 1;
		/*
			Simulation Start.	
		*/
		while(obj.life>0){
			obj.life -= 1;
			x = obj.x + dir_x[obj.dir];
			y = obj.y + dir_y[obj.dir];
			/*
				Hit the walls.
			*/
			if(x<=0||x>=m-1||y<=0||y>=n-1){
				obj.life -= cost;
				(obj.dir==0)? obj.dir=3: obj.dir--;
				continue;
			}
			/*
				Hit a bumper.
			*/
			if(grid[y][x]>=0&&obj.life>0){
				obj.score += bumpers[grid[y][x]].val;
				obj.life -= bumpers[grid[y][x]].cost;
				(obj.dir==0)? obj.dir=3: obj.dir--;
				continue;
			}
			obj.x = x;
			obj.y = y;
		}
		printf("%d\n", obj.score);
		total_score += obj.score;	
	}
	printf("%d\n", total_score);
	return 0;
}
