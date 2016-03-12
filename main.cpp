#include "btree.h"

#include <iostream>

using namespace std;

int main(){
	cout << "Hello" << endl;
	BTree *t = new BTree();

	// for (int i = 0; i < 1000; i++){
	// 	t->insert(i);
	// }


	person f; 
	f.name = "a";
	f.index = 123;

	person a;
	a.name="Ryan";
	a.index=5;

	person b;
	b.name = "Calvin";
	b.index = 2;

	person c; 
	c.name = "John";
	c.index = 1;

	person d; 
	d.name = "Sarah";
	d.index = 12;

	t->insert(a);
	t->insert(b);
	t->insert(c);
	t->insert(d);
	t->insert(f);
    
//    for (int i = 1000; i >= 0; i--){
//        t->insert(i);
//    }
    
    t->printTree(t->getRoot());
    cout << "---------------------" << endl;


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
}