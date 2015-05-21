#include <stdio.h>
#include <stdlib.h>

typedef struct Region{
	int x1, y1;
	int x2, y2;
}Region;

typedef struct Icon{
	int x, y;
	int mark;
}Icon;

int Is_In_Region(Region [], int, int, int);

void Show_Nearest_Icon(Icon [], int, int, int);
void Remove_Icon_In_Region(Region [], int, Icon [], int);

int main(){
	Region regs[25];
	Icon ics[50];
	char ch;
	int size_ics = 0, size_regs = 0;
	int x1, y1, x2, y2, index, ph = 0;
	while(scanf("%c", &ch)!=EOF&&ch!='#'){
		switch(ch){
			case 'I':
				scanf("%d %d\n", &x1, &y1);
				ics[size_ics].x = x1;
				ics[size_ics].y = y1;
				ics[size_ics].mark = 1;
				size_ics++;
				break;
			case 'R':
				scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
				regs[size_regs].x1 = x1;
				regs[size_regs].y1 = y1;
				regs[size_regs].x2 = x2;
				regs[size_regs].y2 = y2;
				size_regs++;
				break;
			case 'M':
				if(ph==0){
					Remove_Icon_In_Region(regs, size_regs, ics, size_ics);
					ph = 1;
				}
				scanf("%d %d\n", &x1, &y1);
				index = Is_In_Region(regs, size_regs, x1, y1);
				if(index!=-1){
					printf("%c\n", 'A'+index);
				}else{
					Show_Nearest_Icon(ics, size_ics, x1, y1);
				}
				break;
		}
	}
	return 0;
}

int Is_In_Region(Region regs[], int size, int x, int y){
	int i, ret = -1;
	for(i=0; i<size; i++){
		if(regs[i].x1<=x&&x<=regs[i].x2&&regs[i].y1<=y&&y<=regs[i].y2){
			ret = i;
		}
	}
	return ret;
}

void Show_Nearest_Icon(Icon ics[], int size, int x, int y){
	int index[50];
	int count, min = 99999999;
	int i, dis;
	for(i=0; i<size; i++){
		if(!ics[i].mark)	continue;
		dis = (x - ics[i].x)*(x - ics[i].x) + (y - ics[i].y)*(y- ics[i].y);
		if(min>dis){
			min = dis;
			index[0] = i;
			count = 1;
		}else if(min==dis){
			index[count++] = i;
		}else{
			continue;
		}
	}
	for(i=0; i<count; i++){
		printf("%3d", index[i]+1);
	}
	printf("\n");
}

void Remove_Icon_In_Region(Region regs[], int size_regs, Icon ics[], int size_ics){
	int i, index;
	for(i=0; i<size_ics; i++){
		if(Is_In_Region(regs, size_regs, ics[i].x, ics[i].y)!=-1){
			ics[i].mark = 0;
		}
	}
}
