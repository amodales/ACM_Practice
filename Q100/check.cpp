#include <iostream>

using namespace std;

int get_number(int);

int main(){
	long long int u_bound, l_bound, max, temp;
	while(cin >> l_bound >> u_bound){
		max = 0;
		for(int i=l_bound; i<=u_bound; i++){
			temp = get_number(i);
			if(max<=temp){
				max = temp;
			}
		}
		cout << l_bound << " " << u_bound << " " << max << endl;
	}	
	return 0;
}

int get_number(int index){
	int ret = 0;
	while(true){
		ret++;
		if(index==1)	break;
		if(index&1==1){
			index = 3 * index + 1;
		}else{
			index = index >> 1;
		}
	}
	return ret;
}
