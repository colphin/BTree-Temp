#include "btree.h"

BTreeNode::BTreeNode(bool leaf1){

	leaf = leaf1;	//whether or not it is a leaf

	person emptyPerson;
	emptyPerson.isPerson=false;
	emptyPerson.name = "";


	// the amount of keys are 5, all initialized to -1
	keys = new string[STR_ARR]; 
	for( int i = 0; i < STR_ARR; i++){
		keys[i] = EMPTY_KEY;
	}

	C = new BTreeNode*[STR_ARR+1]; //initialized to 6 with all NULL values
	for (int i = 0; i < STR_ARR+1; i++){
		C[i] = NULL;
	}

	dataVec.resize(STR_ARR+1); //size of dataVec[i] initialized to zero
	for( int i = 0; i < STR_ARR+1 ; i++){
		dataVec[i].resize(MAX_DATA , emptyPerson);
	}

	//The current of number of keys in the node is 0
	n = 0;
}


bool BTree::PositionFull(BTreeNode *root, person k){
	if (root->leaf){
		int leafPostion = 0;
		while (root->keys[leafPostion] < k.name and leafPostion < root->n){
			leafPostion++;
		}
		if (root->dataVec[leafPostion][0].isPerson==false) return true;
		else return false;
	}
	else{
		int downChildIndex = 0;
		while (root->keys[downChildIndex] < k.name and downChildIndex < root->n){
			downChildIndex++;
		}

		return PositionFull(root->C[downChildIndex], k);
	}
}


