#include<iostream>

#define Max  20

using namespace std;


struct treeNode{
	int val;
	treeNode* left = nullptr;
	treeNode* right = nullptr;
	int height = -1;
};

int max(int a, int b)	{
	return a > b ? a : b;
}

treeNode* insert(treeNode* tree, int value);

int getHeight(treeNode* tree);

treeNode* leftRotation(treeNode* tree);
treeNode* rightRotation(treeNode* tree); 
treeNode* leftRightRotation(treeNode* tree);
treeNode* rightLeftRotation(treeNode* tree);


int main(){

	treeNode* tree = nullptr;
	int N, L;
	int num[Max];

	cin >> N;
	for (int i = 0; i < N; ++i){
		cin >> num[i];
		
	}

	
	for (int i = 0; i < N; ++i)	
		tree = insert(tree, num[i]);	
	
	cout << tree->val;
}


treeNode* insert(treeNode* tree, int value){

	if (!tree){
		tree = new treeNode;
		tree->val = value;
	}
	else if ( value < tree->val){
		tree->left = insert(tree->left, value);
		if ( (getHeight(tree->left) - getHeight(tree->right)) == 2)
		{
			if (value < tree->left->val)  tree = leftRotation(tree);
			else tree = leftRightRotation(tree);
		}
	}
	else if( value > tree->val){
		tree->right = insert(tree->right, value);
		if ( (getHeight(tree->left) - getHeight(tree->right)) == -2)
		{											    
			if ( value > tree->right->val)  tree = rightRotation(tree);
			else tree = rightLeftRotation(tree);
		}

	}

	tree->height = max( getHeight(tree->left), getHeight(tree->right)) + 1;

	return tree;

}

int getHeight(treeNode* tree){
	return !tree ? -1 : tree->height;
}


treeNode* leftRotation(treeNode* A){
	treeNode* B = A->left;

	A->left = B->right;
	B->right = A;

	A->height = max( getHeight(A->left), getHeight(A->right)) + 1;
	B->height = max( getHeight(B->left), A->height ) + 1;

	return B;
}

treeNode* rightRotation(treeNode* A){
	treeNode* B = A->right;

	A->right = B->left;
	B->left = A;

	A->height = max( getHeight(A->left), getHeight(A->right) ) + 1;
	B->height = max( A->height, getHeight(B->right) ) + 1;

	return B;
}

treeNode* leftRightRotation(treeNode* A){

	A->left = rightRotation(A->left);
	return leftRotation(A);
}


treeNode* rightLeftRotation(treeNode* A){

	A->right = leftRotation(A->right);
	return rightRotation(A);
}


