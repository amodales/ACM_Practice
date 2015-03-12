#include <stdio.h>
#include <stdlib.h>

typedef enum {PAR_L, PAR_R, NUM, EMPTY_TREE, TREE, FIN} Type;

typedef struct Node{
	int number;
	struct Node *left, *right;
}Node;

typedef struct Token{
	Type type;
	int num;
	Node *dot;
}Token;

typedef struct Stack{
	Token *con;
	int *state;
	int size;
	int top;
}Stack;

void Free_Tree(Node *);
void state_0(Token *);
void state_1(Token *);
void state_2();
void state_3(Token *);
void state_4(Token *);
void state_5(Token *);
void state_6();
void state_7();
void GoToState(Token*, int);

Stack P_Stack;

int search(Node*, int, int);

void Initial_Stack(){
	P_Stack.size = 100;
	P_Stack.top = -1;
	P_Stack.con = (Token*) malloc( P_Stack.size*sizeof(Token) );
	P_Stack.state = (int*) malloc( P_Stack.size*sizeof(int) );	
}

void Release_Stack(){
	free(P_Stack.con);
	free(P_Stack.state);
}

void Push(Token Tok, int state){
	Token *p;
	int *n, i;
	if(P_Stack.top+1>=P_Stack.size){
		P_Stack.size = P_Stack.size * 1.5;
		p = (Token*) malloc( P_Stack.size*sizeof(Token) );
		n = (int*) malloc( P_Stack.size*sizeof(int) );
		for(i=0; i<=P_Stack.top; i++){
			p[i] = P_Stack.con[i];
			n[i] = P_Stack.state[i];
		}
		free(P_Stack.con);
		free(P_Stack.state);
		P_Stack.con = p;
		P_Stack.state = n;
	}
	P_Stack.con[++P_Stack.top] = Tok;
	P_Stack.state[P_Stack.top] = state;
}

int is_empty(){
	return P_Stack.top==-1;
}

void Pop(Token *Tok, int *state){
	if(is_empty()==0){
		*Tok = P_Stack.con[P_Stack.top];
		*state = P_Stack.state[P_Stack.top--];
	}
}

void Top(Token *Tok, int *state){
	if(is_empty()==0){
		*Tok = P_Stack.con[P_Stack.top];
		*state = P_Stack.state[P_Stack.top];
	}
}

Token *lookahead;

Token peek(){
	int accept, ch, digit, number, sign;
	accept = 0;
	if(lookahead==NULL){
		digit = 0;
		number = 0;
		sign = 1;
		while(!accept){
			ch = fgetc(stdin);
			switch(ch){
				case '(':
					lookahead = (Token*) malloc( sizeof(Token) );
					if(digit==0){
						lookahead->type = PAR_L;
					}else{
						lookahead->type = NUM;
						lookahead->num = sign*number;
						ungetc(ch, stdin);
					}
					accept = 1;
					break;
				case ')':
					lookahead = (Token*) malloc( sizeof(Token) );
					lookahead->type = PAR_R;
					accept = 1;
					break;
				case '0': case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9':
					digit++;
					number = number*10 + (ch - '0');
					break;
				case '-':
					sign = -1;
					break;
				default :
					break;
			}
		}
	}
	return *lookahead;
}

Token* getNextToken(){
	Token *ret;
	ret = (Token*) malloc( sizeof(Token) );
	*ret = peek();
	free(lookahead);
	lookahead = NULL;
	return ret;
}

int main(){
	Token p;
	int num, accept, l;
	while(scanf("%d", &num)==1){
		Initial_Stack();
		lookahead = NULL;
		accept = 0;
		state_0(getNextToken());
		Top(&p, &l);
		if(p.type==FIN){
			switch(search(p.dot, num, 0)){
				case 0:
					printf("no\n");
					break;
				case 1:
					printf("yes\n");
					break;
				default:
					break;
			}
			Free_Tree(p.dot);
		}
		Release_Stack();
	}
	return 0;
}

void GoToState(Token *Tok, int state){
	switch(state){
		case 0: state_0(Tok); break;
		case 1: state_1(Tok); break;
		case 3: state_3(Tok); break;
		case 4: state_4(Tok); break;
		case 5: state_5(Tok); break;
		case 2: case 6: case 7:
			printf("Are you kidding me?????\n\n");
			break;
	}
}

