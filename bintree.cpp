// @file bintree.cpp
// @author Muhammed Saleh

#ifndef BINTREE_CPP
#define BINTREE_CPP

#include "bintree.h"

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

// ---------------------------------------------------------------------------
// Constructor
// Default constructor for BinTree class
// Initializes an empty tree with root = NULL
BinTree::BinTree() {
   root = NULL;
}

// ---------------------------------------------------------------------------
// Copy
// Copy constructor for BinTree class
// Takes in another BinTree object and creates a copy of it by calling
// copyHelper
BinTree::BinTree(const BinTree& other) {
   copyHelper(root, other.root);
}

// ---------------------------------------------------------------------------
// Destructor
// Destructor for BinTree class
// Clears all memory in the BinTree object by calling makeEmpty
BinTree::~BinTree() {
   makeEmpty();
}

// ---------------------------------------------------------------------------
// isEmpty
// Checks to see if the root of the BinTree is NULL, returns true if so
bool BinTree::isEmpty() const {
   return root == NULL;
}

// ---------------------------------------------------------------------------
// makeEmpty
// Clears all memory in the BinTree by calling makeEmptyHelper
void BinTree::makeEmpty() {
   if (!isEmpty()) { // tree is not already empty
      makeEmptyHelper(root);
      root = NULL;
   }
}

// ---------------------------------------------------------------------------
// makeEmptyHelper
// Takes in a root pointer and deletes all nodes pointed to by that root
// as well as any data contained by those nodes
void BinTree::makeEmptyHelper(Node*& rootPtr) {
   if (rootPtr != NULL) {
      makeEmptyHelper(rootPtr->left); // recursively delete left
      makeEmptyHelper(rootPtr->right); // recursively delete right
      
      delete rootPtr->data; // clear DataNode memory
      rootPtr->data = NULL;
      
      delete rootPtr; // clear Node memory
      rootPtr = NULL;
   }
}

// ---------------------------------------------------------------------------
// operator=
// Overloaded assignment operator for BinTree class
// Clears all memory in the left tree, then creates a copy of the right tree
// and assigns it to the left tree
BinTree& BinTree::operator=(const BinTree& other) {
   if (this != &other) {
      makeEmptyHelper(root);
      copyHelper(root, other.root);
   }
   return *this;
}

// ---------------------------------------------------------------------------
// copyHelper
// Copies the nodes pointed to by one root to another root
void BinTree::copyHelper(Node*& thisRoot, Node* otherRoot) {
   if (otherRoot != NULL) { // other node isn't empty
      thisRoot = new Node; // make a copy of it and assign it to the left
      thisRoot->data = new NodeData(*otherRoot->data);
      
      copyHelper(thisRoot->left, otherRoot->left);
      copyHelper(thisRoot->right, otherRoot->right);
   } else { // other node is empty
      thisRoot = NULL;
   }
}

// ---------------------------------------------------------------------------
// operator==
// Overloaded equality operator for BinTree class
// Returns whether or not two BinTree objects are the same
bool BinTree::operator==(const BinTree& other) const {
   return equalityHelper(root, other.root);
}

// ---------------------------------------------------------------------------
// operator!=
// Overloaded inequality operator for BinTree class
// Returns whether or not two BinTree objects are different
bool BinTree::operator!=(const BinTree& other) const {
   return !(*this == other);
}

// ---------------------------------------------------------------------------
// equalityHelper
// Traverses two BinTrees recursively and returns false if the trees are
// different, true otherwise
bool BinTree::equalityHelper(const Node* thisRoot,
                             const Node* otherRoot) const {
   
   if (thisRoot != NULL && otherRoot != NULL) { // neither node is empty
      if (*thisRoot->data == *otherRoot->data) { // the two nodes are same
         // check to see if the left and right are the same
         return equalityHelper(thisRoot->right, otherRoot->right) &&
         equalityHelper(thisRoot->left, otherRoot->left);
      } else { // the two nodes arent the same
         return false;
      }
   }
   // true if both nodes are empty, false otherwise
   return thisRoot == NULL && otherRoot == NULL;
}

// ---------------------------------------------------------------------------
// insert
// Inserts a NodeData* object into the BinTree
bool BinTree::insert(NodeData* value) {
   Node* temp = new Node; // make a new node with value
   temp->data = value;
   temp->left = NULL;
   temp->right = NULL;
   
   if (root == NULL) { // the tree is already empty
      root = temp; // add the node
      return true;
   } else { // check the rest of the tree for a spot
      bool inserted = insertHelper(root, temp);
      if (!inserted) { // the node already exists
         delete temp;  // clear memory
      }
      return inserted;
   }
}

// ---------------------------------------------------------------------------
// insertHelper
// Helps insert a NodeData* object into the BinTree
bool BinTree::insertHelper(Node* rootPtr, Node* temp) {
   if (*temp->data == *rootPtr->data) { // node already exists
      return false;
   } else if (*temp->data < *rootPtr->data) { // go left
      if (rootPtr->left == NULL) { // spot is found
         rootPtr->left = temp;     // assign the new node to this spot
         return true;
      } else {
         return insertHelper(rootPtr->left, temp); // continue left
      }
   } else {                               // go right
      if (rootPtr->right == NULL) { // spot is found
         rootPtr->right = temp;     // assign
         return true;
      } else {
         return insertHelper(rootPtr->right, temp); // continue left
      }
   }
}

