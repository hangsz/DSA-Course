#include<iostream>

#define Max 100000

using namespace std;

void bubbleSort(int A[], int N);

void insertSort(int A[], int N);

int main(){
	int N;
	int A[Max];
	cin >> N;
	for (int i = 0; i < N; ++i)  cin >> A[i];

	//bubbleSort(A, N);
	insertSort(A, N);
	cout << A[0];
	for (int i = 1; i < N; ++i)
		cout << ' ' << A[i];


}

void bubbleSort(int A[], int N){
	int i, j, temp, flag;
	for (j = N - 1; j > 0; --j){
		flag = 0;
		for (i = 0; i < j; ++i){
			if (A[i] > A[i + 1]) {
				temp = A[i + 1];
				A[i + 1] = A[i];
				A[i] = temp;
				flag = 1;
			}
		}
		if (flag == 0) break;
	}

}


void insertSort(int A[], int N){
	int i, j, temp;
	for (j = 1; j < N; ++j){
		temp = A[j];
		for (i = j; i > 0 && A[i - 1] > temp; --i)  A[i] = A[i - 1];
		A[i] = temp;
	}
}