#include <stdio.h>
#include <stdlib.h>

char line[81];
int count;

int Generator(int, int, int);
int is_hard(int, int);

int main(){
	int n, l, i, j, found;
	while(scanf("%d %d", &n, &l)==2){
		if(n==0&&l==0)	break;
		count = 0;
		for(i=1; i<=l; i++){
			line[0] = i;
			count++;
			if(count!=n){
				found = Generator(n, 1, l);
				if(found)	break;
			}else{
				printf("%c\n1\n", line[0]+'A'-1);
				break;
			}
		}
	}
	return 0;
}

int Generator(int rank, int length, int alpha){
	int i, j, found;
	for(i=1; i<=alpha; i++){
		if(line[length-1]!=i){
			if(is_hard(i, length)){
				count++;
				if(count!=rank){
					found = Generator(rank, length+1, alpha);
					if(found)	return 1;
				}else{
					line[length+1] = '\0';
					j = 0;
					while(line[j]!='\0'){
						if(j>0&&j%4==0){
							if(j%64!=0){
								printf(" ");
							}else{
								printf("\n");
							}
						}
						printf("%c", line[j]+'A'-1);
						j++;
					}
					printf("\n%d\n", j);
					return 1;
				}
			}
		}
	}
	return 0;
}

int is_hard(int ch, int length){
	int i, j, check;
	line[length] = ch;
	for(i=1; length-2*i-1>=0; i++){
		/*
			length-i ~ length
			length-2i-1 ~ length-i-1
		*/
		check = 1;
		for(j=0; j<=i; j++){
			if(line[length-j]!=line[length-i-1-j]){
				check = 0;	
			}
		}
		if(check){
			return 0;
		}
	}
	return 1;
}
