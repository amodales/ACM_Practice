#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Card{
	int rank;
	char suit;
}Card;

typedef struct Stack{
	Card cards[52];
	int size;
	struct Stack *last, *next;
}Stack;

Stack head, tail;
int s_size;

void Simulation_Start();

int main(){
	Card ret;
	Stack *ptr, *back;
	int i, j;
	char line[82];
	head.last = NULL;
	head.next = &tail;
	tail.last = &head;
	tail.next = NULL;
	for(i=0; i<52; i++){
		ptr = (Stack *) malloc(sizeof(Stack));
		ptr->size = 0;
		back = tail.last;
		back->next = ptr;
		ptr->last = back;
		ptr->next = &tail;
		tail.last = ptr;
	}
	i=0;
	ptr = head.next;
	s_size = 0;
	while(fgets(line, 82, stdin)!=NULL){
		if(line[0]=='#')	break;
		while(line[i]!='\n'){
			switch(line[i]){
				case 'A':
					ret.rank = 1;
					break;
				case 'K':
					ret.rank = 13;
					break;
				case 'Q':
					ret.rank = 12;
					break;
				case 'J':
					ret.rank = 11;
					break;
				case 'T':
					ret.rank = 10;
					break;
				case '2': case '3': case '4': case '5': case '6':
				case '7': case '8': case '9':
					ret.rank = line[i] - '0';
					break;
			}
			i++;
			switch(line[i]){
				case 'C':
					ret.suit = 0;
					break;
				case 'D':
					ret.suit = 1;
					break;
				case 'H':
					ret.suit = 2;
					break;
				case 'S':
					ret.suit = 3;
					break;
			}
			i++;
			ptr->cards[ptr->size++] = ret;
			ptr = ptr->next;
			s_size++;
			if(line[i]==' ')	i++;
		}
		if(s_size==52){
			Simulation_Start();
			if(s_size!=1){
				printf("%d piles remaining:", s_size);
				ptr = head.next;
				while(ptr->size!=0){
					printf(" %d", ptr->size);
					ptr->size = 0;
					ptr = ptr->next;
				}
				printf("\n");
			}else{
				printf("1 pile remaining: %d\n", head.next->size);
				head.next->size = 0;
			}
			/*
				Reset parameter
			*/	
			s_size = 0;
			ptr = head.next;
		}
		i=0;
	}
	ptr = head.next;
	while(ptr!=&tail){
		ptr = ptr->next;
		free(ptr->last);
	}
	return 0;
}

void Simulation_Start(){
	Card ret;
	Stack *ptr, *ptr1, *ptr3;
	int i=0, j;
	ptr = head.next;
	while(i<s_size){
		ptr3 = ptr;
		j = 0;
		while(ptr3!=&head&&j<3){
			ptr3 = ptr3->last;
			j++;
		}
		ptr1 = ptr->last;
		if(ptr3!=&head&&(ptr->cards[ptr->size-1].rank==ptr3->cards[ptr3->size-1].rank
				||ptr->cards[ptr->size-1].suit==ptr3->cards[ptr3->size-1].suit)){
			ret = ptr->cards[--ptr->size];
			if(ptr->size==0){
				/*
					Remove ptr, and connect its last with its next.
				*/
				ptr->last->next = ptr->next;
				ptr->next->last = ptr->last;
				/*
					Add ptr to tail.
				*/
				ptr1 = tail.last;
				ptr->next = ptr1->next;
				ptr->last = ptr1;
				ptr1->next = ptr;
				tail.last = ptr;
				s_size--;
			}
			ptr3->cards[ptr3->size++] = ret;
			ptr = ptr3;
			i = i - 3;
		}else if(ptr1!=&head&&(ptr->cards[ptr->size-1].rank==ptr1->cards[ptr1->size-1].rank
			||ptr->cards[ptr->size-1].suit==ptr1->cards[ptr1->size-1].suit)){
			ret = ptr->cards[--ptr->size];
			if(ptr->size==0){
				/*
					Remove ptr, and connect its last with its next.
				*/
				ptr->last->next = ptr->next;
				ptr->next->last = ptr->last;
				/*
					Add ptr to tail.
				*/
				ptr3 = tail.last;
				ptr->next = ptr3->next;
				ptr->last = ptr3;
				ptr3->next = ptr;
				tail.last = ptr;
				s_size--;
			}
			ptr1->cards[ptr1->size++] = ret;
			ptr = ptr1;
			i--;
		}else{
			ptr = ptr->next;
			i++;
		}
	}
}