//General Insert - has to decide which case to use
// if the root is empty then create node and then insert it in
// if the root isn't full then go down to where you want to insert and call insert non full
// if the root is full then grow the tree and then insert it
// finds where the element is suppose to go and then just 
void BTree::insert(person k){

	// if the tree is empty;
	if (root == NULL){
		root = new BTreeNode(true);
		//if its the first element, no key just insert it into the first empty data slot
		root->dataVec[0][0] = k;
	}

	// for the 2nd insert
	else if (root->keys[0] == EMPTY_KEY){
		// if there is already something there compare it with the thing in there and see which to put as key
		// the case that the first insert is bigger than 2nd insert

		for (int i = 0; i <= MAX_DATA; i++){			
			if(i == MAX_DATA){
				root->splitLeaf(0,k);
			}
			else if (root->dataVec[0][i].isPerson==false){
				root->dataVec[0][i] = k;
				break;
			}
		}


	}

	//WRONG

	//if the root is full

	else if (root->n == STR_ARR and !PositionFull(root, k)){
        
		//create the new root called s
		BTreeNode * s = new BTreeNode(false);
		//let the first C pointer point of root
		s->C[0] = root;
		//split the root, now C[0] and C[1] are pointing to the two
//        if (s->C[0]->keys[STR_ARR/2]>=k){
//            s->splitNode1(0, root);
//        }else{
//            s->splitNode2(0, root);
//        }
        
        s->splitNode1(0, root);


        cout << "ROOT GROWTH new root key:" << s->keys[0] << endl;
        
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
void BTreeNode::insertNonFull(person k){
	// if the current node you are on is not a leaf, then traverse down till you find the right place	
	if (leaf == false){

		// goes to the correct pointer 
		int downChildIndex = 0;
		while (keys[downChildIndex] < k.name and downChildIndex < n){
			downChildIndex++;
            
		}
        
        if (C[downChildIndex]->n == STR_ARR){
            int leafposition = 0;
            while (C[downChildIndex]->keys[leafposition] < k.name and leafposition < STR_ARR){
                leafposition++;
            }
            
            bool isLeafFull = true;
            for( int i = 0; i < MAX_DATA ; i++){
                if (C[downChildIndex]->dataVec[leafposition][i].isPerson==false){
                    isLeafFull = false;
                    break;
                }
            }
            
            if (isLeafFull == true){
                
//                if (C[downChildIndex]->keys[STR_ARR/2]>=k){
//                    splitNode1(downChildIndex, C[downChildIndex]);
//                }else{
//                    splitNode2(downChildIndex, C[downChildIndex]);
//                }
                
                splitNode1(downChildIndex, C[downChildIndex]);
                downChildIndex++;
                int leafposition = 0;
                while (C[downChildIndex]->keys[leafposition] < k.name and leafposition < STR_ARR){
                    leafposition++;
                }
                
                bool isLeafFull = true;
                for( int i = 0; i < MAX_DATA ; i++){
                    if (C[downChildIndex]->dataVec[leafposition][i].isPerson==false){
                        isLeafFull = false;
                        break;
                    }
                }
                
            }
            
        }
        

		// At this point it calls insertNonFull at the new node
        if (C[downChildIndex]->n == 4){
            splitNode1(downChildIndex, C[downChildIndex]);
            downChildIndex++;
        }
		C[downChildIndex]->insertNonFull(k);
	}
	// The current node is a leaf
	else{
        
		// This finds where which the data vector should k go into
		int leafPosition = 0;
		while (keys[leafPosition] < k.name and leafPosition < n){
			leafPosition++;
		}

		bool isLeafFull = true;
		for( int i = 0; i < MAX_DATA ; i++){
			if (dataVec[leafPosition][i].isPerson==false){
				isLeafFull = false;
				break;
			}
		}

		// if the leaf is full then split it and insert it into correct leaf
		if (isLeafFull == true){
			splitLeaf(leafPosition,k);
		}
		// the leaf is not full and that means you get to just put it in
		else{
			dataVec[leafPosition].push_back(k);

			//delete first empty person
			for (int i = 0; i < MAX_DATA; i++){
				if (dataVec[leafPosition][i].isPerson == false){
					dataVec[leafPosition].erase(dataVec[leafPosition].begin() + i);
					break;
				}
			}
			sort(dataVec[leafPosition].begin(), dataVec[leafPosition].end(), myobject);
			// dataVec[leafPostion].erase(dataVec[leafPostion].begin());


		}

	}

}

//i is the location of y in y's parent node, y HAS to be full
//has to increment the parent n value (the num of keys)
//with the larger one on the left
void BTreeNode::splitNode1(int i, BTreeNode *y){
    
    cout << "SPLIT NODE 1 IS CALLED" << endl;
    
	//create the left and right nodes

	BTreeNode* leftChild = new BTreeNode(y->leaf);
	BTreeNode* rightChild = new BTreeNode(y->leaf);

	//move the needed keys to Right and Left
    for (int i = 0; i < STR_ARR/2; i++){
        leftChild->keys[i] = y->keys[i];
    }
    
    for (int i = 0; i < STR_ARR/2-1; i++){
        rightChild->keys[i] = y->keys[i+(STR_ARR/2)+1];
    }

	//move the pointers to Right and Left
    if (y->leaf == false){
        for (int i = 0; i<(int)((STR_ARR/2)+1);i++){
            leftChild->C[i] = y->C[i];
        }
        
        for (int i = 0; i <(int)(STR_ARR/2); i++){
            rightChild->C[i] = y->C[i + (STR_ARR/2)+1];
        }
    }

	if(y->leaf == true){
		for (int i = 0; i<(int)((STR_ARR)/2)+1;i++){
			leftChild->dataVec[i] = y->dataVec[i];
		}
		for (int i = 0; i<(int)((STR_ARR)/2);i++){
			rightChild->dataVec[i] = y->dataVec[i+(int)STR_ARR/2+1];
		}
	}		

	//move middle element to parent and scoot all over
	cout<< "n: "<<n<<endl;
	int j = n;
	while (j>i){
		keys[j] = keys[j-1];
		C[j+1] = C[j];
		j--;
	}

	//set the middle element in the correct place, set pointers i and i+1 to left and right
	keys[i] = y->keys[(int)STR_ARR/2];
    
	C[i] = leftChild;
	C[i+1] = rightChild;

	//update counts
    for (int j = 0; j < STR_ARR; j++){
        if (leftChild->keys[j] != EMPTY_KEY){
            leftChild->n = leftChild->n+1;
        }
        if (rightChild->keys[j] != EMPTY_KEY)
            rightChild->n = rightChild->n+1;
    }
    
    
    cout << "LEFT:" << leftChild->n << endl;
    cout << "RIGHT:" << rightChild->n << endl;
    
	n = n+1;

	//delete y
	free(y);
}



void BTreeNode::splitLeaf(int i, person k){
	person emptyPerson;
	emptyPerson.isPerson=false;
	emptyPerson.name = "";

	dataVec[i].push_back(k);
	int half_size =	(int)dataVec[i].size() / 2;
	sort(dataVec[i].begin(), dataVec[i].end(), myobject);
    vector<person> split_lo(dataVec[i].begin(), dataVec[i].begin() + half_size);
    vector<person> split_hi(dataVec[i].begin() + half_size, dataVec[i].end());
    dataVec[i]=split_lo;
	dataVec[i].insert(dataVec[i].begin(),emptyPerson);
    //loop for vectors leave space open on i+1 index
    for(int x = 3; x > i ; x--){
        dataVec[x+1]= dataVec[x];
    }
    dataVec[i+1]=split_hi;
    dataVec[i+1].insert(dataVec[i+1].begin(),emptyPerson);
    //loop through keys
    for(int x = 2; x >= i ; x--){
        keys[x+1]=keys[x];
    }
    keys[i] = split_hi[0].name;
    n++;  // Update number of keys in root
}



void BTree::printTree(BTreeNode *root){

	if (root == NULL) return;

	for (int i = 0 ; i < root->n; i++){
		if (root->leaf){
			for (int j = 0; j < MAX_DATA; j++){
				if (root->dataVec[i][j].isPerson==true)
					cout << "\t" << root->dataVec[i][j].name<<", "<<root->dataVec[i][j].index << endl;
			}		
		}
		cout<<"(KEY "<<i << "=" << root->keys[i] << ") " << endl;
	}
	// }

	if (root -> leaf){
		for (int j = 0; j < MAX_DATA; j++){
			if (root->dataVec[root->n][j].isPerson==true)
				cout << "\t" << root->dataVec[root->n][j].name<<", "<<root->dataVec[root->n][j].index << endl;
		}
	}

	cout << endl;

	for (int i = 0; i< root->n + 1; i++){
		printTree(root->C[i]);
	}
}
