#include <stdio.h>
#include <stdlib.h>

void print_line(int *, int);

int main(){
	int n, i, *line;
	scanf("%d", &n);
	line = (int*) malloc( sizeof(int)*n );
	for(i=0; i<n; i++){
		line[i] = i;
	}
	/*
		HEAD
	*/
	printf("program sort(input,output);\n");
	printf("var\n");
	print_line(line, n);
	printf(" : integer;\n");
	printf("begin\n");
	printf("\treadln(");
	print_line(line, n);
	printf(");\n");
	/*
		BODY
	*/
	/*
		FOOT
	*/
	printf("end.\n");
	/*
		Release memory
	*/
	free(line);
	return 0;
}

void print_line(int *line, int n){
	int i;
	for(i=0; i<n; i++){
		printf("%c", 'a'+i);
		if(i+1!=n)	printf(",");
	}
}
