#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dir_x[] = {0, 1,  0, -1};
int dir_y[] = {1, 0, -1,  0};

int main(){
	int m, n, x, y, ori, lost, i, rx, ry;
	int grid[51][51];
	char line[102], ch;
	memset(grid, 0, sizeof(int)*51*51);
	scanf("%d %d\n", &m, &n);
	while(scanf("%d %d %c\n", &x, &y, &ch)!=EOF){
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
					ori = (ori + 1) % 4;
					break;
				case 'L':
					ori = (ori + 3) % 4;
					break;
				case 'F':
					rx = x + dir_x[ori];
					ry = y + dir_y[ori];
					if(rx > m || ry > n || rx < 0 || ry < 0){
						if(grid[y][x]==0){
							grid[y][x] = 1;
							lost = 1;
						}
					}else{
						x = rx;
						y = ry;
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
		printf("\n");
	}
	return 0;
}
