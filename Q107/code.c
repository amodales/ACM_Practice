#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long llu_int;

llu_int Power_N(llu_int, llu_int);

int main(){
	llu_int h, n, m, fac, power, found, sum_h, sum_work, num;
	while(scanf("%llu %llu", &h, &n)==2){
		if(n>h)	continue;
		if(h==0&&n==0)	break;
		if(n!=1||h!=1){
			found = 0;
			for(m=1; m<=200&&!found; m++){
				for(fac=1; fac<=1000; fac++){
					if(Power_N(fac, m)==n&&Power_N(fac+1, m)==h){
						found = 1;
						power = m;
						break;
					}
				}
			}
			if(!found&&n==1)	fac=1;
			num = 1;
			sum_h = 0;
			sum_work = 0;
			while(h!=0){
				sum_h += h*num;
				sum_work += num;
				num *= fac;
				h/=(fac+1);
			}
			printf("%llu %llu\n", sum_work-n, sum_h);
		}else{
			printf("0 1\n");
		}
	}	
	return 0;
}

llu_int Power_N(llu_int base, llu_int n){
	llu_int m=base, ret=1;
	while(n!=0){
		if(n%2==1){
			ret *= m;
		}
		m*=m;
		n/=2;
	}
	return ret;
}
