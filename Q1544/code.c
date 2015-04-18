#include <stdio.h>
#include <stdlib.h>

typedef struct BigNumber{
	int length;
	char digit[2001];
}BigNumber;

void Reverse(BigNumber *);

BigNumber Add(BigNumber, BigNumber);
BigNumber Sub(BigNumber, BigNumber);
BigNumber MultiplyInt(BigNumber, int);
BigNumber MoveLeftInt(BigNumber, int);

int main(){
	BigNumber a, b, p_result[500], result;
	char ch;
	int n, accept, op, i, j, count, limit, s_limit;
	a.length = 0;
	b.length = 0;
	scanf("%d\n", &n);
	while(n>0){
		/*
			Input
		*/
		accept = 0;
		op = 0;
		while(!accept){
			ch = fgetc(stdin);
			switch(ch){
				case '+':
					a.digit[a.length] = '\0';
				 	op = 1;
					break;
				case '-':
					a.digit[a.length] = '\0';
					op = 2;
					break;
				case '*':
					a.digit[a.length] = '\0';
					op = 3;
					break;
				case '\n': case EOF:
					b.digit[b.length] = '\0';
					accept = 1;
					break;
				default:
					/*
						WARNING: PRETEND THERE IS NOTHING BUT "NUMBER" HERE.
					*/
					if(op==0){
						a.digit[a.length++] = ch - '0';	
					}else{
						b.digit[b.length++] = ch - '0';
					}
					break;
			}
		}
		Reverse(&a);
		Reverse(&b);
		if(op==1){
			result = Add(a, b);
			limit = (result.length>b.length+1)?	result.length: b.length+1;
			/*
				Line 1: First Number
			*/
			for(i=0; i<limit-a.length; i++)	printf(" ");
			for(i=a.length-1; i>=0; i--){
				printf("%d", a.digit[i]);
			}
			printf("\n");
			/*
				Line 2: Second Number + Operator
			*/
			for(i=0; i<limit-b.length-1; i++)	printf(" ");
			printf("+");
			for(i=b.length-1; i>=0; i--){
				printf("%d", b.digit[i]);
			}
			printf("\n");
			/*
				Line 3: Horizontal Line
			*/
			for(i=0; i<limit; i++)	printf("-");
			printf("\n");
			/*
				Line 4: Result
			*/
			for(i=0; i<limit-result.length; i++)	printf(" ");
			for(i=result.length-1; i>=0; i--){
				printf("%d", result.digit[i]);
			}
			printf("\n");
		}else if(op==2){
			result = Sub(a, b);
			limit = (a.length>b.length+1)? a.length:b.length+1;
			s_limit = (result.length>b.length+1)?	result.length: b.length+1;
			/*
				Line 1: First Number
			*/
			for(i=0; i<limit-a.length; i++)	printf(" ");
			for(i=a.length-1; i>=0; i--){
				printf("%d", a.digit[i]);
			}
			printf("\n");
			/*
				Line 2: Second Number + Operator
			*/
			for(i=0; i<limit-b.length-1; i++)	printf(" ");
			printf("-");
			for(i=b.length-1; i>=0; i--){
				printf("%d", b.digit[i]);
			}
			printf("\n");
			/*
				Line 3: Horizontal Line
			*/
			for(i=0; i<limit-s_limit; i++)	printf(" ");
			for(i=0; i<s_limit; i++)	printf("-");
			printf("\n");
			/*
				Line 4: Result
			*/
			for(i=0; i<limit-result.length; i++)	printf(" ");
			for(i=result.length-1; i>=0; i--){
				printf("%d", result.digit[i]);
			}
			printf("\n");
		}else{
			result.length = 1;
			result.digit[0] = 0;
			result.digit[1] = '\0';
			for(i=0; i<b.length; i++){
				p_result[i] = MultiplyInt(a, b.digit[i]);
				result = Add(MoveLeftInt(p_result[i], i), result);
			}
			limit = (result.length>b.length+1)? result.length:b.length+1;
			s_limit = (p_result[0].length>b.length+1)? p_result[0].length:b.length+1;
			/*
				Line 1: First Number
			*/
			for(i=0; i<limit-a.length; i++)	printf(" ");
			for(i=a.length-1; i>=0; i--){
				printf("%d", a.digit[i]);
			}
			printf("\n");
			/*
				Line 2: Second Number + Operator
			*/
			for(i=0; i<limit-b.length-1; i++)	printf(" ");
			printf("*");
			for(i=b.length-1; i>=0; i--){
				printf("%d", b.digit[i]);
			}
			printf("\n");
			/*
				Line 3: Horizontal Line 1
			*/
			for(i=0; i<limit-s_limit; i++)	printf(" ");
			for(i=0; i<s_limit; i++)	printf("-");
			printf("\n");
			/*
				Line 4 - ?: Summation
			*/
			for(i=0; i<b.length; i++){
				for(j=0; j<limit-p_result[i].length-i; j++)	printf(" ");
				for(j=p_result[i].length-1; j>=0; j--){
					printf("%d", p_result[i].digit[j]);
				}
				printf("\n");
			}
			if(b.length>1){
				/*
					Line ?+1: Horizontal Line 2
				*/
				for(i=0; i<limit-result.length; i++)	printf(" ");
				for(i=0; i<result.length; i++)	printf("-");
				printf("\n");
				/*
					Line ?+2: Result
				*/
				for(i=0; i<limit-result.length; i++)	printf(" ");
				for(i=result.length-1; i>=0; i--){
					printf("%d", result.digit[i]);
				}
				printf("\n");
			}
		}
		/*
			Reset parameter
		*/
		a.length = 0;
		b.length = 0;
		n--;
		printf("\n");
	}
	return 0;
}

