#include "btree.h"

BTreeNode::BTreeNode(bool leaf1){

	leaf = leaf1;	//whether or not it is a leaf


	// the amount of keys are 5, all initialized to -1
	keys = new int[NUM_ARR]; 
	for( int i = 0; i < NUM_ARR; i++){
		keys[i] = EMPTY_KEY;
	}

	C = new BTreeNode*[NUM_ARR+1]; //initialized to 6
	dataVec.resize(NUM_ARR); //size of dataVec[i] initialized to zero
	for( int i = 0; i < NUM_ARR+1 ; i++){
		dataVec[i].resize(MAX_DATA , EMPTY_DATA);
	}

	//The current of number of keys in the node is 0
	n = 0;
}


//General Insert - has to decide which case to use
// if the root is empty then create node and then insert it in
// if the root isn't full then go down to where you want to insert and call insert non full
// if the root is full then grow the tree and then insert it
// finds where the element is suppose to go and then just 
void BTree::insert(int k){

	// if the tree is empty;
	if (root == NULL){
		root = new BTreeNode(true);
		//if its the first element, no key just insert it into the first empty data slot
		cout << "first insert" << endl;
		root->dataVec[0][0] = k;
	}

	// for the 2nd insert
	if (root->keys[0] == EMPTY_KEY){
		// if there is already something there compare it with the thing in there and see which to put as key
		// the case that the first insert is bigger than 2nd insert
		cout << "2nd insert "<< endl;
		if (root->dataVec[0][0] > k){
			root->dataVec[1][0] = root->dataVec[0][0];
			root->dataVec[0][0] = k;
			root->keys[0] = root->dataVec[1][0];
		}else{ // the case where the first insert is smaller than the 2nd insert
			root->dataVec[1][0] = k;
			root->keys[0] = k;
		}
		//update the number of keys
		root->n = root->n+1;
	}


	//if the root is full
	if (root->n == NUM_ARR){
		//create the new root called s
		BTreeNode * s = new BTreeNode(false);
		//let the first C pointer point of root
		s->C[0] = root;
		//split the root, now C[0] and C[1] are pointing to the two
		s->splitNode(0, root);

		//at this point n should be 1

		//this should go to one of the new children created
		s->insertNonFull(k);
		//change the root to now equal s
		root = s;
	}

	else{
		root->insertNonFull(k);
	}


}

//this always starts at root, and then it finds where it is suppose to be
//then puts it in
//needs to check for splitting children and leaf

//There are two cases
//		x is a leaf node
//			x is full split it and put it in
//			other wise just put it in
//		x isn't a leaf node
//	 		has to find where it belongs (will be done in insert non full)
//			if the child to insert is full has to split it and figure out which one k belongs too

void BTreeNode::insertNonFull(int k){
	// if the current node you are on is not a leaf, then traverse down till you find the right place
	if (leaf == false){
		int downChildIndex = 0;

	}
}

//i is the location of y in y's parent node, y HAS to be full
//has to increment the parent n value (the num of keys)
void BTreeNode::splitNode(int i, BTreeNode *y){

}

void BTree::printTree(BTreeNode *root){
	for (int i = 0 ; i < root->n; i++){
		cout<<"(KEY "<<i << "=" << root->keys[i] << ") ";
	}
	cout << endl;
}