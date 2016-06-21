#include<iostream>

#define Max 120

using namespace std;


int isInsertSort(int A[], int B[], int N);

void insertSort(int B[], int N, int p);
int getLength(int B[], int N);
void mergeSort(int B[], int N, int length);
void mergePass(int B[], int tmpB[], int N, int length);
void merge(int B[], int tmpB[], int left, int right, int rightEnd);

int main(){
	int N;
	cin >> N;
	int A[Max], B[Max];

	for (int i = 0; i < N; ++i)  cin >> A[i];
	for (int i = 0; i < N; ++i)  cin >> B[i];

	int p = isInsertSort(A, B, N);
	if (p != -1)	{
		insertSort(B, N, p);
		cout << "Insertion Sort" << endl;
	}
	else {
		int length = getLength(B, N);

		mergeSort(B, N, length);

		cout << "Merge Sort" << endl;
	}
	cout << B[0];
	for (int i = 1; i < N; ++i)
		cout << ' ' << B[i];


}

int isInsertSort(int A[], int B[], int N){
	int p = 0;
	int i, j;
	while (B[p] < B[p + 1])  p++;

	for (i = p + 1; i < N; ++i){
		if (A[i] != B[i])  return -1;
	}

	return p;

}

void insertSort(int B[], int N, int p){
	int i, j, tmp;

	for (i = p + 1; i < N; ++i){
		tmp = B[i];
		for (j = i; j<N && B[j - 1]>tmp; --j) {
			B[j] = B[j - 1];
		}
		B[j] = tmp;
		break;
	}
}
int getLength(int B[], int N){

	int length = 1;
	int i, j;

	int flag = 0;

	while (length < N)	{
		for (i = 0; i < N - 2 * length; i += 2 * length){
			for (j = i; j < i + 2 * length - 1; ++j){
				if (B[j] > B[j + 1]) {
					flag = 1;
					break;
				}
				if (flag == 1) break;

			}
		}
		if (i < N){
			for (j = i; j < N - 1; ++j){
				if (B[j] > B[j + 1]) {
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1) break;
		length *= 2;

	}
	return length;

}

void mergeSort(int B[], int N, int length){
	//int length =1;
	int tmpB[Max];

	//	length *= 2;

	while (length < N) {
		mergePass(B, tmpB, N, length);

		break;

		length *= 2;

		mergePass(tmpB, B, N, length);
		length *= 2;

	}

}



void mergePass(int B[], int tmpB[], int N, int length){
	int i;
	for (i = 0; i < N - 2 * length; i += 2 * length){
		merge(B, tmpB, i, i + length, i + 2 * length - 1);
		if (i + length < N){
			merge(B, tmpB, i, i + length, N - 1);
		}
		else{
			for (int j = i; j < N; ++j) tmpB[j] = B[j];
		}
	}
}

void merge(int B[], int tmpB[], int left, int right, int rightEnd){
	int leftEnd = right - 1;
	int tmp = left;
	int numEle = rightEnd - left + 1;
	while (left <= leftEnd && right <= rightEnd){
		if (B[left] <= B[right])  tmpB[tmp++] = B[left++];
		else tmpB[tmp++] = B[right++];
	}

	while (left <= leftEnd) tmpB[tmp++] = B[left++];
	while (right <= rightEnd) tmpB[tmp++] = B[right++];

	for (int i = 0; i < numEle; ++i, rightEnd--)  B[rightEnd] = tmpB[rightEnd];
}