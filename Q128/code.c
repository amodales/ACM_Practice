#include <stdio.h>
#include <stdlib.h>
#define v 34943

int main(){
	char line[1025];
	long long m;
	int i, hex;
	while(fgets(line, 1025, stdin)!=NULL){
		if(line[0]=='#')	break;
		i = 0;
		m = 0;
		while(line[i]!='\n'){
			m = (m << 8) % v;
			m = (m + line[i]) % v;
			i++;	
		}
		m = (m << 8) % v;
		m = (m << 8) % v;
		hex = (v - m) % v;
		printf("%02X %02X\n", (hex >> 8)%v, hex % 256);
	}
	return 0;
}
