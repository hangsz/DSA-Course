#include<iostream>

using namespace std;


struct treeNode{
	int val;
	treeNode* left = nullptr;
	treeNode* right = nullptr;
	int flag = 0;
};

treeNode* buildTree(treeNode* tree, int N);
treeNode* insert(treeNode* tree, int value);
void resetFlag(treeNode* tree);

void freeTree(treeNode* tree);

int judge(treeNode* tree, int N);

int check(treeNode* tree, int value);




int main(){

	treeNode* tree = nullptr;
	int N, L;

	while (true) {
		cin >> N;
		if (N == 0)  break;

		cin >> L;

		tree = buildTree(tree, N);

		for (int i = 0; i < L; ++i){
			if (judge(tree, N))	cout << "Yes" << endl;
			else cout << "No" << endl;
			resetFlag(tree);
		}
		freeTree(tree);
		tree = nullptr;

		//system("pause");
	}

}
treeNode* buildTree(treeNode* tree, int N){
	//cout << "buildTree" << endl;
	int value;
	for (int i = 0; i < N; ++i){
		cin >> value;
		tree = insert(tree, value);
	}
	return tree;

}

void freeTree(treeNode* tree){

	//cout << "freeTree" << endl;
	if (!tree) return;

	else{
		freeTree(tree->left);
		freeTree(tree->right);
		delete tree;
	}
}

void resetFlag(treeNode* tree){
	if (!tree) return;
	else{
		//cout << "tree flag: " << tree->flag<<endl;
		tree->flag = 0;
		//	cout << "tree flag: " << tree->flag<<endl;

		resetFlag(tree->left);
		resetFlag(tree->right);
	}

}

treeNode* insert(treeNode* tree, int value){
	//cout << "insert" << endl;

	if (!tree){
		tree = new treeNode;
		tree->val = value;
	}
	else{
		if (value < tree->val)
			tree->left = insert(tree->left, value);
		else
			tree->right = insert(tree->right, value);
	}

	return tree;

}

int judge(treeNode* tree, int N){

	//cout << "judge" << endl;
	int flag = 0;
	int value;
	for (int i = 0; i < N; ++i){
		cin >> value;
		if (!flag)
		{
			//cout << "check-------" << endl;
			if (!check(tree, value))
			{
				flag = 1;
				//cout << "flag:" << flag << endl;
			}

		}
	}
	if (flag) return 0;
	else return 1;

}

int check(treeNode* tree, int value){

	//cout << "check" << endl;
	if (!tree)  return 0;

	if (tree->flag){
		if (value < tree->val) check(tree->left, value);
		else if (value > tree->val) check(tree->right, value);
		else return 0;
	}
	else{
		if (tree->val == value){
			tree->flag = 1;
			//cout << "check 1:" << value << endl;
			return 1;
		}
		else {
			//cout << "check 0:" << value << endl;
			return 0;
		}
	}
}