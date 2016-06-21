#include<iostream>

#define Max 100000
#define MaxAge 51

using namespace std;


int* bucketSort(int A[], int N);

int main(){
	int N;
	cin >> N;

	int A[Max];
	for (int i = 0; i < N; ++i){
		cin >> A[i];
	}

	int *age = bucketSort(A, N);

	for (int i = 0; i < MaxAge; ++i){
		if (age[i] != 0) cout << i << ":" << age[i] << endl;
	}

	delete[] age;

}

int* bucketSort(int A[], int N){

	int *age = new int[MaxAge];
	for (int i = 0; i < MaxAge; ++i) age[i] = 0;
	for (int i = 0; i < N; ++i){
		age[A[i]]++;
	}
	return age;
}