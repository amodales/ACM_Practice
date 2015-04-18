#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char x;
	int list[19];
	int size;
}Node;

Node word[20];
int check[20];
int size=0;

int Find_Index(char);
int Partition(int, int);

void Quicksort(int, int);
void construct_order(int, char[]);
void modify_list(int, int);

int main(){
	int phase = 0, i, j, pair, first_index, sec_index, count = 0;
	char line[200];
	while(fgets(line, 200, stdin)!=NULL){
		if(phase==0){
			i = 0;
			while(line[i]!='\n'&&line[i]!='\0'){
				if(line[i]!=' '){
					word[size].x = line[i];
					word[size++].size = 0;
				}
				i++;
			}
			Quicksort(0, size-1);
			phase = 1;
		}else{
			/*
				Receive constraint.
			*/
			i = 0;
			pair = 0;
			while(line[i]!='\n'&&line[i]!='\0'){
				if(line[i]!=' '){
					if(pair==0){
						first_index = Find_Index(line[i]);
					}else{
						sec_index = Find_Index(line[i]);
						word[sec_index].list[word[sec_index].size++] = first_index;
					}
					pair = (pair+1)%2;
				}
				i++;
			}
			/*
				Little modify constraint list.
			*/
			for(i=0; i<size; i++){
				modify_list(i, i);
			}
			/*
				Construct ordering.
			*/
			memset(check, 0, sizeof(check));
			memset(line, 0, sizeof(line));
			if(count!=0)	printf("\n");
			construct_order(0, line);
			/*
				Reset parameters.
			*/
			count++;
			phase = 0;
			size = 0;
		}
	}
	return 0;
}

int Find_Index(char ch){
	int i;
	for(i=0; i<size; i++){
		if(word[i].x==ch)	return i;
	}
	return -1;
}

void modify_list(int parent, int now){
	int i, flag=1;
	for(i=0; i<word[now].size; i++){
		modify_list(parent, word[now].list[i]);
	}
	if(parent!=now){
		for(i=0; i<word[parent].size&&flag; i++){
			if(now==word[parent].list[i])	flag = 0;
		}
		if(flag){
			word[parent].list[word[parent].size++] = now;
		}
	}
}

void construct_order(int n, char line[]){
	int i, j, flag;
	if(n!=size){
		for(i=0; i<size; i++){
			if(check[i]==0){
				flag = 1;
				for(j=0; j<word[i].size&&flag; j++){
					if(check[word[i].list[j]]==0)	flag = 0;
				}
				if(flag){
					check[i] = 1;
					line[n] = word[i].x;
					construct_order(n+1, line);
					check[i] = 0;
				}
			}
		}
	}else{
		line[n] = '\0';
		printf("%s\n", line);
	}
}

void Quicksort(int left, int right){
	int p;
	if(left<right){
		p = Partition(left, right);
		Quicksort(left, p-1);
		Quicksort(p+1, right);
	}
}

int Partition(int left, int right){
	Node temp;
	int i = left - 1, j;
	for(j=left; j<right; j++){
		if(word[j].x<=word[right].x){
			i++;
			temp = word[i];
			word[i] = word[j];
			word[j] = temp;
		}
	}
	i++;
	temp = word[i];
	word[i] = word[right];
	word[right] = temp;
	return i;
}
