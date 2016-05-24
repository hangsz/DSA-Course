#include <iostream>
#include<stack>

using namespace std;

int main(){

	

	int M, N, K;	 
	cin >> M >> N >> K;
	int *A = new int[N];
	int **B = new int*[K];

	for (int i = 0; i < K; ++i)
	{
		B[i] = new int[N];
	}
		
	for (int i = 0; i < K;++i){
		for (int j = 0; j < N; ++j)
		    cin >> B[i][j];
	}

	for (int i = 0; i < N; ++i)  A[i]=i+1;    

	for (int i = 0; i < K; ++i){	
		 // S ³õÊ¼»¯
		stack<int> S;
		S.push(A[0]);
		int k = 0;
		int j = 0;
		for (;j < N;++j){
			if (S.empty()) S.push( A[++k] );
			while (S.top() != B[i][j] && S.size()<M)  S.push( A[++k] );
			
			if (S.top() != B[i][j] ) break;
			else S.pop();	
		}
		if (j == N) cout << "YES" << endl;	
		else cout << "NO" << endl;
	}				
  
}