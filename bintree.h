// @file bintree.h
// @author Muhammed Saleh

#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"

//---------------------------------------------------------------------------
// Implements a Binary Search Tree for storing NodeData objects. NodeData
//    objects in the left subtree are less than the root, and NodeData
//    objects in the right subtree are greater than the root. Class allows
//    functionality for creation of new BinTree objects using using default
//    and copy constructors, clearing all memory of BinTree objects,
//    assigning one BinTree to another, checking to see if two BinTree
//    objects are equal or inequal, inserting a new NodeData into a
//    bintree, retrieving a NodeData object from a BinTree, displaying
//    a BinTree sideways, finding the depth of a node in a BinTree,
//    converting a BinTree to an array and converting an array to a BinTree
//    as well as printing the contents of a BinTree.
//
// A NodeData class must be properly defined with constructor, copy,
//    destructor, as well as all necessary comparison operators.


class BinTree {
   // output
   friend ostream& operator<<(ostream& output, const BinTree& tree);
   
   public:
   // constructors and destructor
   BinTree();                     // constructor
   BinTree(const BinTree& other); // copy constructor
   ~BinTree();                    // destructor, calls makeEmpty
   
   // operators
   BinTree& operator=(const BinTree& other);    // assigns left to right
   bool operator==(const BinTree& other) const; // equality
   bool operator!=(const BinTree& other) const; // inequality
   
   // other functions
   bool isEmpty() const;          // true if tree is empty, otherwise false
   void makeEmpty();              // make the tree empty
   bool insert(NodeData* value);                // inserts a new node
   bool retrieve(const NodeData&, NodeData*&) const; // retrieves a node
   void displaySideways() const; // displays the tree sideways
   int getDepth(const NodeData& value) const; // finds the depth of a node
   void bstreeToArray(NodeData* array[]); // converts the tree to an array
   void arrayToBSTree(NodeData* array[]); // converts an array to a tree
   
   private:
   struct Node {
      NodeData* data; // pointer to data object
      Node* left;     // left subtree pointer
      Node* right;    // right subtree pointer
   };
   Node* root;        // root of the tree
   
   // helper methods
   void makeEmptyHelper(Node*& rootPtr);
   bool insertHelper(Node* rootPtr, Node* temp);
   void inorderHelper(ostream& output, Node* root) const;
   void sideways(Node*, int) const;
   bool equalityHelper(const Node* thisRoot,
   const Node* otherRoot) const;
   bool retrieveHelper(Node* rootPtr, const NodeData& value,
                       NodeData*& pointer) const;
   void copyHelper(Node*& thisRoot, Node* otherRoot);
   int getDepthHelper(const NodeData& value, Node* rootPtr) const;
   void bstreeToArrayHelper(NodeData* array[], Node* rootPtr,
                            int& index) const;
   void arrayToBSTreeHelper(NodeData* tempArray[], int low, int high);
};

#endif
