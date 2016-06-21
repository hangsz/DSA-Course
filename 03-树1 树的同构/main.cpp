#include <iostream>

#define treeMax 10	

using namespace std;

struct treeNode{
	char value;
	int left = -1;
	int right = -1;

	friend istream& operator>>(istream& is, treeNode& node)	{
		char c1, c2;
		is >> node.value >> c1 >> c2;
		if (c1 == '-') node.left = -1;
		else node.left = c1 - '0';

		if (c2 == '-') node.right = -1;
		else node.right = c2 - '0';

		return is;
	}
};

int buildTree(treeNode* tree1);
int isomorphic(treeNode* tree1, int root1, treeNode* tree2, int root2);

int main(){

	treeNode  tree1[treeMax], tree2[treeMax];

	int root1, root2;

	root1 = buildTree(tree1);
	root2 = buildTree(tree2);

	if (isomorphic(tree1, root1, tree2, root2))
		cout << "Yes";
	else
		cout << "No";

	return 0;

}

int buildTree(treeNode* tree)
{
	int N, sum = 0;

	cin >> N;
	if (N == 0) return -1;

	for (int i = 0; i < N; ++i)
	{
		cin >> tree[i];
		if (tree[i].left != -1)  sum += tree[i].left;
		if (tree[i].right != -1)  sum += tree[i].right;
	}


	return N*(N - 1) / 2 - sum;

}

int isomorphic(treeNode* tree1, int root1, treeNode* tree2, int root2)
{
	if (root1 == -1 && root2 == -1)  return 1;
	if ((root1 != -1 && root2 == -1) || (root1 == -1 && root2 != -1))	 return 0;
	if (tree1[root1].value != tree2[root2].value) return 0;

	if ((tree1[root1].left == -1) && (tree2[root2].left == -1))
		return isomorphic(tree1, tree1[root1].right, tree2, tree2[root2].right);

	if ((tree1[root1].left != -1) && (tree2[root2].left != -1) && (tree1[tree1[root1].left].value == tree2[tree2[root2].left].value))
		return isomorphic(tree1, tree1[root1].left, tree2, tree2[root2].left) && \
		isomorphic(tree1, tree1[root1].right, tree2, tree2[root2].right);
	else
		return isomorphic(tree1, tree1[root1].left, tree2, tree2[root2].right) && \
		isomorphic(tree1, tree1[root1].right, tree2, tree2[root2].left);

}