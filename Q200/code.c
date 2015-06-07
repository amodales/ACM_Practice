#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int check, size;
	char word;
	struct Node *next[30];
}Node;

void DFS(Node *, int);

char ans[30];
int size;

int main(){
	char a[25], b[25];
	Node alpha[26], *ptr;
	int i, j, left, right, count;
	while(fgets(a, 25, stdin)!=NULL){
		count = 0;
		size = 0;
		for(i=0; i<26; i++){
			alpha[i].size = 0;
			alpha[i].word = 0;
			alpha[i].check = 0;
		}
		while(fgets(b, 25, stdin)!=NULL){
			if(b[0]=='#')	break;	
			for(i=0; a[i]!='\n'&&b[i]!='\n'; i++){
				if(a[i]!=b[i])	break;
			}
			if(a[i]!='\n'&&b[i]!='\n'){
				left = a[i] - 'A';
				right = b[i] - 'A';
				alpha[left].word = a[i];
				alpha[right].word = b[i];
				for(j=0; j<alpha[left].size; j++){
					if(alpha[left].next[j]==&alpha[right]) break;
				}
				if(j==alpha[left].size)	alpha[left].next[alpha[left].size++] = &alpha[right];
			}
			/*
				Backup string b.
			*/
			for(i=0; b[i]!='\0'; i++){
				a[i] = b[i];
			}
			a[i] = '\0';
		}
		/*
			DFS & Topological Sort
		*/
		for(i=0; i<26; i++){
			if(alpha[i].word!=0){
				count++;
			}
		}
		for(i=0; i<26; i++){
			if(alpha[i].word!=0&&alpha[i].check==0){
				DFS(&alpha[i], count);
			}
		}
		ans[size] = '\0';
		printf("%s\n", ans);
	}
	return 0;
}

void DFS(Node *n, int num){
	int i;
	n->check = 1;
	for(i=0; i<n->size; i++){
		if(n->next[i]->check==0){
			DFS(n->next[i], num);
		}
	}
	ans[num-size-1] = n->word;
	size++;
}
