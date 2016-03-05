#include "btree.h"

BTreeNode::BTreeNode(bool leaf1){

	leaf = leaf1;	//whether or not it is a leaf


	// the amount of keys are 5, all initialized to -1
	keys = new int[NUM_ARR]; 
	for( int i = 0; i < NUM_ARR; i++){
		keys[i] = EMPTY_KEY;
	}

	C = new BTreeNode*[NUM_ARR+1]; //initialized to 6 with all NULL values
	for (int i = 0; i < NUM_ARR+1; i++){
		C[i] = NULL;
	}

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
	else if (root->keys[0] == EMPTY_KEY){
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
	else if (root->n == NUM_ARR){
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

		// goes to the correct pointer 
		int downChildIndex = 0;
		while (keys[downChildIndex] < k and downChildIndex < n){
			downChildIndex++;
		}

		cout << "DCI" <<downChildIndex << endl;

		// At this point it calls insertNonFull at the new node
		// C[downChildIndex]->insertNonFull(k);
	}
	// The current node is a leaf
	else{
		// This finds where which the data vector should k go into
		int leafPostion = 0;
		while (keys[leafPostion] < k and leafPostion < n){
			leafPostion++;
		}

		bool isLeafFull = true;
		for( int i = 0; i < NUM_ARR+1 ; i++){
			if (dataVec[leafPostion][i] == EMPTY_DATA){
				isLeafFull = false;
				break;
			}
		}

		cout << "isleaffull: "<< isLeafFull << endl;


	}

}

//i is the location of y in y's parent node, y HAS to be full
//has to increment the parent n value (the num of keys)
void BTreeNode::splitNode(int i, BTreeNode *y){
	//create the left and right nodes
	BTreeNode leftChild(y->leaf);
	BTreeNode rightChild(y->leaf);

	//move the needed keys to Right and Left
	for (int i = 0; i<(int)(NUM_ARR/2); i++){
		leftChild.keys[i] = y->keys[i];
		rightChild.keys[i] = y->keys[i+(int)NUM_ARR/2 + 1];
	}

	//move the pointers to Right and Left
	for (int i = 0; i<(int)((NUM_ARR+1)/2);i++){
		leftChild.C[i] = y->C[i];
		rightChild.C[i] = y->C[i+(NUM_ARR+1)/2 + 1];
	}	

	//move middle element to parent and scoot all over
	int j = n;
	while (j>i){
		keys[j] = keys[j-1];
		C[j+1] = C[j];
		j--;
	}

	//set the middle element in the correct place, set pointers i and i+1 to left and right
	keys[i] = y->keys[(int)NUM_ARR/2];
	C[i] = &leftChild;
	C[i+1] = &rightChild;

	//update counts
	leftChild.n = rightChild.n = NUM_ARR/2;
	n = n+1;

	//delete y
	free(y);
}

void BTreeNode::splitLeaf(int i, vector<vector<int>> *y){

}



void BTree::printTree(BTreeNode *root){

	if (root == NULL) return;

	for (int i = 0 ; i < root->n; i++){
		cout<<"(KEY "<<i << "=" << root->keys[i] << ") ";
	}
	cout << endl;

	for (int i = 0; i< root->n + 1; i++){
		printTree(root->C[i]);
	}
}