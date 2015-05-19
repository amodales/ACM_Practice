#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char name;
	int size;
	int neighbor[8];
}Node;

typedef struct perm{
	int list[8];
	int size, bandwidth;
}perm;

int search(Node [], int, char);
int search_N(Node, int);
int Band_Compute(perm, Node []);
int Band_Compare(perm, perm, Node []);

void Calculation(Node [], perm *, perm, int);

int check[8];

int main(){
	int size, i, j, ph, p_index, c_index;
	char line[1000];
	perm min, mid;
	Node nod[8];
	while(fgets(line, 1000, stdin)!=NULL){
		if(strcmp(line, "#\n")==0)	break;
		/*
			Processing data.
		*/
		size = 0;
		ph = 0;
		i = 0;
		while(line[i]!='\n'){
			if(line[i]==':'){	
				ph = 1;
			}else if(line[i]==';'){
				ph = 0;
			}else{
				if(!ph){
					p_index = search(nod, size, line[i]);
					if(p_index==-1){
						p_index = size;
						nod[size].size = 0;
						nod[size++].name = line[i];
					}
				}else{
					c_index = search(nod, size, line[i]);
					if(c_index==-1){
						c_index = size;
						nod[size].size = 0;
						nod[size++].name = line[i];
					}
					j = search_N(nod[p_index], c_index);
					if(j==-1){
						nod[p_index].neighbor[nod[p_index].size++] = c_index;
					}
					j = search_N(nod[c_index], p_index);
					if(j==-1){
						nod[c_index].neighbor[nod[c_index].size++] = p_index;
					}
				}
			}
			i++;
		}
		/*
			Calculate.
		*/
		memset(check, 0, sizeof(check));
		min.bandwidth = 99;
		mid.size = 0;
		Calculation(nod, &min, mid, size);
		for(i=0; i<min.size; i++){
			printf("%c ", nod[min.list[i]].name);
		}
		printf("-> %d\n", min.bandwidth);
	}
	return 0;
}

int search(Node nod[], int size, char name){
	int i;
	for(i=0; i<size; i++){
		if(nod[i].name==name)	return i;
	}
	return -1;
}

int search_N(Node n, int tar){
	int i;
	for(i=0; i<n.size; i++){
		if(n.neighbor[i]==tar)	return i;
	}
	return -1;
}

void Calculation(Node nod[], perm *min, perm mid, int max){
	int i, index;
	if(mid.size!=max){
		for(i=0; i<max; i++){
			if(check[i]==0){
				mid.list[mid.size++] = i;
				check[i] = mid.size;
				Calculation(nod, min, mid, max);
				check[i] = 0;
				mid.size--;
			}
		}
	}else{
		mid.bandwidth = Band_Compute(mid, nod);
		if(Band_Compare(*min, mid, nod)){
			*min = mid;
		}
	}
}

int Band_Compute(perm tar, Node nod[]){
	int max = 0, i, j, temp;
	for(i=0; i<tar.size; i++){
		for(j=0; j<nod[tar.list[i]].size; j++){
			temp = abs(check[tar.list[i]] - check[nod[tar.list[i]].neighbor[j]]);
			if(temp>max)	max = temp;
		}
	}
	return max;
}

int Band_Compare(perm a, perm b, Node nod[]){
	int i;
	char ca, cb;
	if(a.bandwidth>b.bandwidth){
		return 1;	
	}else if(a.bandwidth<b.bandwidth){
		return 0;
	}else{
		for(i=0; i<b.size; i++){
			ca = nod[a.list[i]].name;
			cb = nod[b.list[i]].name;
			if(ca>cb)	return 1;
			if(ca<cb)	return 0;
		}
	}
}
