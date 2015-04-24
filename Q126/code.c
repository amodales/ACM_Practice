#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {END, TERM} Type;

typedef struct Token{
	int coe;
	int exp_x, exp_y;
	Type type;
}Token;

Token getNextToken(char [], int *);

int get_digit(int);
int get_right(Token);
int Token_Compare(Token, Token);
int b_search(Token [], Token, int, int);

void Insert(Token [], Token, int *);
void Print_Token_Line(Token [], int);

int main(){
	char line[82];
	Token first[100], second[100], third[200], ret;
	int i, j, phase=0, count1=0, count2=0, count3=0, index;
	while(fgets(line, 82, stdin)!=NULL){
		if(strcmp(line, "#\n")==0)	break;
		i = 0;
		ret = getNextToken(line, &i);
		while(ret.type!=END){
			if(phase==0){
				first[count1++] = ret;
			}else{
				second[count2++] = ret;
			}
			ret = getNextToken(line, &i);
		}
		phase++;
		if(phase==2){
			for(i=0; i<count1; i++){
				for(j=0; j<count2; j++){
					ret.coe = first[i].coe*second[j].coe;
					ret.exp_x = first[i].exp_x + second[j].exp_x;
					ret.exp_y = first[i].exp_y + second[j].exp_y;
					ret.type = TERM;
					Insert(third, ret, &count3);
				}
			}
			Print_Token_Line(third, count3);
			count1 = 0;
			count2 = 0;
			count3 = 0;
			phase = 0;
		}
	}
	return 0;
}

Token getNextToken(char line[], int *index){
	Token ret;
	int i = *index, accept=0, num=0, sign=1, part=0, digit=0;
	ret.exp_x = 0;
	ret.exp_y = 0;
	while(line[i]!='\0'&&!accept){
		switch(line[i]){
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				num = num*10 + line[i] - '0';
				digit++;
				break;
			case '+':
				if(part==0&&digit!=0){
					ret.coe = num*sign;
					accept = 1;
				}else if(part==0){
					sign = 1;
				}else if(part==1){
					ret.exp_x = (num==0)? (digit==0)? 1: 0
						: num;
					accept = 1;
				}else{
					ret.exp_y = (num==0)? (digit==0)? 1: 0
						: num;
					accept = 1;
				}
				break;
			case '-':
				if(part==0&&digit!=0){
					ret.coe = num*sign;
					accept = 1;
				}else if(part==0){
					sign = -1;
				}else if(part==1){
					ret.exp_x = (num==0)? (digit==0)? 1: 0
						: num;
					accept = 1;
				}else{
					ret.exp_y = (num==0)? (digit==0)? 1: 0 
						: num;
					accept = 1;
				}
				break;
			case 'x':
				if(part==0){
					ret.coe = (num==0)? (digit==0)? sign: 0 
						: num*sign;
				}else{
					ret.exp_y = (num==0)? (digit==0)? 1: 0 
						: num;
				}
				digit = 0;
				part = 1;
				num = 0;
				break;
			case 'y':
				if(part==0){
					ret.coe = (num==0)? (digit==0)? sign: 0
						: num*sign;
				}else{
					ret.exp_x = (num==0)? (digit==0)? 1: 0
						: num;
				}
				digit = 0;
				part = 2;
				num = 0;
				break;
			case '\n':
				if(part==0){
					ret.coe = (num==0)? (digit==0)? sign: 0
						: num*sign;
				}else if(part==1){
					ret.exp_x = (num==0)? (digit==0)? 1: 0 
						: num;
				}else{
					ret.exp_y = (num==0)? (digit==0)? 1: 0 
						: num;
				}
				accept = 1;
				i++;
				break;
		}
		i = (accept)? i: i+1;
	}
	ret.type = (accept)? TERM: END;
	*index = i;
	return ret;
}

