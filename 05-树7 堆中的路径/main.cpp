#include <iostream>

#define Max 1000
#define MIN -10001

using namespace std;

struct minHeap{
	int ele[Max];
	int size;
	int capcity;
	minHeap(){ size = 0; capcity = Max; ele[0] = MIN; }
};

void insert(minHeap&, int);

int main(){
	int N, M;
	cin >> N >> M;

	int num;
	minHeap heap;
	for (int i = 0; i < N; ++i){
		cin >> num;
		insert(heap, num);
	}

	for (int i = 0; i < M; ++i){
		cin >> num;
		for (int j = num; j > 1; j /= 2)
			cout << heap.ele[j] << ' ';
		cout << heap.ele[1] << endl;
	}
}

void insert(minHeap& heap, int num){
	int i = ++heap.size;
	for (; heap.ele[i / 2] > num; i /= 2)
		heap.ele[i] = heap.ele[i / 2];
	heap.ele[i] = num;

}