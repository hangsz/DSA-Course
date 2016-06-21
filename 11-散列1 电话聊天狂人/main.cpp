#include <iostream>
#include <string>
#include <cmath>

#define maxSize 1000000

using namespace std;


struct Node{
	string phoneNo{ "" };
	int count{ 0 };
	Node *next{ nullptr };

};
struct HashTable{
	int tableSize{ 0 };
	Node *first{ nullptr };
};

HashTable* createTable(int N);
int nextPrime(int N);
void insert(HashTable *hashTable, const string &phoneNo);
int Hash(const string &phoneNo, const int tableSize);
void scan(const HashTable *hashTable);


int main(){

	int N;
	cin >> N;
	HashTable *hashTable = createTable(2 * N);
	string phoneNo;
	for (int i = 0; i < N; i++){
		cin >> phoneNo;  insert(hashTable, phoneNo);
		cin >> phoneNo;  insert(hashTable, phoneNo);
	}
	scan(hashTable);

}

HashTable* createTable(int N){
	HashTable *hashTable = new HashTable;
	hashTable->tableSize = nextPrime(N);
	hashTable->first = new Node[hashTable->tableSize];
	return hashTable;
}

int nextPrime(int N){

	int i;
	int p{ N % 2 ? N + 2 : N + 1 };

	while (p <= maxSize){
		for (i = sqrt(p); i > 2; i--)
			if (!(p%i)) 	break;

		if (i == 2) break;
		else p += 2;
	}

	return p;
}

void insert(HashTable *hashTable, const string &phoneNo){

	int pos{ Hash(phoneNo, hashTable->tableSize) };
	Node *head = hashTable->first + pos;

	Node *p = head->next;

	while (p && p->phoneNo != phoneNo)
		p = p->next;

	if (p)  p->count++;
	else{
		p = new Node;
		p->phoneNo = phoneNo;
		p->count = 1;
		p->next = head->next;
		head->next = p;
	}
}

int Hash(const string &phoneNo, const int tableSize){

	int pos;

	pos = stoi(phoneNo.substr(6, 10));

	return  pos%tableSize;

}

void scan(const HashTable * hashTable){
	string min{ " " };
	int count{ 0 };
	int no{ 0 };

	Node *node;
	for (int i = 0; i < hashTable->tableSize; i++){
		node = hashTable->first[i].next;
		while (node){
			if (node->count > count){
				min = node->phoneNo;
				count = node->count;
				no = 1;
			}
			else if (node->count == count){
				min = min < node->phoneNo ? min : node->phoneNo;
				no++;
			}
			node = node->next;
		}

	}
	if (no > 1)
		cout << min << ' ' << count << ' ' << no;
	else
		cout << min << ' ' << count;
}