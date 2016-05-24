#include <iostream>
#include <cmath>
#include <cstdlib>

#define Max 1000

using namespace std;



int compare(const void* a,const void* b){
	return *(int*)a - *(int*)b;
}

void solve(int*,int, int, int*,int);
int getLeft(int N);
int main(){
	
	int N;
	int test[Max];	
	
	cin >> N ;
	for (int i = 0; i < N; ++i)
		cin >> test[i];

	qsort(test, N, sizeof(int), compare);


	int CBST[Max];

	solve(test, 0, N - 1, CBST, 0);


	cout << CBST[0];

	for (int i = 1; i < N; ++i)
		cout <<" "<< CBST[i];


}

void solve(int* test,int left, int right, int* CBST, int pos)		{
	
	int length = right - left + 1;
	if ( length == 0)  return;

	int L;

	L = getLeft(length);	 

	//cout << L;

	CBST[pos] = test[left + L];

	int Lpos, Rpos;

	Lpos = 2 * pos + 1;
	Rpos = Lpos + 1;

	solve(test,left, left+L-1, CBST, Lpos);
	solve(test,left + L + 1, right, CBST, Rpos);


}

int getLeft(int N)	{
	if (N == 1)  return 0;	
	if (N == 2 || N == 3)  return 1;

	int k=0;
	while (true){
		if ( pow(2, k + 2) > N + 1)  break;
		++k;	
	}

	int m = N + 1 - pow(2, k + 1);

	if ( (m - pow(2, k) > 0))  return pow(2, k+1)-1;
	else	return pow(2, k)-1 + m;

}

