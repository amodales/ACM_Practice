#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dir_x[] = {0, 1,  0, -1};
int dir_y[] = {1, 0, -1,  0};

int main(){
	int m, n, x, y, ori, lost, i, c=0;
	int grid[51][51];
	char line[102], ch;
	scanf("%d %d\n", &m, &n);
	while(scanf("%d %d %c\n", &x, &y, &ch)==3){
		if(c!=0)	printf("\n");
		switch(ch){
			case 'N':
				ori = 0;
				break;
			case 'E':
				ori = 1;
				break;
			case 'S':
				ori = 2;
				break;
			case 'W':
				ori = 3;
				break;
			default:
				break;
		}
		lost = 0;
		memset(line, 0, sizeof(char)*102);
		fgets(line, 102, stdin);
		i=0;
		while(line[i]!='\n'&&line[i]!='\0'&&!lost){
			switch(line[i]){
				case 'R':
					ori++;
					ori = ori & 3;
					break;
				case 'L':
					ori--;
					ori = (ori + 4)& 3;
					break;
				case 'F':
					if(x + dir_x[ori] > m || y + dir_y[ori] > n 
					   || x + dir_x[ori] < 0 || y + dir_y[ori] < 0){
						if(grid[y][x]==0){
							grid[y][x] = 1;
							lost = 1;
						}
					}else{
						x = x + dir_x[ori];
						y = y + dir_y[ori];
					}
					break;
				default:
					break;
			}
			i++;
		}
		printf("%d %d ", x, y);
		switch(ori){
			case 0:
				printf("N");
				break;
			case 1:
				printf("E");
				break;
			case 2:
				printf("S");
				break;
			case 3:
				printf("W");
				break;
			default:
				break;
		}
		if(lost){
			printf(" LOST");
		}
		c++;
	}
	return 0;
}
