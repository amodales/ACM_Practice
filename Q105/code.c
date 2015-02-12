#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int pos;
	int height;
	struct Node *next;
}Node;

void show_list(Node*);
void show_debug_list(Node*);

int main(){
	int l, h, r, temp, temp_h;
	Node *head, *p, *n, *start;
	head = (Node*) malloc( sizeof(Node) );	
	head->pos = 0;
	head->height = 0;
	head->next = NULL;
	start = head;
	while(scanf("%d %d %d", &l, &h, &r)==3){
		p = start;
		if(l!=r){
			if(p->next==NULL){
				n = (Node*) malloc( sizeof(Node) );
				p->pos = r;
				n->pos = l;
				n->height = h;
				n->next = p;
				head = n;
				start = head;
			}else{
				while(p->next!=NULL&&p->next->pos<=l){
					p = p->next;
				}
				start = p;
				if(p->next!=NULL){
					temp_h = p->height;
					if(h>p->height){
						if(l==p->pos){
							p->height = h;
						}else{
							n = (Node*) malloc( sizeof(Node) );
							n->pos = l;
							n->height = h;
							n->next = p->next;
							p->next = n;
							p = n;
						}
					}
					temp = 0;
					while(p->next!=NULL&&p->next->pos<=r){
						if(h>p->height)	p->height = h;					
						p = p->next;
						temp++;
					}
					if(p->next!=NULL){
						if(temp!=0){
							if(h>p->height){
								if(r>p->pos){
									n = (Node*) malloc( sizeof(Node) );
									n->pos = r;
									n->height = p->height;
									n->next = p->next;
									p->height = h;
									p->next = n;
								}
							}
						}else{
							if(h>temp_h){
								if(r>p->pos){
									n = (Node*) malloc( sizeof(Node) );
									n->pos = r;
									n->height = temp_h;
									n->next = p->next;
									p->next = n;
								}
							}
						}
					}else{
						if(r>p->pos){
							n = (Node*) malloc( sizeof(Node) );
							n->pos = r;
							n->height = 0;
							n->next = NULL;
							p->height = h;
							p->next = n;
						}
					}
				}else{
					if(l>p->pos){
						n = (Node*) malloc( sizeof(Node) );
						n->pos = l;
						n->height = h;
						p->next = n;
						p = n;
					}else{
						p->height = h;							
					}
					n = (Node*) malloc( sizeof(Node) );
					n->pos = r;
					n->height = 0;
					n->next = NULL;
					p->next = n;
				}
			}
		}else{
			if(p->next==NULL){
				n = (Node*) malloc( sizeof(Node) );
				p->pos = r;
				n->pos = l;
				n->height = h;
				n->next = p;
				head = n;	
				start = head;			
			}else{
				while(p->next!=NULL&&p->next->pos<=l){
					temp_h = p->height;
					start = p;					
					p = p->next;
				}
				if(p->next!=NULL){
					if(l==p->pos){
						if(h>temp_h){
							n = (Node*) malloc( sizeof(Node) );
							n->pos = l;
							n->height = p->height;
							n->next = p->next;
							p->height = h;
						}		
					}else{
						if(h>p->height){
							n = (Node*) malloc( sizeof(Node) );
							n->pos = l;
							n->height = h;
							n->next = p->next;
							p->next = n;
							temp_h = p->height;
							p = n;
							n = (Node*) malloc( sizeof(Node) );
							n->pos = l;
							n->height = temp_h;
							n->next = p->next;
							p->next = n;
						}
					}
				}else{
					if(l==p->pos){
						if(h>temp_h){
							n = (Node*) malloc( sizeof(Node) );
							n->pos = l;
							n->height = 0;
							n->next = NULL;
							p->next = n;
							p->height = h;
						}
					}else{
						n = (Node*) malloc( sizeof(Node) );
						n->pos = l;
						n->height = h;
						p->next = n;
						p = n;
						n = (Node*) malloc( sizeof(Node) );
						n->pos = l;
						n->height = 0;
						n->next = NULL;
						p->next = n;
					}
				}
			}
		}
	}
	show_list(head);
	p = head;
	while(p!=NULL){
		n = p;
		p = p->next;
		free(n);
	}
	return 0;
}

void show_list(Node* list){
	Node *p;
	int temp=-1;
	p = list;
	while(p!=NULL){
		if(temp!=p->height){
			printf("%d %d", p->pos, p->height);
			temp = p->height;
			if(p->next!=NULL)	printf(" ");		
		}
		p = p->next;
	}
	printf("\n");
}

void show_debug_list(Node* list){
	Node *p;
	p = list;
	while(p!=NULL){
		printf("(%d %d)", p->pos, p->height);
		if(p->next!=NULL)	printf("  ");
		p = p->next;
	}
	printf("\n");
}
