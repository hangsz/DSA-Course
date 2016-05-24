#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;
struct node
{
	int address = -1;
	int data;
	int next = -1;

	inline node& operator=(node&);

	inline friend istream& operator>>(istream&, node&);
	inline friend ostream& operator<<(ostream&, node&);

};

node& node::operator=(node& nod){
	address = nod.address;
	data = nod.data;
	next = nod.next;
	return nod;
}
istream& operator>>(istream& is, node& nod){
	is >> nod.address >> nod.data >> nod.next;
	return is;
}
ostream& operator<<(ostream& os, node& nod){
	os << setw(5) << setfill('0') << nod.address << ' ' << nod.data << ' ' << setw(5) << setfill('0') << nod.next << endl;
	return os;
}





void sort(vector<node>&,int,int&);
void reverse(vector<node>&, int,int);
void print(vector<node>&,int);

int main(){
	
	vector<node> nvet;
	int start,N,K;
	cin >> start>>N>>K;

	node nod;
	for (int i = 0; i < N; ++i){
		cin >> nod;
		nvet.push_back(nod);
	}

	//cout << endl;

	int sortedNum = N;
	sort(nvet, start, sortedNum);
	reverse(nvet, K,sortedNum);
	print(nvet,sortedNum);
}

void sort(vector<node>& nvet,int start,int& sortedNum){   

	int site = start;
	unsigned size = nvet.size();
	node temp;
	for (int i = 0; i <size; ++i){
		int j = i ;
		for (;j< size; ++j){
			if (site == nvet[j].address){
				temp = nvet[i];
				nvet[i] = nvet[j];
				nvet[j] = temp;
				site = nvet[i].next;
				break;
			}
		}	
		/*if (j == size ) {
			sortedNum = i;
			break;
		}*/
	}

	sortedNum = nvet.size();

	//nvet.resize(sortedNum);

	//nvet.shrink_to_fit;
}


void reverse(vector<node>& nvet, int K,int sortedNum){

	node temp;
	for (int i = K - 1; i < sortedNum; i += K){
		for (int j = 0; j < K/2; ++j){
			temp = nvet[i - K + 1 + j];
			nvet[i - K + 1 + j]=nvet[i - j];
			nvet[i - j] = temp;	 
		}
	}

	for (int i = 0; i < sortedNum-1; ++i){
		nvet[i].next = nvet[i + 1].address;
	}
	nvet[sortedNum - 1].next = -1;

}

void print(vector<node>&nvet,int sortedNum){

	for (int i = 0; i < sortedNum-1; ++i){
			cout << nvet[i];
	}
	node nod = nvet[sortedNum - 1];
	cout << setw(5) << setfill('0') << nod.address << ' ' << nod.data << ' '<< nod.next << endl;
}
