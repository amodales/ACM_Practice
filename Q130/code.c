#include <stdio.h>
#include <stdlib.h>

typedef struct Person{
	int rank;
	struct Person *next;
}Person;

void PRINT(Person *, Person *);

int main(){
	Person head, *ptr1, *ptr2, *last1, *last2;
	int n, k, i, j;
	while(scanf("%d %d", &n, &k)==2){
		if(n==0&&k==0)	break;
		ptr2 = (Person *) malloc(sizeof(Person));
		ptr2->rank = n;
		head.next = ptr2;
		for(i=n-1; i>=1; i--){
			ptr1 = (Person *) malloc(sizeof(Person));
			ptr1->rank = i;
			ptr1->next = head.next;
			head.next = ptr1;
		}
		ptr2->next = head.next;
		ptr1 = head.next;
		for(i=1; i<n; i++){
			for(j=1; j<k; j++){
				last1 = ptr1;
				ptr1 = ptr1->next;
			}
			ptr2 = ptr1->next;
			last1->next = ptr1->next;
			if(head.next==ptr1)	head.next = last1;
			free(ptr1);
			for(j=1; j<k; j++){
				last2 = ptr2;
				ptr2 = ptr2->next;
			}
			if(last1!=ptr2){
				last2->next = ptr2->next;
				ptr2->next = last1->next;
				last1->next = ptr2;
			}
			ptr1 = ptr2->next;
		}
		ptr1 = head.next;
		/*
			[x + (rank - 1)] % n = 1
			=> x + (rank - 1) = 1 + n
			=> x = (n + 2 - rank) % n
		*/
		j = (n + 2 - ptr1->rank) % n;
		if(j==0)	j = n;
		printf("%d\n", j);
		free(ptr1);
	}
	return 0;
}
