#include <stdio.h>
#include <stdlib.h>

int main(){
	int count = 0;
	char ch;
	while(scanf("%c", &ch)!=EOF){
		switch(ch){
			case '\"':
				if(count%2==0)	printf("``");
				else	printf("''");
				count++;
				break;
			default:
				printf("%c", ch);
		}
	}
	return 0;
}