// ---------------------------------------------------------------------------
// retrieve
// Retrieves the pointer of a NodeData object if it exists in the BinTree
// returns true if found, false otherwise
bool BinTree::retrieve(const NodeData& value, NodeData*& pointer) const {
   if (root == NULL) { // tree is empty
      return false;    // nothing to retrieve
   } else {            // not empty
      return retrieveHelper(root, value, pointer); // traverse tree
   }
}

// ---------------------------------------------------------------------------
// retrieveHelper
// Traverses the tree to find the passed in NodeData object, returns true if
// found, false otherwise
bool BinTree::retrieveHelper(Node* rootPtr, const NodeData& value,
                             NodeData*& pointer) const {
   
   if (value == *rootPtr->data) { // object is found
      pointer = rootPtr->data;    // set it to pointer for access
      return true;
   } else if (value < *rootPtr->data) { // check left
      if (rootPtr->left != NULL) {
         return retrieveHelper(rootPtr->left, value, pointer);
      } else { // nothing left
         return false;
      }
   } else {                          // check right
      if (rootPtr->right != NULL) {
         return retrieveHelper(rootPtr->right, value, pointer);
      } else { // nothing right
         return false;
      }
   }
}

//---------------------------------------------------------------------------
// displaySideways
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const {
   sideways(root, 0);
}

// ---------------------------------------------------------------------------
// sideways
// Helper method for displaySideways
void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->right, level);
      // indent for readability, 4 spaces per depth level
      for(int i = level; i >= 0; i--) {
         cout << "    ";
      }
      cout << *current->data << endl;      // display information of object
      sideways(current->left, level);
   }
}

// ---------------------------------------------------------------------------
// getDepth
// Returns the depth of the passed in NodeData object, returns 0 if that
// object is not in the tree
int BinTree::getDepth(const NodeData& value) const {
   return getDepthHelper(value, root);
}

// ---------------------------------------------------------------------------
// getDepthHelper
// Traverses the tree recursively until the passed in object is found or all
// nodes have been visited and returns the depth of that object
int BinTree::getDepthHelper(const NodeData& value, Node* rootPtr) const {
   if (rootPtr == NULL) { // dead end, object wasn't found
      return 0;
   } else if (*rootPtr->data == value) { // found it
      return 1;
   } else {
      int leftDepth = getDepthHelper(value, rootPtr->left);
      int rightDepth = getDepthHelper(value, rootPtr->right);
      if (leftDepth == 0 && rightDepth == 0) { // both dead ends
         return 0; // not found
      } else {
         // return the sum of all the levels visited
         return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
      }
   }
}

// ---------------------------------------------------------------------------
// bstreeToArray
// Converts a BinTree object to an array, leaving the BinTree empty after
void BinTree::bstreeToArray(NodeData* array[]) {
   if (root != NULL) {
      int index = 0; // starting index for array traversal
      bstreeToArrayHelper(array, root, index);
      makeEmpty();   // leave the tree empty afterwards
   }
}

// ---------------------------------------------------------------------------
// bstreeToArrayHelper
// Performs an inorder traversal of the BinTree object, adding its contents
// to an array
void BinTree::bstreeToArrayHelper(NodeData* array[], Node* rootPtr,
                                  int& index) const {
   
   if (rootPtr->left != NULL) {
      bstreeToArrayHelper(array, rootPtr->left, index); // traverse left
   }
   
   array[index] = rootPtr->data; // add data to array
   index++;                      // increase index
   rootPtr->data = NULL;
   
   if (rootPtr->right != NULL) {
      bstreeToArrayHelper(array, rootPtr->right, index); // traverse right
   }
}

// ---------------------------------------------------------------------------
// arrayToBSTree
// Converts a sorted array to a balanced BinTree object
// Pre: the array must be sorted and have no more than 100 elements
void BinTree::arrayToBSTree(NodeData* array[]) {
   int size = 0;
   for(;;) { // find how many non-NULL elements are in the array
      if (array[size] == NULL) {
         break;
      }
      size++;
   }
   arrayToBSTreeHelper(array, 0, size - 1); // build tree
}

// ---------------------------------------------------------------------------
// arrayToBSTreeHelper
// Constructs a balanced BinTree from a sorted array
void BinTree::arrayToBSTreeHelper(NodeData* array[], int low, int high) {
   if (low <= high) { // valid index
      int rootIndex = (low + high) / 2; // find center of sub array
      
      insert(array[rootIndex]); // add it to tree
      array[rootIndex] = NULL;  // remove it from array
      
      arrayToBSTreeHelper(array, rootIndex + 1, high); // go left
      arrayToBSTreeHelper(array, low, rootIndex - 1);  // go right
   }
}

// ---------------------------------------------------------------------------
// operator<<
// Overloaded output operator for BinTree class
// Calls inorderHelper to print the contents of the BinTree inorder
ostream& operator<<(ostream& output, const BinTree& tree) {
   if (!tree.isEmpty()) { // there is something to print
      tree.inorderHelper(output, tree.root); // print it
   }
   output << endl;
   return output;
}

// ---------------------------------------------------------------------------
// inorderHelper
// Outputs the contents of the BinTree object using an inorder traversal
void BinTree::inorderHelper(ostream& output, Node* rootPtr) const {
   if (rootPtr->left != NULL) {
      inorderHelper(output, rootPtr->left); // traverse left
   }
   output << *rootPtr->data << " "; // print data
   if (rootPtr->right != NULL) {
      inorderHelper(output, rootPtr->right); // traverse right
   }
}

#endif
