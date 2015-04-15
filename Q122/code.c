/*
	Date: 2015.4.15
	Author: Wei-Teng, Lo
	Description:
		To handle the input, see (int,string) as a token.
		Before getting a empty token (), continue to construct the binary tree.

		To judge if the tree is complete, while building sequence with BFS, the program 
		would count how many nodes added into the sequence. If the program reaches a 
		node whose value is -1, the program would stop the BFS. If the counting number 
		isn't equal to the number of nodes added into tree, the program would judge the 
		tree is incomplete. Otherwise, the tree is complete.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {EMPTY, NODE, END} Type;

typedef struct Token{
	int value, length;
	char path[256]; 
	Type type;
}Token;

typedef struct Node{
	int value;
	struct Node *left, *right;
}Node;

typedef struct Sequence{
	int size;
	Node list[256];
}Sequence;

Token getNextToken();

void Release_Tree(Node*);
void Build_Sequence(Sequence*, Node*);

int main(){
	int count, i;
	Node *root, *ptr;
	Sequence db;
	Token tok;
	/*
		Initialization
	*/
	root = NULL;
	db.size = 0;
	count = 0;
	while(1==1){
		tok = getNextToken();
		if(tok.type==END){
			break;
		}else if(tok.type==EMPTY){
			/*
				Check the tree.
			*/
			if(root!=NULL)	Build_Sequence(&db, root);
			/*
				Print out the tree.
			*/
			if(db.size==count){
				for(i=0; i<db.size; i++){
					printf("%d", db.list[i].value);
					if(i!=db.size-1){
						printf(" ");
					}
				}
				printf("\n");
			}else{
				printf("not complete\n");
			}
			/*
				Reset the tree.
			*/
			Release_Tree(root);
			root = NULL;
			db.size = 0;
			count = 0;
		}else{
			/*
				Construct the tree.
			*/
			if(root==NULL){
				root = (Node*) malloc(sizeof(Node));
				root->left = NULL;
				root->right = NULL;
				root->value = -1;
			}
			ptr = root;
			i = 0;
			while(tok.path[i]!='\0'){
				if(tok.path[i]=='L'){
					if(ptr->left==NULL){
						ptr->left = (Node*) malloc(sizeof(Node));
						ptr->left->left = NULL;
						ptr->left->right = NULL;
						ptr->left->value = -1;
					}
					ptr = ptr->left;
				}else{
					if(ptr->right==NULL){
						ptr->right = (Node*) malloc(sizeof(Node));
						ptr->right->left = NULL;
						ptr->right->right = NULL;
						ptr->right->value = -1;
					}
					ptr = ptr->right;
				}
				i++;
			}
			ptr->value = tok.value;
			count++;
		}
	}
	return 0;
}

Token getNextToken(){
	int accept = 0, flag = 0;
	Token ret;
	char ch;
	/*
		DEFAULT TYPE: END.
		If program doesn't get anything from the loop,
		it would be the signal telling the caller there is nothing left.
	*/
	ret.type = END;
	ret.value = 0;
	ret.length = 0;
	while(scanf("%c", &ch)==1&&!accept){
		switch(ch){
			case '(':
				/*
					SIGNAL-> START TO ACCEPT AN INTEGER.
				*/
				break;
			case ')':
				/*
					SIGNAL-> STRING AND TOKEN ACCEPTED.
				*/
				if(flag==0){
					ret.type = EMPTY;
				}else{
					ret.path[ret.length] = '\0';
					ret.type = NODE;
				}
				accept = 1;
				break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9':
				ret.value = ret.value*10 + ch - '0';
				break;
			case ',':
				flag = 1;
				/*
					SIGNAL-> INTEGER ACCEPTED.
				*/
				break;
			case ' ': case '\n':
				/*
					SHOULD BE IGNORED.
				*/
				break;
			case 'L': case 'R':
				if(ret.length<=254){
					ret.path[ret.length++] = ch;
				}
				break;
			default:
				break;
		}
	}
	return ret;
}

void Release_Tree(Node *ptr){
	if(ptr->left!=NULL)	Release_Tree(ptr->left);
	if(ptr->right!=NULL)	Release_Tree(ptr->right);
	free(ptr);
}

void Build_Sequence(Sequence *db, Node *root){
	int i;
	Node *ptr;
	if(root->value!=-1){
		db->list[db->size++] = *root;
		for(i=0; i<db->size&&db->list[i].value!=-1; i++){
			if(db->list[i].left!=NULL){
				ptr = db->list[i].left;
				db->list[db->size++] = *ptr;
			}
			if(db->list[i].right!=NULL){
				ptr = db->list[i].right;
				db->list[db->size++] = *ptr;
			}
		}
	}
}
