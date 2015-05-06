#include <stdio.h>
#include <stdlib.h>

typedef struct Person{
	int label;
	struct Person *next, *last;
}Person;

int main(){
	int n, m, k, l, r, count;
	Person head, end, *ptr1, *ptr2, *b;
	while(scanf("%d %d %d", &n, &k, &m)!=EOF){
		if(n==0&&k==0&&m==0)	break;
		/*
			Construct a circular list
		*/
		count = 0;
		head.next = ptr2 = (Person *) malloc(sizeof(Person));
		head.last = NULL;
		end.last = NULL;
		end.next = ptr2;
		ptr2->label = ++count;
		while(count<n){
			ptr1 = (Person *) malloc(sizeof(Person));
			ptr1->label = ++count;
			ptr1->next = head.next;
			ptr1->next->last = ptr1;
			head.next = ptr1;
		}
		ptr2->next = ptr1;
		ptr1->last = ptr2;
		/*
			Count member.
			ptr1 move counter-clockwise. k people.
			ptr2 move clockwise. m people.
		*/
		ptr1 = end.next;
		ptr2 = head.next;
		while(n>0){
			l = 1;
			while(l<k){
				ptr1 = ptr1->last;
				l++;
			}
			r = 1;
			while(r<m){
				ptr2 = ptr2->next;
				r++;
			}
			if(ptr1!=ptr2){
				printf("%3d%3d", ptr1->label, ptr2->label);
				if(ptr1->last==ptr2){
					/*
						  <--last-- node --next-->
						new_ptr1 ptr2 ptr1 new_ptr2
					*/
					ptr1 = ptr2->last;
					ptr2 = ptr2->next->next;
					free(ptr1->next);
					free(ptr2->last);
					ptr1->next = ptr2;
					ptr2->last = ptr1;
				}else if(ptr1->next==ptr2){
					/*
						  <--last-- node --next-->
						new_ptr1 ptr1 ptr2 new_ptr2
					*/
					ptr1 = ptr1->last;
					ptr2 = ptr2->next;
					free(ptr1->next);
					free(ptr2->last);
					ptr1->next = ptr2;
					ptr2->last = ptr1;
				}else{
					/*
						     <--last-- node --next-->
						b new_ptr1 ptr1 y ptr2 new_ptr2 c
					*/
					b = ptr1;
					ptr1->last->next = ptr1->next;
					ptr1->next->last = ptr1->last;
					ptr1 = ptr1->last;
					free(b);
					b = ptr2;
					ptr2->last->next = ptr2->next;
					ptr2->next->last = ptr2->last;
					ptr2 = ptr2->next;
					free(b);
				}
				n-=2;
			}else{
				/*
					Remove this guy from the list.
					and set ptr1 be ptr1->last,
					ptr2 be ptr2->next.
				*/
				printf("%3d", ptr1->label);
				ptr1 = ptr1->last;
				ptr2 = ptr2->next;
				free(ptr1->next);
				ptr1->next = ptr2;
				ptr2->last = ptr1;

				n--;
			}
			if(n!=0)	printf(",");
		}
		printf("\n");
	}
	return 0;
}
