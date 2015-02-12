#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool is_contained(vector<int> &left, vector<int> &right);

class node{
	public:
		vector<int> seq;
		vector<int> children;
		int discover, finish;
		int length;
		int parent;		

		void connect(node& right, int lin, int rin){
			if(is_contained(seq, right.seq)){
				right.children.push_back(lin);
			}
			if(is_contained(right.seq, seq)){
				children.push_back(rin);
			}
		}
};

void DFS(node *vert, node &u, int &time, int k, vector<int> &prior);

int main(){
	vector<int> seq;
	vector<int> prior;
	node *vert;
	int k, n, index, max;
	while(cin >> k >> n){
		vert = new node[k];
		prior.clear();		
		seq.resize(n);
		for(int i=0; i<k; i++){
			for(int j=0; j<n; j++){
				cin >> seq[j];
			}
			sort(seq.begin(), seq.end());
			vert[i].parent = -1;
			vert[i].seq = seq;
			vert[i].discover = -1;
			vert[i].finish = -1;
			for(int j=0; j<i; j++){
				vert[i].connect(vert[j], i, j);
			}
		}
		for(int i=0, time=0; i<k; i++){
			if(vert[i].discover==-1){
				vert[i].discover = time++;
				DFS(vert, vert[i], time, k, prior);
				vert[i].finish = time++;
				prior.push_back(i);
			}
		}
		max = -1;
		for(int i=k-1; i>=0; i--){
			vert[prior[i]].length = 0;
			for(int j=k-1; j>i; j--){
				if(vert[prior[j]].length+1>vert[prior[i]].length){
					for(int m=0; m<vert[prior[j]].children.size(); m++){
						if(vert[prior[j]].children[m]==prior[i]){
							vert[prior[i]].length = vert[prior[j]].length+1;
							vert[prior[i]].parent = prior[j];
						}
					}
				}
			}
			if(vert[prior[i]].length>max){
				max = vert[prior[i]].length;
				index = prior[i];
			}
		}	
		cout << max+1 << endl;
		while(index!=-1){
			cout << index+1 << " ";
			index = vert[index].parent;
		}
		cout << endl;
		delete [] vert;
	}
	return 0;
}

void DFS(node *vert, node& u, int& time, int k, vector<int> &prior){
	for(int i=0; i<u.children.size(); i++){
		if(vert[u.children[i]].discover==-1){
			vert[u.children[i]].discover = time++;
			DFS(vert, vert[u.children[i]], time, k, prior);
			vert[u.children[i]].finish = time++;
			prior.push_back(u.children[i]);
		}
	}
}

bool is_contained(vector<int> &left, vector<int> &right){
	if(left.size()!=right.size())	return false;
	for(int i=0; i<left.size(); i++){
		if(left[i]>=right[i])	return false;
	}
	return true;
}
