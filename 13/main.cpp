#include <iostream>

#define Max 10000

using namespace std;


void Union(int*,int , int );
int isConnect(int*, int, int);

int components(int* computer,int N);
int main(){

	int N;
	char ch; int c1, c2;

	cin >> N;
	int* computer = new int[N];

	for (int i = 0; i < N; ++i)
		computer[i] = -1;

	while (true){
		cin >> ch;

		if(ch == 'S') break;

		cin >> c1 >> c2;
		if (ch == 'I')
			Union(computer, c1 - 1, c2 - 1);
		else if(ch =='C'){
			if ( isConnect(computer, c1-1, c2-1) ) cout << "yes" << endl;
			else cout << "no" << endl;
		}
	}

	int k = components(computer, N);
	if (k == 1) cout << "The network is connected.";
	else cout << "There are " << k << " components.";


}

void Union(int* computer,int c1, int c2){
	int root1 = c1, root2 = c2;
	while (computer[root1] > 0)
		root1 = computer[root1];
	while (computer[root2] > 0)
		root2 = computer[root2];

	if (computer[root1] < computer[root2]) {  
		computer[root1] += computer[root2];
		computer[root2] = root1;	
	}
	else {
		computer[root2] += computer[root1];
		computer[root1] = root2;
	}
}


int isConnect(int* computer, int c1, int c2){

	int root1 = c1, root2 = c2;
	while (computer[root1] > 0)
		root1 = computer[root1];
	while (computer[root2] > 0)
		root2 = computer[root2];

	if (root1 == root2)	  return 1;
	else return 0;

}

int components(int* computer,int N){
	int k = 0;
	for(int i = 0; i < N; ++i)
	    if (computer[i] < 0) k++;
	
	return k;

}

