#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <stack>

#define treeMax 30

using namespace std;

struct treeNode{
	int num = 0;
	int left = -1;
	int right = -1;

	friend istream& operator>>(istream& is, treeNode& tree){
		char lc, rc;
		cin >> lc >> rc;
		if (lc != '-') tree.left = lc - '0';
		if (rc != '-') tree.right = rc - '0';
		return is;
	}
};

int buildTree(treeNode* tree);
int buildTreeFromCommand(treeNode* tree);
void levelOrderTraversal(treeNode* tree, int root);

void preOrderTraversal(treeNode* tree, int root);
void inOrderTraversal(treeNode* tree, int root);
void postOrderTraversal(treeNode* tree, int root);


int main(){

	treeNode tree[treeMax];

	int root;
	root = buildTreeFromCommand(tree);
	postOrderTraversal(tree, root);

	//levelOrderTraversal(tree, root);

}

int buildTree(treeNode* tree){

	int N, sum = 0;
	cin >> N;
	if (N == 0) return -1;
	for (int i = 0; i < N; ++i){
		cin >> tree[i];
		if (tree[i].left != -1)  sum += tree[i].left;
		if (tree[i].right != -1)  sum += tree[i].right;
	}

	return N*(N - 1) / 2 - sum;

}

int buildTreeFromCommand(treeNode* tree){
	string 	str;
	int nodeNum;
	int N;


	cin >> N;

	int* hit = new int[N];  //每个节点第一次命中关联左节点，第二次命中关联右节点。

	for (int i = 0; i < N; ++i)  hit[i] = 0;

	//初始化第一个节点
	cin >> str >> tree[0].num;


	stack<int> index;
	int curIndex = 0;

	index.push(0);

	int k = 0;
	for (int i = 1; i < 2 * N; ++i){

		//cout << "curIndex： " << curIndex << endl;
		//cout << "k: " << k << endl;



		cin >> str;
		if (str == "Push"){
			++k;
			index.push(k);
			cin >> tree[k].num;

			if (hit[curIndex] == 0){
				tree[curIndex].left = k;
				curIndex = index.top();
				//cout << "curIndex-left:" << curIndex << "-" << k << endl;

			}
			else if (hit[curIndex] == 1){
				tree[curIndex].right = k;
				curIndex = index.top();
				//cout << "curIndex-right:" << curIndex << "-" << k << endl;
			}
			//else
			//cout << "error";
		}
		else if (str == "Pop"){
			curIndex = index.top();
			hit[curIndex] = 1;
			index.pop();
		}
		//else
		//cout << "ERROR";
	}


	//for (int i = 0; i < N; ++i)
	//	cout << i<<'\t'<<tree[i].num << '\t' << tree[i].left << '\t' << tree[i].right << endl;


	delete[] hit;

	return 0;
}

void levelOrderTraversal(treeNode* tree, int root){
	queue<int> ique;

	vector<int> ivet;

	if (root == -1) return;
	ique.push(root);

	while (!ique.empty()){
		if (tree[ique.front()].left == -1 && tree[ique.front()].right == -1)
			ivet.push_back(ique.front());
		if (tree[ique.front()].left != -1)
			ique.push(tree[ique.front()].left);
		if (tree[ique.front()].right != -1)
			ique.push(tree[ique.front()].right);
		ique.pop();
	}

	for (int i = 0; i < ivet.size() - 1; ++i)
		cout << ivet[i] << ' ';
	cout << ivet[ivet.size() - 1];

}


void preOrderTraversal(treeNode* tree, int root){
	stack<int> istk;

	while (root || !istk.empty()){
		while (root){
			istk.push(root);
			cout << root;                         //第一次遇到，输出
			root = tree[root].left;
		}
		if (!istk.empty()){
			root = istk.top();

			istk.pop();
			root = tree[root].right;
		}

	}
}

void inOrderTraversal(treeNode* tree, int root){
	stack<int> istk;

	while (root || !istk.empty()){
		while (root){
			istk.push(root);
			root = tree[root].left;
		}
		if (!istk.empty()){
			root = istk.top();
			cout << root;					 // 第二次遇到，输出
			istk.pop();
			root = tree[root].right;
		}

	}

}

void postOrderTraversal(treeNode* tree, int root){

	if (root == -1) return;
	stack<int> istk;
	vector<int> ivet;
	int pre;

	istk.push(root);
	while (!istk.empty()){
		root = istk.top();
		if ((tree[root].left == -1 && tree[root].right == -1) || \
			(pre != -1 && (pre == tree[root].left || pre == tree[root].right))){
			ivet.push_back(root);
			//cout << tree[root].num;
			pre = root;
			istk.pop();
		}
		else{
			if (tree[root].right != -1)
				istk.push(tree[root].right);
			if (tree[root].left != -1)
				istk.push(tree[root].left);

		}
	}

	for (int i = 0; i < ivet.size() - 1; ++i)
		cout << tree[ivet[i]].num << " ";

	cout << tree[ivet[ivet.size() - 1]].num;

}