void Print_Token_Line(Token tok[], int max){
	int i, j;
	/*
		Exp_Line
	*/
	if(max==0){
		printf(" \n");
		printf("0\n");
		return;
	}
	if(tok[0].coe<0)	printf(" ");
	if(get_right(tok[0])){
		for(i=0; i<get_digit(abs(tok[0].coe)); i++){
			printf(" ");
		}
	}
	if(tok[0].exp_x!=0){
		printf(" ");
		if(tok[0].exp_x>1){
			printf("%d", tok[0].exp_x);
		}
	}
	if(tok[0].exp_y!=0){
		printf(" ");
		if(tok[0].exp_y>1){
			printf("%d", tok[0].exp_y);
		}
	}
	for(i=1; i<max; i++){
		printf("   ");
		if(get_right(tok[i])){
			for(j=0; j<get_digit(abs(tok[i].coe)); j++){
				printf(" ");
			}
		}
		if(tok[i].exp_x!=0){
			printf(" ");
			if(tok[i].exp_x>1){
				printf("%d", tok[i].exp_x);
			}
		}
		if(tok[i].exp_y!=0){
			printf(" ");
			if(tok[i].exp_y>1){
				printf("%d", tok[i].exp_y);
			}
		}
	}
	printf("\n");
	/*
		Fac_Line
	*/
	if(tok[0].coe<0)	printf("-");
	if(get_right(tok[0]))	printf("%d", abs(tok[0].coe));
	if(tok[0].exp_x>0){
		printf("x");
		if(tok[0].exp_x>1){
			for(i=0; i<get_digit(tok[0].exp_x); i++){
				printf(" ");
			}
		}
	}
	if(tok[0].exp_y>0){
		printf("y");
		if(tok[0].exp_y>1){
			for(i=0; i<get_digit(tok[0].exp_y); i++){
				printf(" ");
			}
		}
	}
	for(i=1; i<max; i++){
		if(tok[i].coe<0)	printf(" - ");
		if(tok[i].coe>0)	printf(" + ");
		if(get_right(tok[i]))	printf("%d", abs(tok[i].coe));
		if(tok[i].exp_x>0){
			printf("x");
			if(tok[i].exp_x>1){
				for(j=0; j<get_digit(tok[i].exp_x); j++){
					printf(" ");
				}
			}
		}
		if(tok[i].exp_y>0){
			printf("y");
			if(tok[i].exp_y>1){
				for(j=0; j<get_digit(tok[i].exp_y); j++){
					printf(" ");
				}
			}
		}
	}
	printf("\n");
}

int get_digit(int num){
	int ret = 0;
	while(num>0){
		ret++;
		num/=10;
	}
	return ret;
}

int get_right(Token tok){
	if(abs(tok.coe)!=1||abs(tok.coe)==1&&tok.exp_x==0&&tok.exp_y==0){
		return 1;
	}else{
		return 0;
	}
}

/*
	A < B , return -1
	A = B , return 0
	A > B , return 1
	A < B means that Token A should be ahead of Token B.
	A > B means that Token B should be ahead of Token A.
*/
int Token_Compare(Token a, Token b){
	if(a.exp_x<b.exp_x){
		return 1;
	}else if(a.exp_x>b.exp_x){
		return -1;
	}else{
		if(a.exp_y<b.exp_y){
			return -1;
		}else if(a.exp_y>b.exp_y){
			return 1;
		}else{
			return 0;
		}
	}
}

int b_search(Token tok[], Token tar, int left, int right){
	int mid = (left+right)/2;
	if(left<=right){
		if(Token_Compare(tok[mid], tar)>0){
			return b_search(tok, tar, left, mid-1);
		}else if(Token_Compare(tok[mid], tar)<0){
			return b_search(tok, tar, mid+1, right);
		}else{
			return mid;
		}
	}
	return -1;
}

void Insert(Token tok[], Token tar, int *max){
	int i, mark, count, index;
	count = *max;
	if(tar.coe==0)	return;
	index = b_search(tok, tar, 0, count-1);
	if(index==-1){
		for(i=0; i<count&&Token_Compare(tok[i], tar)<0; i++);
		mark = i;
		for(i=count; i>mark; i--){
			tok[i] = tok[i-1];
		}
		tok[mark] = tar;
		*max = count+1;
	}else{
		tok[index].coe += tar.coe;
		if(tok[index].coe==0){
			for(i=index; i<count-1; i++){
				tok[i] = tok[i+1];
			}
			count--;
		}
		*max = count;
	}
}
