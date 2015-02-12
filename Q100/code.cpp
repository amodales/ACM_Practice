#include <iostream>
#include <vector>

using namespace std;

int main(){
	bool done;
	long long int *number; 
	vector<int> rec;
	long long int lb, ub, times, max, temp;
	while(cin >> lb >> ub){
		number = new long long int[ub-lb+1];
		max = 0;
		for(int i=0; i<ub-lb+1; i++){
			number[i] = 0;
		}
		for(int i=0; i<ub-lb+1; i++){
			if(number[i]==0){
				done = false;
				times = 0;
				temp = lb + i;
				rec.clear();
				while(!done){
					times++;
					if(temp==1){
						done = true;
					}else{
						if(lb<=temp&&temp<=ub&&(temp-lb)!=i){
							if(number[temp-lb]==0){
								// 40 20 10 5* 16 8 4 2 1
								number[temp-lb] = times-1;
								rec.push_back(temp-lb);
							}else{
								// 40 20 10 5* 16 8 4 2 1
								done = true;
								times += number[temp-lb];
								times--;
							}
						}
						if(temp&1==1){
							temp = 3 * temp + 1;
						}else{
							temp = temp >> 1;
						}
					}
				}
				number[i] = times;
				if(times>max) max = times;
				for(int j=0; j<rec.size(); j++){
					number[rec[j]] = times - number[rec[j]];
				}
			}
		}
		cout << lb << " " << ub << " " << max << endl;
		delete [] number;
	}
	return 0;
}
