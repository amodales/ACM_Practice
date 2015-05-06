#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int num[1500], count = 0;
	int p1 = 0, p2 = 0, p3 = 0;
	num[0] = 1;
	while(count<1500){
		while(num[p1]*2<=num[count])	p1++;
		while(num[p2]*3<=num[count])	p2++;
		while(num[p3]*5<=num[count])	p3++;
		if(num[p1]*2<num[p2]*3&&num[p1]*2<num[p3]*5){
			num[++count] = num[p1]*2;
		}else if(num[p2]*3<num[p3]*5){
			num[++count] = num[p2]*3;
		}else{
			num[++count] = num[p3]*5;
		}
	}
	printf("The 1500'th ugly number is %d.\n", num[1499]);
	return 0;
}
