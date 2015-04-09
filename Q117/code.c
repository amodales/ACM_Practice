#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int neighbor[26];
	int degree;
	int cost[26];
	int visited;
}Node;

Node section[26];
int dist[26];

void GetInfo(char [], char *, char *, int *);
void Initialize();

int is_empty();
int GetMinVertex();

int main(){
	int i, j, sum=0, index_begin=-1, index_end;
	int length;
	char line[256], start, end;
	memset(section, 0, sizeof(Node)*26);
	memset(line, 0, 256);
	while(fgets(line, 256, stdin)!=NULL){
		if(strcmp(line, "deadend\n")!=0){
			GetInfo(line, &start, &end, &length);
			i = start - 'a';
			j = end - 'a';
			section[i].neighbor[ section[i].degree] = j;
			section[i].cost[ section[i].degree++] = length;
			section[j].neighbor[ section[j].degree] = i;
			section[j].cost[ section[j].degree++] = length;
			sum += length;
		}else{
			/*
			For checking nodes if they are connected with each other correctly.
			for(i=0; i<26; i++){
				printf("%c : %d %d\n", i+'a', section[i].visited, section[i].degree);
				for(j=0; j<section[i].degree; j++){
					printf("\t%c %d\n", section[i].neighbor[j]+'a', section[i].cost[j]);
				}
			}
			printf("\n\n");
			*/
			/*
				Find the two vertices which have odd degree.
			*/
			for(i=0; i<26; i++){
				if(section[i].degree%2==1){
					if(index_begin==-1){
						index_begin = i;
					}else{
						index_end = i;
					}
				}
			}
			/*
				If the two vertices don't exist, just print out the total sum.
				If the two vertices exist, calculate the shortest path between
				the two vertices, and then print out the total sum + the cost 
				of the shortest path between the two vertices.
			*/
			if(index_begin==-1){
				printf("%d\n", sum);		
			}else{
				memset(dist, -1, 26*sizeof(int));
				Initialize();
				dist[index_begin] = 0;
				while(!is_empty()){
					i = GetMinVertex();
					for(j=0; j<section[i].degree; j++){
						if(dist[section[i].neighbor[j]]==-1){
							dist[section[i].neighbor[j]] = dist[i] + section[i].cost[j];
						}else{
							if(dist[section[i].neighbor[j]]>dist[i]+section[i].cost[j]){
								dist[section[i].neighbor[j]] = dist[i] + section[i].cost[j];
							}
						}
					}
					section[i].visited = 1;
				}
				printf("%d\n", sum+dist[index_end]);
			}
			sum = 0;
			index_begin = -1;
			memset(section, 0, 26*sizeof(Node));
		}
		memset(line, 0, 256);
	}
	return 0;
}

void GetInfo(char line[], char *start, char *end, int *length){
	int i = 0;
	*start = line[0];
	while(line[i]!='\n'){
		i++;		
	}
	*end = line[i-1];
	*length = i;
}

void Initialize(){
	int i;
	for(i=0; i<26; i++){
		if(section[i].degree==0){
			section[i].visited = 1;
		}
	}
}

int is_empty(){
	int i;
	for(i=0; i<26; i++){
		if(section[i].visited==0){
			return 0;
		}
	}
	return 1;
}

int GetMinVertex(){
	int i, min = -1, ret = -1;
	for(i=0; i<26; i++){
		if(min==-1){
			if(section[i].visited==0&&dist[i]!=-1){
				ret = i;
				min = dist[i];
			}
		}else{
			if(section[i].visited==0&&dist[i]!=-1&&dist[i]<min){
				ret = i;
				min = dist[i];
			}
		}
	}
	return ret;
}
