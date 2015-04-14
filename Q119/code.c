#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person{
	char name[13];
	int balance;
}Person;

typedef struct Data{
	Person people[10];
	int size;
}Data;

int Find_Index(Data, char []);

int main(){
	int n, i, j, amount, div, giver_index, rec_index, c=0;
	char ch, giver_name[13], rec_name[13];
	Data database;
	while(scanf("%d\n", &n)!=EOF){
		if(c!=0)	printf("\n");
		memset(database.people, 0, sizeof(database.people));
		database.size = n;
		for(i=0; i<n; i++){
			scanf("%s", database.people[i].name);
		}
		for(i=0; i<n; i++){
			scanf("%s %d %d ", giver_name, &amount, &div);
			giver_index = Find_Index(database, giver_name);
			if(div!=0){
				for(j=0; j<div; j++){
					scanf("%s", rec_name);
					rec_index = Find_Index(database, rec_name);
					database.people[giver_index].balance -= amount/div;
					database.people[rec_index].balance += amount/div;
				}
			}
		}
		for(i=0; i<n; i++){
			printf("%s %d\n", database.people[i].name, database.people[i].balance);
		}
		c++;
	}
	return 0;
}

int Find_Index(Data database, char name[]){
	int i;
	for(i=0; i<database.size; i++){
		if(strcmp(database.people[i].name, name)==0){
			return i;
		}
	}
	return -1;
}
