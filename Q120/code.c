#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Flip(int [], int);
void Print(int [], int);

int main(){
	int n = 0, num = 0, i, j, max, index;
	int stack[30];
	char ch;
	memset(stack, 0, sizeof(stack));
	while(scanf("%c", &ch)!=EOF){
		switch(ch){
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9':
				num = num * 10 + ch - '0';
				break;
			case ' ':
				/*
					put pancake into stack.
				*/
				stack[n++] = num;
				/*
					Reset parameter.
				*/
				num = 0;
				break;
			case '\n':
				/*
					Put pancake into stack.
				*/
				stack[n++] = num;
				Print(stack, n);
				/*
					Start sorting.
					Initial value of m = n.
					Step 1: Find the max value of sub-stack(1-m).
					Step 2: Check if the max value is on the bottom of stack.
					If it is, then m = m - 1, and go back to step 1.
					If it isn't, then flip the max value to the top of the stack,
					flip the max value back to the bottom of the stack,
					and then m = m - 1, and go back to step 1.
					Step 3: while m = 0, print out 0.
				*/
				for(i=n-1; i>=0; i--){
					max = 0;
					index = -1;
					for(j=0; j<=i; j++){
						if(stack[j]>max){
							index = j;
							max = stack[j];
						}
					}
					if(index!=i){
						if(index!=0){
							Flip(stack, index);
							printf("%d ", n-index);
						}
						Flip(stack, i);
						printf("%d ", n-i);
					}
				}
				printf("0\n");
				/*
					Reset parameter.
				*/
				num = 0;
				n = 0;
				memset(stack, 0, sizeof(stack));
				break;
			default:
				break;
		}
	}
	return 0;
}

void Flip(int stack[], int bottom){
	int i, temp, limit;
	limit = bottom/2 + 1;
	for(i=0; i<limit; i++){
		temp = stack[i];
		stack[i] = stack[bottom-i];
		stack[bottom-i] = temp;
	}
}

void Print(int stack[], int num){
	int i;
	for(i=0; i<num; i++){
		printf("%d", stack[i]);
		if(i!=num-1)	printf(" ");
	}
	printf("\n");
}