void Reverse(BigNumber *ptr){
	int i;
	char temp;
	for(i=0; i<(ptr->length+1)/2; i++){
		temp = ptr->digit[i];
		ptr->digit[i] = ptr->digit[ptr->length-i-1];
		ptr->digit[ptr->length-i-1] = temp;
	}
}

BigNumber Add(BigNumber a, BigNumber b){
	BigNumber ret, temp;
	int i;
	if(b.length>a.length){
		temp = a;
		a = b;
		b = temp;
	}
	ret.digit[0] = 0;
	for(i=0; i<b.length; i++){
		ret.digit[i] = a.digit[i] + b.digit[i] + ret.digit[i];
		ret.digit[i+1] = ret.digit[i]/10;
		ret.digit[i] = ret.digit[i]%10;
	}
	for(i=b.length; i<a.length; i++){
		ret.digit[i] += a.digit[i];
		ret.digit[i+1] = ret.digit[i]/10;
		ret.digit[i] = ret.digit[i]%10;
	}
	i = a.length;
	if(ret.digit[a.length]!=0)	i++;
	ret.length = i;
	ret.digit[i] = '\0';
	return ret;
}

BigNumber Sub(BigNumber a, BigNumber b){
	BigNumber ret = a;
	int i, j, k;
	for(i=b.length-1; i>=0; i--){
		ret.digit[i] -= b.digit[i];
	}
	/*
		Eliminate negative digit in all digits.
	*/
	for(i=0; i<b.length; i++){
		j = i;
		if(ret.digit[i]<0){
			while(ret.digit[j]<=0){
				j++;
			}
			ret.digit[j] -= 1;
			for(k=j-1; k>i; k--){
				ret.digit[k] += 9;
			}
			ret.digit[i] += 10;
		}
		i = j;
	}
	/*
		Eliminate zero on the left.
	*/
	for(i=a.length-1; ret.digit[i]==0; i--){
		ret.length--;
	}
	ret.digit[ret.length] = '\0';
	return ret;
}

BigNumber MultiplyInt(BigNumber a, int n){
	BigNumber ret;
	int i;
	if(n==0){
		ret.length = 1;
		ret.digit[0] = 0;
		ret.digit[1] = '\0';
		return ret;
	}
	ret.digit[0] = 0;
	for(i=0; i<a.length; i++){
		ret.digit[i] += (a.digit[i] * n);
		ret.digit[i+1] = ret.digit[i]/10;
		ret.digit[i] = ret.digit[i]%10;
	}
	while(ret.digit[i]!=0){
		ret.digit[i+1] = ret.digit[i]/10;
		ret.digit[i] = ret.digit[i]%10;
		i++;
	}
	ret.digit[i] = '\0';
	ret.length = i;
	return ret;
}

BigNumber MoveLeftInt(BigNumber a, int n){
	BigNumber ret;
	int i;
	for(i=0; i<n; i++){
		ret.digit[i] = 0;
	}
	for(i=0; i<a.length; i++){
		ret.digit[i+n] = a.digit[i];
	}
	ret.length = a.length + n;
	ret.digit[ret.length] = '\0';
	return ret;
}