void state_0(Token *Tok){
	switch(Tok->type){
		case EMPTY_TREE:
			Push(*Tok, 0);
			free(Tok);
			state_7();
			break;
		case TREE:
			/*
				push Tok into stack,
				and then parser finished.
			*/
			Tok->type = FIN;
			Push(*Tok, 0);
			free(Tok);
			break;
		case PAR_L:
			/*
				push Tok into stack,
				and then go to state_1.
			*/
			Push(*Tok, 0);
			free(Tok);
			state_1(getNextToken());
			break;
		default:
			break;
	}
}

void state_1(Token *Tok){
	switch(Tok->type){
		case PAR_R:
			/*
				push Tok into stack,
				and then go to state_2.
			*/
			Push(*Tok, 1);
			free(Tok);
			state_2();
			break;
		case NUM:
			/*
				push Tok into stack,
				and then go to state_3.
			*/
			Push(*Tok, 1);
			free(Tok);
			state_3(getNextToken());
			break;
		default:
			break;
	}
}

void state_2(){
	/*
		pop out two token from stack,
		create a new token (EMPTY_TREE),
		push it into stack,
		and then go back to 2 state before.
	*/
	Token p1, p2, *n;
	int l1, l2;
	Pop(&p1, &l1);
	Pop(&p2, &l2);
	n = (Token*) malloc( sizeof(Token) );
	n->type = EMPTY_TREE;
	n->dot = NULL;
	GoToState(n, l2);
}

void state_3(Token *Tok){
	switch(Tok->type){
		case PAR_L:
			/*
				push Tok into stack,
				and then go to state_1.
			*/
			Push(*Tok, 3);
			free(Tok);
			state_1(getNextToken());
			break;
		case EMPTY_TREE:
			Push(*Tok, 3);
			free(Tok);
			state_7();
			break;
		case TREE:
			/*
				push Tok into stack,
				and then go to state_4.
			*/
			Push(*Tok, 3);
			free(Tok);
			state_4(getNextToken());
			break;
		default:
			break;
	}
}

void state_4(Token *Tok){
	switch(Tok->type){
		case PAR_L:
			/*
				push Tok into stack,
				and then go to state_1.
			*/
			Push(*Tok, 4);
			free(Tok);
			state_1(getNextToken());
			break;
		case EMPTY_TREE:
			Push(*Tok, 4);
			free(Tok);
			state_7();
			break;
		case TREE:
			/*
				push Tok into stack,
				and tehn go to state_5.
			*/
			Push(*Tok, 4);
			free(Tok);
			state_5(getNextToken());
			break;
		default:
			break;
	}
}

void state_5(Token *Tok){
	switch(Tok->type){
		case PAR_R:
			/*
				push Tok into stack,
				and then go to state_6.
			*/
			Push(*Tok, 5);
			free(Tok);
			state_6();
			break;
		default:
			break;
	}
}

void state_6(){
	/*
		pop out 5 token,
		create a new token (TREE),
		push it into stack,
		and then go back to 5 state before.
	*/
	Token p1, p2, p3, p4, p5, *n;
	int l1, l2, l3, l4, l5;
	Pop(&p1, &l1);
	Pop(&p2, &l2);
	Pop(&p3, &l3);
	Pop(&p4, &l4);
	Pop(&p5, &l5);
	n = (Token*) malloc( sizeof(Token) );
	n->type = TREE;
	n->dot = (Node*) malloc( sizeof(Node) );
	n->dot->number = p4.num;
	n->dot->left = p3.dot;
	n->dot->right = p2.dot;
	GoToState(n, l5);
}

void state_7(){
	/*
		pop out 1 token,
		create a new token (TREE),
		push it into stack,
		and then go back to 1 state before.
	*/
	Token p, *n;
	int l;
	Pop(&p, &l);
	n = (Token*) malloc( sizeof(Token) );
	n->type = TREE;
	n->dot = NULL;
	GoToState(n, l);
}

int search(Node *ptr, int num, int sum){
	if(ptr==NULL)	return 0;
	if(ptr->left==NULL&&ptr->right==NULL){
		return (sum+ptr->number==num);
	}
	if(search(ptr->left, num, sum+ptr->number))	return 1;
	if(search(ptr->right, num, sum+ptr->number))	return 1;
	return 0;
}

void Free_Tree(Node *ptr){
	if(ptr!=NULL){
		Free_Tree(ptr->left);
		Free_Tree(ptr->right);
		free(ptr);
	}
}
