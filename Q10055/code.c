#include <stdio.h>
#include <stdlib.h>

int main(){
	long long int num_self, num_opp, diff;
	while(scanf("%lld %lld", &num_self, &num_opp)==2){
		diff = num_opp - num_self;
		if(diff<0)	diff*=-1;
		printf("%lld\n", diff);
	}
	return 0;
}
