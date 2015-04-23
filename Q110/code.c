#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Print_If_ElseIf_Else(int, int, int []);
void Print_Line(int);

int main(){
	int m, n, i, count=0, line[8];
	scanf("%d", &m);
	while(count<m){
		if(count!=0)	printf("\n");
		scanf("%d", &n);
		/*
			HEAD
		*/
		printf("program sort(input,output);\n");
		printf("var\n");
		Print_Line(n);
		printf(" : integer;\n");
		printf("begin\n");
		printf("  readln(");
		Print_Line(n);
		printf(");\n");
		/*
			BODY
		*/
		if(n>1){
			line[0] = 0;
			Print_If_ElseIf_Else(2, n, line);
		}else{
			printf("  writeln(a)\n");
		}
		/*
			FOOT
		*/
		printf("end.\n");
		count++;
	}
	return 0;
}

void Print_If_ElseIf_Else(int num, int max, int perm[]){
	int i, j, temp, line[8];
	/*
		Make a copy of perm.
	*/
	for(i=0; i<num-1; i++){
		line[i] = perm[i];
	}
	line[num-1] = num-1;
	for(i=num-1; i>=0; i--){
		for(j=0; j<(num-1)*2; j++)	printf(" ");
		if(i==num-1){
			printf("if %c < %c then\n", line[i-1]+'a', num+'a'-1);
		}else if(i>0&&i<num-1){
			printf("else if %c < %c then\n", line[i-1]+'a', num+'a'-1);
		}else{
			printf("else\n");
		}
		if(num<max){
			Print_If_ElseIf_Else(num+1, max, line);
		}else{
			for(j=0; j<num*2; j++)	printf(" ");
			printf("writeln(");
			for(j=0; j<max; j++){
				printf("%c", line[j]+'a');
				if(j!=max-1)	printf(",");
			}
			printf(")\n");
		}
		if(i!=0){
			temp = line[i];
			line[i] = line[i-1];
			line[i-1] = temp;
		}
	}
}

void Print_Line(int n){
	int i;
	for(i=0; i<n; i++){
		printf("%c", i+'a');
		if(i!=n-1)	printf(",");
	}
}
