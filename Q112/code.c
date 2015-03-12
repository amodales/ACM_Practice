/*
	Author: Wei-Teng, Lo
	Date: 2015.3.12
	Description: 
		All parsing procedure is based on the test data following the rules,
	which means that if there is any grammar error, this program would crash.
*/
#include <stdio.h>
#include <stdlib.h>

/*
	Customized Types
*/
typedef enum {PAR_L, INT, PAR_R} Type;

typedef struct Token{
	int number;
	Type type;
}Token;

typedef struct Vector{
	int *list;
	int size, capacity;
}Vector;

/*
	Global Variable
*/
Vector Record;

/*
	Function of Token
*/
Token getNextToken(){
	Token Tok;
	int number = 0, digit = 0, accept = 0, sign = 1;
	char ch;
	while(!accept){
		ch = fgetc(stdin);
		switch(ch){
			case '(':
				if(digit==0){
					Tok.type = PAR_L;
				}else{
					ungetc(ch, stdin);
					Tok.type = INT;
					Tok.number = number*sign;
				}
				accept = 1;
				break;
			case ')':
				Tok.type = PAR_R;
				accept = 1;
				break;
			case '-':
				sign = -1;
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				number = number * 10 + (ch - '0');
				digit++;
				break;
			default:
				break;
		}
	}
	return Tok;
}

/*
	Function of Vector
*/
void Initialize_Vector(){
	Record.capacity = 1000;
	Record.list = (int*) calloc( 1000, sizeof(int) );
	Record.size = 0;
}

void Push(int number){
	int i, *ptr;
	if(Record.size+1>=Record.capacity){
		Record.capacity = Record.capacity * 1.5;
		ptr = (int*) calloc( Record.capacity, sizeof(int));
		for(i=0; i<Record.size; i++){
			ptr[i] = Record.list[i];
		}
		free(Record.list);
		Record.list = ptr;
	}
	Record.list[Record.size++] = number;
}

int Search_Vector(int number){
	int i;
	for(i=0; i<Record.size; i++){
		if(Record.list[i]==number)	return 1;
	}
	return 0;
}

void Release_Vector(){
	free(Record.list);
}

/*
	Functions of Node(Tree)
*/
int BuildUpTree(Token Tok, int sum){
	int left, right;
	switch(Tok.type){
		case INT:
			getNextToken();
			left = BuildUpTree(getNextToken(), sum+Tok.number);
			getNextToken();
			right = BuildUpTree(getNextToken(), sum+Tok.number);
			getNextToken();
			if(left==0&&right==0){
				Push(sum+Tok.number);
			}
			return 1;
			break;
		case PAR_R:
			return 0;
			break;
		default:
			printf("Are you fucking kidding me?\n");
			break;
	}
}

int main(){
	int num;
	Token Tok;
	while(scanf("%d", &num)==1){
		Initialize_Vector();
		getNextToken();
		BuildUpTree(getNextToken(), 0);
		(Search_Vector(num)==1)? 
			printf("yes\n"):
			printf("no\n");
		Release_Vector();
	}
	return 0;
}
