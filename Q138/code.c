#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	long long int count=0, u=3, v=2, s, t;
	while(count<10){
		s = 3*u + 4*v;
		t = 2*u + 3*v;
		printf("%10lld%10lld\n", t/2, (s-1)/2);
		u = s;
		v = t;
		count++;
	}
	return 0;
}
