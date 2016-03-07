#include "btree.h"

#include <iostream>

using namespace std;

int main(){
	cout << "Hello" << endl;
	BTree *t = new BTree();

	for (int i = 0; i < 58; i++){
		t->insert(i);
        t->printTree(t->getRoot());
	}
    


	// t->insert(12);
	// t->insert(10);
	// t->insert(15);
	// t->insert(5);
	// t->insert(1);
	// t->insert(17);
	// t->insert(3);
	// t->insert(13);
	// t->insert(8);
	// t->insert(2);
	// t->insert(7);
	// t->insert(4);


	// t->insert(12345);
	// t->insert(4351);
	// t->insert(135314);
	// t->insert(1451);
	// t->insert(243623);
	// t->insert(256);


	t->printTree(t->getRoot());

}