#ifndef BTREE_H_
#define BTREE_H_

#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
using namespace std;

#define STR_ARR 4
#define MAX_DATA 3
#define INITIAL_INSERT 3
#define EMPTY_KEY ""

struct person{
        string name;
        int index;
        bool isPerson = true;
};

// A BTree node
class BTreeNode
{   
    string * keys; // An array of keys
    vector<vector<person>> dataVec;
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    //This is for the sort method
    struct myclass {
        bool operator() (person i,person j) { return (i.name<j.name);}
    } myobject;

    BTreeNode(bool _leaf);   // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(person k);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    // the larger is on the left
    void splitNode1(int i, BTreeNode *y);

    void splitLeaf(int i, person k);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in subtree rooted with this node.
    BTreeNode *search(person k);   // returns NULL if k is not present.


// Make BTree friend of this so that we can access private members of this
// class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    vector<person> initialVec; //insert to this before root is created;
public:
    // Constructor (Initializes tree as empty)
    BTree()
    {  root = NULL; }

    // function to traverse the tree
    void traverse();

    // function to search a key in this tree
    // BTreeNode* search(int k)
    // {  return (root == NULL)? NULL : root->search(k); }

    // The main function that inserts a new key in this B-Tree
    void insert(person k);

    void printTree(BTreeNode *root);

    BTreeNode* getRoot(){ return root; };

    bool PositionFull(BTreeNode *root,person k);
};

#endif