#include <iostream>
#include <vector>
#include <string>

#define Max 100

using namespace std;


struct element{
	char ch;
	int fre;
	element() :fre(0){}
	element& operator=(element& ele1)	{ ch = ele1.ch; fre = ele1.fre; return *this; }
	friend istream& operator>>(istream& is,element& ele ){
		is >> ele.ch >> ele.fre;
		return is;
	}
	friend ostream& operator<<(ostream& os, element& ele){
		os << ele.ch << ele.fre;
		return os;
	}
}; 
struct huffmanTree{
	element ele;
	huffmanTree* left = nullptr;
	huffmanTree* right = nullptr;
};

struct minHeap{

	huffmanTree* huff[Max];
	int size;
	minHeap() :size(0) { huff[0] = new huffmanTree; huff[0]->ele.fre = 0; }

};

void insert(minHeap& heap, huffmanTree* huff);

huffmanTree* deleteMin(minHeap& heap);

huffmanTree* huffman(minHeap& heap);


int WPL(huffmanTree* huff,int depth);

int testWPL(vector<string>& code, element* chr, int wpl);

int isPre(vector<string>& code);

int main(){

	int N;
	cin >> N;

	minHeap heap;

	element* chr = new element[N];

	huffmanTree* huff;
	for (int i = 0; i < N; ++i){
		huff = new huffmanTree;
		cin >> chr[i];
		huff->ele = chr[i];
		insert(heap, huff);
	
	}

	huffmanTree* rootHuff = huffman(heap);

	int wpl = WPL(rootHuff,0);


	int M;
	cin >> M;

	vector<string> code(N);

	int flag = 0;
	char ch;

	for (int i = 0; i < M; ++i){
		for (int j = 0; j < N; j++){
			cin >>ch>> code[j];
			if ( code[j].size() > (N - 1) ) flag = 1;
		}

		if ( flag || !testWPL(code,chr,wpl) || !isPre(code) ) {
			cout << "No"<<endl;	
			flag = 0;
			continue;
		}
		else{
			cout << "Yes"<<endl;
		}
	}

}

void insert(minHeap& heap, huffmanTree* huff){		  // insert to the last position
	int i = ++heap.size;

	for (; heap.huff[i / 2]->ele.fre > huff->ele.fre; i /= 2){
		heap.huff[i] = heap.huff[i / 2];
	}
	heap.huff[i] = huff;
}


huffmanTree* deleteMin(minHeap& heap){		  // put the last one to a proper place
	huffmanTree* min = heap.huff[1];

	huffmanTree* last = heap.huff[heap.size--];

	int parent, child;

	for (parent = 1;parent*2 <= heap.size; parent = child){
		child = parent*2;
		if ( child != heap.size && (heap.huff[child]->ele.fre > heap.huff[child + 1]->ele.fre)	)
			++child;
		if (last->ele.fre <= heap.huff[child]->ele.fre) break;
		else heap.huff[parent] = heap.huff[child];
	}
	heap.huff[parent] = last;

	return min;
}

huffmanTree* huffman(minHeap& heap){
	huffmanTree* huff;

	for (int i = 0; heap.size>1;){

		huff = new huffmanTree;
		huff->left = deleteMin(heap);
		huff->right =deleteMin(heap);

		huff->ele.fre = huff->left->ele.fre + huff->right->ele.fre;
		insert(heap, huff);
	}

	huff = deleteMin(heap);

	return huff;
	
}


int WPL(huffmanTree* huff, int depth){
	if (!huff->left && !huff->right)
		return huff->ele.fre*depth;
	else
		return WPL(huff->left, depth + 1) + WPL(huff->right, depth + 1);
}


int testWPL(vector<string>& code, element* chr, int wpl){
	int sum = 0;
	for (int i = 0; i < code.size(); i++){
		sum += code[i].size() * chr[i].fre;
	}
	if (sum == wpl)  return 1;
	else return 0;
}


int isPre(vector<string>& code){
	struct charNode{
		int isLeaf = 0;
		charNode* left = nullptr;
		charNode* right = nullptr;
	};

	charNode* root = new charNode;
	charNode* p;
	for (int i = 0; i < code.size(); ++i){
		p = root;
		for (int j = 0; j < code[i].size(); ++j){
			if ( p->isLeaf == 0 ){
				if (code[i][j] == '0' ){ 
					if( !p->left) p->left = new charNode;			
					p = p->left;
				}
				else if (code[i][j] == '1'){ 
					if( !p->right) p->right = new charNode;
					p = p->right;
				}
			}
			else  return 0;
		}
		if ( !p->left && !p->right && !p->isLeaf)  // p if leaf node and is new  
		    p->isLeaf = 1;
		else return 0;
	}

	return 1;

}




