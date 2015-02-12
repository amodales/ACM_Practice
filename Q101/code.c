#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	int num;
	struct Node *next, *last;
}Node;

Node *head, *tail;

int parse(char* buf, int *obj, int *tar, int limit);
int FindIndexWithNumber(int num, int limit);
Node* FindNodeWithNumber(int num, int limit);
void show(int n);

int main(){
	char buf[256];
	Node *ptr1, *ptr2, *ptr3;
	int i, n, obj, tar, opt, done = 0;
	scanf("%d\n", &n);
	head = (Node *) malloc(sizeof(Node)*n);
	tail = (Node *) malloc(sizeof(Node)*n);
	for(i=0; i<n; i++){
		ptr1 = (Node *) malloc(sizeof(Node));
		ptr1->num = i;
		ptr1->last = &head[i];
		ptr1->next = &tail[i];
		head[i].next = ptr1;
		head[i].last = NULL;
		tail[i].last = ptr1;
		tail[i].next = NULL;
	}
	while(done!=1){
		memset(buf, 0 ,256);
		fgets(buf, 256, stdin);
		opt = parse(buf, &obj, &tar, n);
		switch(opt){
			case 0:
				done = 1;
				break;
			case 1:
				ptr1 = FindNodeWithNumber(obj, n);
				obj = FindIndexWithNumber(obj, n);
				ptr2 = FindNodeWithNumber(tar, n);
				tar = FindIndexWithNumber(tar, n);
				if(obj!=tar){
					ptr1->last->next = ptr1->next;
					ptr1->next->last = ptr1->last;
					ptr3 = ptr1->next;
					ptr1->last = ptr2;
					ptr1->next = ptr2->next;
					ptr2->next->last = ptr1;
					ptr2->next = ptr1;
					ptr2 = ptr1->next;
					while(ptr2!=&tail[tar]){
						ptr1 = ptr2;
						ptr2 = ptr2->next;
						ptr1->last->next = ptr2;
						ptr2->last = ptr1->last;
						tail[ptr1->num].last->next = ptr1;
						ptr1->next = &tail[ptr1->num];
						ptr1->last = tail[ptr1->num].last;
						tail[ptr1->num].last = ptr1;
					}
					while(ptr3!=&tail[obj]){
						ptr1 = ptr3;
						ptr3 = ptr3->next;
						ptr1->last->next = ptr3;
						ptr3->last = ptr1->last;
						tail[ptr1->num].last->next = ptr1;
						ptr1->next = &tail[ptr1->num];
						ptr1->last = tail[ptr1->num].last;
						tail[ptr1->num].last = ptr1;
					}
				}
				break;
			case 2:
				ptr1 = FindNodeWithNumber(obj, n);
				obj = FindIndexWithNumber(obj, n);
				tar = FindIndexWithNumber(tar, n);
				if(obj!=tar){
					ptr2 = tail[tar].last;
					ptr1->last->next = ptr1->next;
					ptr1->next->last = ptr1->last;
					ptr3 = ptr1->next;
					ptr1->last = ptr2;
					ptr1->next = ptr2->next;
					ptr2->next->last = ptr1;
					ptr2->next = ptr1;
					while(ptr3!=&tail[obj]){
						ptr1 = ptr3;
						ptr3 = ptr3->next;
						ptr1->last->next = ptr3;
						ptr3->last = ptr1->last;
						tail[ptr1->num].last->next = ptr1;
						ptr1->next = &tail[ptr1->num];
						ptr1->last = tail[ptr1->num].last;
						tail[ptr1->num].last = ptr1;
					}
				}
				break;
			case 3:
				ptr1 = FindNodeWithNumber(obj, n);
				obj = FindIndexWithNumber(obj, n);
				ptr2 = FindNodeWithNumber(tar, n);
				tar = FindIndexWithNumber(tar, n);
				if(obj!=tar){
					ptr1->last->next = &tail[obj];
					ptr3 = tail[obj].last;
					tail[obj].last = ptr1->last;
					ptr1->last = ptr2;
					ptr3->next = ptr2->next;
					ptr2->next->last = ptr3;
					ptr2->next = ptr1;
					ptr3 = ptr3->next;
					while(ptr3!=&tail[tar]){
						ptr1 = ptr3;
						ptr3 = ptr3->next;
						ptr1->last->next = ptr3;
						ptr3->last = ptr1->last;
						tail[ptr1->num].last->next = ptr1;
						ptr1->next = &tail[ptr1->num];
						ptr1->last = tail[ptr1->num].last;
						tail[ptr1->num].last = ptr1;
					}
				}
				break;
			case 4:
				ptr1 = FindNodeWithNumber(obj, n);
				obj = FindIndexWithNumber(obj, n);
				tar = FindIndexWithNumber(tar, n);
				if(obj!=tar){
					ptr2 = &tail[tar];
					ptr1->last->next = &tail[obj];
					ptr3 = tail[obj].last;
					tail[obj].last = ptr1->last;
					ptr2->last->next = ptr1;
					ptr1->last = ptr2->last;
					ptr3->next = ptr2;
					ptr2->last = ptr3;
				}
				break;
			default:
				;
		}
	}
	show(n);
	for(i=0; i<n; i++){
		ptr1 = head[i].next;
		while(ptr1!=&tail[i]){
			ptr2 = ptr1;
			ptr1 = ptr1->next;
			free(ptr2);
		}
	}
	free(head);
	free(tail);
	return 0;
}

void show(int n){
	int i;
	Node *ptr;
	for(i=0; i<n; i++){
		ptr = head[i].next;
		printf("%d:", i);
		while(ptr!=&tail[i]){
			printf(" %d", ptr->num);
			ptr = ptr->next;
		}
		printf("\n");
	}
}

int FindIndexWithNumber(int num, int limit){
	int i;
	Node *ptr;
	if(num<0||num>=limit)	return -1;
	for(i=0; i<limit; i++){
		ptr = head[i].next;
		while(ptr!=&tail[i]){
			if(ptr->num==num)	return i;
			ptr = ptr->next;
		}
	}
}

Node* FindNodeWithNumber(int num, int limit){
	int i;
	Node *ptr;
	if(num<0||num>=limit)	return NULL;
	for(i=0; i<limit; i++){
		ptr = head[i].next;
		while(ptr!=&tail[i]){
			if(ptr->num==num)	return ptr;
			ptr = ptr->next;
		}
	}
}

int parse(char* buf, int *obj, int *tar, int limit){
	char *seg1, *seg2, *seg3, *seg4;
	int ret = 5;
	seg1 = strtok(buf, " \n");
	seg2 = strtok(NULL, " \n");
	seg3 = strtok(NULL, " \n");
	seg4 = strtok(NULL, " \n");
	if(strcmp(seg1, "quit")==0&&seg2==seg3==seg4==NULL){
		ret = 0;
	}else{ 
		if(seg2!=NULL&&seg3!=NULL&&seg4!=NULL){
			*obj = atoi(seg2);
			*tar = atoi(seg4);
			if(*obj!=*tar&&*obj>=0&&*obj<limit&&*tar>=0&&*tar<limit){
				if(strcmp(seg1, "move")==0){
					if(strcmp(seg3, "onto")==0){
						ret = 1;
					}
					if(strcmp(seg3, "over")==0){
						ret = 2;
					}
				}
				if(strcmp(seg1, "pile")==0){
					if(strcmp(seg3, "onto")==0){
						ret = 3;
					}
					if(strcmp(seg3, "over")==0){
						ret = 4;
					}
				}
			}
		}
	}
	return ret;
}
