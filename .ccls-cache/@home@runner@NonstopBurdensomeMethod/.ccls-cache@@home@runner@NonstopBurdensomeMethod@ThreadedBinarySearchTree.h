//Created by Justin Guilarte,Pavan Sai Ram Korumilli, Jesus Celestino
//Css 342
//Date: 12/11/2021
//Purpose: To build a single Threaded Binary Search Tree with right threads.

#include <iostream>

using namespace std;

class BinaryTreeInterface;

class TreeNode {

  friend class BinaryTreeInterface;
  friend ostream &operator<<(ostream &ostream, const BinaryTreeInterface &bti);

private:
  // Data portion
  int item;
  // Pointer to left and right child
  TreeNode *leftChild = nullptr;
  TreeNode *rightChild = nullptr; 

  // Bool value that shows whether a node is threaded
  // to the right. True if it is threaded, false
  // if it is not.
  bool rightThread;

  // Constructor for the TreeNode object that goes
  // inside the Threaded Binary Tree.
  explicit TreeNode(const int nodeItem)
      : item(nodeItem), leftChild(NULL), rightChild(NULL), rightThread(false){};

public:
};

class BinaryTreeInterface {

private:
// Helper variable that acts as the max value when constructing 
// the Threaded Binary Tree.
  int end;
  // TreeNode pointer object that will be the root for the 
  // entire threaded binary tree.
  TreeNode *rootPtr;

public:

  // Constructor for the Threaded Binary Tree. It takes an integer
  // as a paremeter and makes a Threaded Binary Tree with n amount 
  // of nodes.
  explicit BinaryTreeInterface(int n);

  // Copy constructor that takes in a BinaryTreeInterface object,
  // and returns a new deep copy of it. 
  BinaryTreeInterface(BinaryTreeInterface &oldTree);

  // Overloaded << operator that will output the Tree.
  friend ostream &operator<<(ostream &ostream, const BinaryTreeInterface &bti);

  // Destructor that will return back the memory slots.
  virtual ~BinaryTreeInterface();

  // Helps the constructor build the Threaded Binary Search Tree.
  TreeNode *helperConstructionFunction(int array[], int begin, int end);

  // Threads the right leaves of the Tree together.
  TreeNode *addingThreads(TreeNode *root);

  // 
  TreeNode *leftMost(TreeNode *root) const;

  // traverse through binary tree in Inorder
  void inOrder();

  // removes a value
  bool removeThreadedBinaryTreeNode(int value);

  // adds an value in tree
  bool addTreeNode(int n);

  // deletes leaf nodes
  TreeNode *onlyLeafNodes(TreeNode *root, TreeNode *parent, TreeNode *curr);

  // only left child
  TreeNode *OnlyForLeftChild(TreeNode *root, TreeNode *parent, TreeNode *curr);

  // only right child
  TreeNode *OnlyForRightChild(TreeNode *root, TreeNode *parent, TreeNode *curr);

  // two node childs
  TreeNode *havingTwoNodeChilds(TreeNode *root, TreeNode *parent, TreeNode *curr);

  // Getter value for the end integer value.
  int getEndVal() const;

  // Getter method for the rootPtr field.
  TreeNode *getRootPtr() const;

  // Getter method for the Item integer value field.
  int getItemVal(const TreeNode *node) const;

/* Parameters: A TreeNode object
 * Return Value: Returns the right child
 */
  TreeNode *getRightChild(const TreeNode *node) const;

/* Parameters: A TreeNode object
 * Return Value: Returns the left child
 */
  TreeNode *getLeftChild(const TreeNode *node) const;

  /* Parameters: TreeNode object
 * Return Value: Returns the furthest right TreeNode
 */
  TreeNode *getFurthestRight(TreeNode *node);

/* Parameters: TreeNode object
 * Postcondition: TreeNode object points to nullptr and is deleted
 */
  void helperDestructor(TreeNode *Ptr);

/* Parameters: An integer value
 * Precondition: A BinaryTreeInterface object
 * Postcondition: None
 * Return Values: Returns true if the integer is in the BinaryTreeInterface
 object, false if not
 */
  bool contains(const int n);
};

// end BinaryTreeInterface
