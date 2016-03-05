#include "btree.h"

#include <iostream>

using namespace std;

int main(){
	cout << "Hello" << endl;
	BTree *t = new BTree();

	t->insert(1);
	t->insert(3);
	t->insert(4);
	t->insert(2);
	t->insert(5);

	t->printTree(t->getRoot());

}