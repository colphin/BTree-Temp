#include "btree.h"

#include <iostream>

using namespace std;

int main(){
	cout << "Hello" << endl;
	BTree *t = new BTree();

	t->insert(1);
	t->insert(2);

	t->printTree(t->getRoot());

}