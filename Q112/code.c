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

typedef struct Node{
	int number;
	struct Node *left, *right;
}Node;

typedef struct Token{
	int number;
	Type type;
}Token;

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
	Functions of Node(Tree)
*/
void Release_Tree(Node *ptr){
	if(ptr!=NULL){
		Release_Tree(ptr->left);
		Release_Tree(ptr->right);
		free(ptr);
	}
}

Node* BuildUpTree(Token Tok){
	Node *ptr;
	switch(Tok.type){
		case INT:
			ptr = (Node*) malloc( sizeof(Node) );
			ptr->number = Tok.number;
			getNextToken();
			ptr->left = BuildUpTree(getNextToken());
			getNextToken();
			ptr->right = BuildUpTree(getNextToken());
			getNextToken();
			return ptr;
			break;
		case PAR_R:
			return NULL;
			break;
		default:
			printf("Are you fucking kidding me?\n");
			break;
	}
}

void SHOW_TREE(Node *ptr){
	if(ptr!=NULL){
		printf("%d ", ptr->number);
		SHOW_TREE(ptr->left);
		SHOW_TREE(ptr->right);
	}
}

int search(Node *ptr, int num, int sum){
	if(ptr==NULL)	return 0;
	if(ptr->left==NULL&&ptr->right==NULL){
		return ((ptr->number+sum)==num);
	}
	if(search(ptr->left, num, sum+ptr->number))	return 1;
	if(search(ptr->right, num, sum+ptr->number))	return 1;
	return 0;
}

int main(){
	int num, accept, pair;
	Token Tok;
	Node *root;
	while(scanf("%d", &num)==1){
		root = NULL;
		getNextToken();
		root = BuildUpTree(getNextToken());
		(search(root, num, 0)==1)? 
			printf("yes\n"):
			printf("no\n");
		Release_Tree(root);
	}
	return 0;
}
