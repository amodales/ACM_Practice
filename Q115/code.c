#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	name : 30 characters + 1 null character.
	parent : saving parent's index.
*/
typedef struct Node{
	char name[31];
	int parent;
}Node;

void Parse(char [], char []);
void Print_Relation(int, int);
int Add_Person(char []);

Node people[300];
int size = 0;

int main(){
	/*
		Maximum : Receive 60 characters (for two names) + 1 space character +  
		1 newline character + 1 null character = 63
	*/
	int accept = 0, index_first, index_second, m, n, l, r;
	char first[31], second[31], c;
	/*
		Process of building a tree.
	*/
	while(!accept){
		Parse(first, second);
		if(strcmp("no.child", first)!=0&&strcmp("no.parent", second)!=0){
			index_first = Add_Person(first);
			index_second = Add_Person(second);
			people[index_first].parent = index_second;
		}else{
			accept = 1;
		}
	}
	/*
		Receiving queries and giving answers.
	*/
	while(!feof(stdin)){
		Parse(first, second);
		index_first = Add_Person(first);
		index_second = Add_Person(second);
		m = 0;
		l = index_first;
		while(l!=-1){
			n = 0;
			r = index_second;
			while(r!=-1){
				if(r==l)	break;
				n++;
				r = people[r].parent;
			}
			if(r==l)	break;
			m++;
			l = people[l].parent;
		}
		if(l!=-1&&r!=-1){
			Print_Relation(m, n);
		}else{
			printf("no relation\n");
		}
		c = fgetc(stdin);
		if(c!=EOF)	ungetc(c, stdin);
	}
	return 0;
}

void Parse(char first[], char second[]){
	char c;
	int i = 0;
	c = fgetc(stdin);
	while(c=='.'||c>='a'&&c<='z'||c=='-'){
		first[i] = c;
		i++;
		c = fgetc(stdin);
	}
	first[i] = '\0';
	i = 0;
	c = fgetc(stdin);
	while(c=='.'||c>='a'&&c<='z'||c=='-'){
		second[i] = c;
		i++;
		c = fgetc(stdin);
	}
	second[i] = '\0';
}

/*
	Based on the values |m-n|, m, and n, print out the relation between two people.
*/
void Print_Relation(int m, int n){
	int i, min, abs;
	if(m==0&&n!=0){
		for(i=2; i<n; i++)	printf("great ");
		if(n>=2)	printf("grand ");
		printf("parent\n");
	}else if(n==0&&m!=0){
		for(i=2; i<m; i++)	printf("great ");
		if(m>=2)	printf("grand ");
		printf("child\n");
	}else if(m==0&&n==0){
		printf("sibling\n");
	}else{
		min = (m>n)? n: m;
		abs = (m>n)? m-n: n-m;
		min--;
		(min==0&&abs==0)?	printf("sibling"): printf("%d cousin", min);
		if(abs!=0){
			printf(" removed %d", abs);
		}
		printf("\n");
	}
}

/*
	Add a person into tree, and return its index.
	However, if the person has existed in the tree already, just return its index.
*/
int Add_Person(char name[]){
	int i;
	for(i=0; i<size; i++){
		if(strcmp(name, people[i].name)==0){
			return i;
		}
	}
	i = 0;
	while(name[i]!='\0'){
		people[size].name[i] = name[i];
		i++;
	}
	people[size].name[i] = '\0';
	people[size].parent = -1;
	return size++;
}
