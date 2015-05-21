#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Rotation : 
		x' = -y + n + 1;
		y' = x;
*/

typedef struct Point{
	int x, y;
}Point;

void Quicksort(Point ps[], int left, int right){
	int m;
	if(left<right){
		m = Partition(ps, left, right);
		Quicksort(ps, left, m-1);
		Quicksort(ps, m+1, right);
	}
}

int Partition(Point ps[], int left, int right){
	Point temp;
	int i = left - 1, j;
	for(j=left; j<right; j++){
		if(Compare_Point(ps[j], ps[right])<0){
			i++;
			temp = ps[j];
			ps[j] = ps[i];
			ps[i] = temp;
		}
	}
	i++;
	temp = ps[right];
	ps[right] = ps[i];
	ps[i] = temp;
	return i;
}

int Compare_Point(Point a, Point b){
	if(a.x > b.x){
		return 1;
	}else if(a.x < b.x){
		return -1;
	}else{
		if(a.y > b.y){
			return 1;
		}else if(a.y < b.y){
			return -1;
		}else{
			return 0;
		}
	}
}

int main(){
	Point record[250][101], copy[250], entry;
	int n, i, j, k, size[101], check, dx, dy;
	char mov;
	while(scanf("%d", &n)==1&&n!=0){
		/*
			Receive input data, and calculate.
		*/
		memset(size, 0, sizeof(size));
		for(i=1; i<=2*n; i++){
			scanf("%d %d %c\n", &entry.x, &entry.y, &mov);
			switch(mov){
				case '+':
					/*
						Insert point in order.
					*/
					for(j=0; j<size[i-1]; j++){
						if(Compare_Point(record[j][i-1], entry)<0){
							record[j][i] = record[j][i-1];
						}else{
							break;
						}
					}
					record[j][i] = entry;
					while(j<size[i-1]){
						record[j+1][i] = record[j][i-1];
						j++;
					}
					size[i] = j+1;
					break;
				case '-':
					for(j=0, k=0; j<size[i-1]; j++){
						if(Compare_Point(record[j][i-1], entry)!=0){
							record[k++][i] = record[j][i-1];
						}
					}
					size[i] = k;
					break;
			}
			/*
				Check if the game ends. 
			*/
			for(j=0, check=0; j<i&&!check; j++){
				if(size[j]!=size[i])	continue;
				/*
					Make a copy
				*/
				for(k=0; k<size[j]; k++){
					copy[k] = record[k][j];
				}
				/*
					No Rotation
				*/
				check = 1;
				for(k=0; k<size[j]&&check; k++){
					if(Compare_Point(copy[k], record[k][i])!=0){
						check = 0;
					}
				}
				if(check==1)	break;
				/*
					Rotation 90 degree.
				*/
				for(k=0; k<size[j]; k++){
					dx = copy[k].x;
					dy = copy[k].y;
					copy[k].x = -1*dy + n + 1;
					copy[k].y = dx;
				}
				check = 1;
				Quicksort(copy, 0, size[j]-1);
				for(k=0; k<size[j]&&check; k++){
					if(Compare_Point(copy[k], record[k][i])!=0){
						check = 0;
					}
				}
				if(check==1)	break;	
				/*
					Rotation 180 degree.
				*/
				for(k=0; k<size[j]; k++){
					dx = copy[k].x;
					dy = copy[k].y;
					copy[k].x = -1*dy + n + 1;
					copy[k].y = dx;
				}
				check = 1;
				Quicksort(copy, 0, size[j]-1);
				for(k=0; k<size[j]&&check; k++){
					if(Compare_Point(copy[k], record[k][i])!=0){
						check = 0;
					}
				}
				if(check==1)	break;	
				/*
					Rotation 270 degree.
				*/
				for(k=0; k<size[j]; k++){
					dx = copy[k].x;
					dy = copy[k].y;
					copy[k].x = -1*dy + n + 1;
					copy[k].y = dx;
				}
				check = 1;
				Quicksort(copy, 0, size[j]-1);
				for(k=0; k<size[j]&&check; k++){
					if(Compare_Point(copy[k], record[k][i])!=0){
						check = 0;
					}
				}
			}
			if(check==1)	break;
		}
		/*
			To eliminate the remaining input data.
		*/
		if(check){
			j = (i%2==0)? 1: 2;
			printf("Player %d wins on move %d\n", j, i++);
			while(i<=2*n){
				scanf("%d %d %c\n", &entry.x, &entry.y, &mov);
				i++;
			}
		}else{
			printf("Draw\n");
		}
	}
	return 0;
}
