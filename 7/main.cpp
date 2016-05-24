#include <iostream>
#include <queue>
#include <vector>
#define treeMax 10

using namespace std;

struct treeNode{
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
void levelOrderTraversal(treeNode* tree, int root);


int main(){

	treeNode tree[treeMax];

	int root;
	root = buildTree(tree);

	levelOrderTraversal(tree, root);

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