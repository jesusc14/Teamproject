#include "ThreadedBinarySearchTree.h"
#include <array>
#include <iostream>
#include <queue>

using namespace std;

// Constructor for BinaryTreeInterfae; Takes in an integer as data value
BinaryTreeInterface::BinaryTreeInterface(int n) {
  this->end = n;
  int start = 1;
  int mid = (start + end) / 2;
  int end = n;
  int arr[n - 1];

  for (int i = 1; i <= n; i++) {
    arr[i] = i;
  }

  rootPtr = helperConstructionFunction(arr, start, end);
  addingThreads(rootPtr);
};

/* Parameters: BinaryTreeInterface
 * Precondition: BinaryTreeInterface object must be created already
 * Postcondition: Creates a deeop copy of the BinaryTreeInterface object
 */
BinaryTreeInterface::BinaryTreeInterface(BinaryTreeInterface &source) {
  vector<int> newTree;

  TreeNode *temp = source.leftMost(source.rootPtr);

  while (temp != nullptr) {
    newTree.push_back(temp->item);
    if (temp->rightThread) {
      temp = temp->rightChild;
    } else
      temp = leftMost(temp->rightChild);
  }
  this->end = newTree.size();
  int start = 0;
  int *arr = newTree.data();

  this->rootPtr = helperConstructionFunction(arr, start, end - 1);

  addingThreads(this->rootPtr);
}

// Outputs an in-order traversal of the BinaryTreeInterface
ostream &operator<<(ostream &output, const BinaryTreeInterface &bti) {
  if (bti.rootPtr == nullptr) {
    output << "Tree is empty" <<endl;
  }

  TreeNode *curr = bti.leftMost(bti.rootPtr);

  while (curr->rightChild != nullptr) {
    output << curr->item << ", ";
    if (curr->rightThread) {
      curr = curr->rightChild;
    } else {
      curr = bti.leftMost(curr->rightChild);
    }
  }
  output << curr->item;
  return output;
};

/* Parameters: An array, and two integers
 * Precondition: Must have BinaryTreeInterface object
 * Postcondition: A TreeNode is deleted
 * Return Values: Returns true if the Treenode is removed, false if not
 */
TreeNode *BinaryTreeInterface::helperConstructionFunction(int arr[], int begin, int end) {
  if (begin > end) {
    return nullptr;
  }

  int mid = (begin + end) / 2;

  TreeNode *root = new TreeNode(arr[mid]);

  root->leftChild = helperConstructionFunction(arr, begin, mid - 1);
  root->rightChild = helperConstructionFunction(arr, mid + 1, end);

  return root;
};

// Destructor; Deletes a BinaryTreeInterface object
BinaryTreeInterface::~BinaryTreeInterface() { helperDestructor(rootPtr); };

/* Parameters: TreeNode object
 * Postcondition: TreeNode object points to nullptr and is deleted
 */
void BinaryTreeInterface::helperDestructor(TreeNode *Ptr) {
  TreeNode *curr = leftMost(Ptr);
  while (curr) {
    TreeNode *temp = curr;
    if (temp->rightThread) {
      temp = curr;
      curr = curr->rightChild;

      delete temp;
    } else {
      temp = curr;
      curr = leftMost(curr->rightChild);

      delete temp;
    }
  }
};

/* Parameters: TreeNode object
 * Precondition: Must have BinaryTreeInterface object
 * Postcondition: A threaded Binary Tree is create
 * Return Values: The TreeNode that is being threaded
 */
TreeNode *BinaryTreeInterface::addingThreads(TreeNode *root) {
  if (root == nullptr) {
    return nullptr;
  }
  if (root->leftChild == nullptr && root->rightChild == nullptr) {
    return root;
  }
  if (root->leftChild != nullptr) {
    TreeNode *temp = addingThreads(root->leftChild);

    temp->rightChild = root;
    temp->rightThread = true;
  }
  if (root->rightChild == nullptr) {
    return root;
  }

  return addingThreads(root->rightChild);
};

/* Parameters: TreeNode object
 * Precondition: None
 * Postcondition: Left most TreeNode is found
 * Return Values: Returns the left most TreeNode
 */
TreeNode *BinaryTreeInterface::leftMost(TreeNode *root) const {
  while (root != nullptr && root->leftChild != nullptr) {
    root = root->leftChild;
  }
  return root;
};

void BinaryTreeInterface::inOrder() {
  if (rootPtr == nullptr) {
    return;
  }

  TreeNode *temp = leftMost(rootPtr);

  while (temp != nullptr) {
    cout << temp->item << " ";

    if (temp->rightThread) {
      temp = temp->rightChild;
    } else
      temp = leftMost(temp->rightChild);
  }
};

// The first case of the remove function; Removes a TreeNode if it has no
// children
TreeNode *BinaryTreeInterface::onlyLeafNodes(TreeNode *root, TreeNode *parent, TreeNode *curr) {

  // if root is the one being deleted
  if (parent == nullptr) {
    root = nullptr;
    delete root;
    return nullptr;
  } else {
    if (parent->rightChild == curr) {
      parent->rightChild = curr->rightChild;
      if (curr->rightThread) {
        parent->rightThread = true;

        curr->rightChild = nullptr;
      }
    } else {
      parent->leftChild = curr->leftChild;
    }
  }
  delete curr;
  return root;
};

// Helper function for removeThreadedBinaryTreeNode; Removes TreeNode that
// contains a leftChild
TreeNode *BinaryTreeInterface::OnlyForLeftChild(TreeNode *root, TreeNode *parent, TreeNode *curr) {

  if (parent == nullptr) {
    root = root->leftChild;
    curr->leftChild = nullptr;
    delete curr;
  }
  if (parent->leftChild == curr) {
    parent->leftChild = curr->leftChild;
    if (curr->leftChild->rightThread) {
      curr->leftChild->rightChild = curr->rightChild;
    }
  } else {
    parent->rightChild = curr->leftChild;
    if (curr->leftChild->rightThread) {
      curr->leftChild->rightChild = nullptr;
      curr->leftChild->rightThread = false;
    }
  }
  curr->leftChild = nullptr;
  curr->rightChild = nullptr;
  delete curr;
  return root;
};

// Helper function for removeThreadedBinaryTreeNode; Removes TreeNode that
// contains a rightChild
TreeNode *BinaryTreeInterface::OnlyForRightChild(TreeNode *root, TreeNode *parent, TreeNode *curr) {

  if (parent == nullptr) {
    root = root->rightChild;
    curr->rightChild = nullptr;
    delete curr;
  }
  if (parent->leftChild == curr) {
    parent->leftChild = curr->rightChild;
    curr->rightChild = nullptr;
    delete curr;
  } else {
    parent->rightChild = curr->rightChild;
    curr->rightChild = nullptr;
    delete curr;
  }
  return root;
};

// Helper function for removeThreadedBinaryTreeNode; Removes TreeNode that
// conatins two children
TreeNode *BinaryTreeInterface::havingTwoNodeChilds(TreeNode *root, TreeNode *parent, TreeNode *curr) {

  TreeNode *rmv = curr->leftChild;
  while (rmv->rightChild != nullptr && !rmv->rightThread) {
    rmv = rmv->rightChild;
  }
  int newItem = rmv->item;
  removeThreadedBinaryTreeNode(newItem);
  curr->item = newItem;
  return parent;
};

/* Parameters: An integer value
 * Precondition: Must have BinaryTreeInterface object
 * Postcondition: A TreeNode is deleted
 * Return Values: Returns true if the Treenode is removed, false if not
 */
bool BinaryTreeInterface::removeThreadedBinaryTreeNode(int value) {
  TreeNode *curr = rootPtr;
  TreeNode *parent = nullptr;
  bool flag = false;

  while (curr != nullptr) {
    if (curr->item == value) {
      flag = true;
      break;
    }
    parent = curr;
    if (curr->item < value) {
      if (curr->rightChild != nullptr && !curr->rightThread) {
        curr = curr->rightChild;
      } else {
        break;
      }
    } else {
      if (curr->leftChild != nullptr) {
        curr = curr->leftChild;
      } else {
        break;
      }
    }
  }
  if (flag == true) {
    if (curr->leftChild == nullptr &&
        (curr->rightChild == nullptr || curr->rightThread)) {
      onlyLeafNodes(rootPtr, parent, curr);
      return true;
    } else if (curr->leftChild != nullptr &&
               (curr->rightChild == nullptr || curr->rightThread)) {
      OnlyForLeftChild(rootPtr, parent, curr);
      return true;
    } else if (curr->leftChild == nullptr &&
               (curr->rightChild != nullptr && !curr->rightThread)) {
      OnlyForRightChild(rootPtr, parent, curr);
      return true;
    } else {
      havingTwoNodeChilds(rootPtr, parent, curr);
      return true;
    }
  }
  return false;
};

/* Parameters: An integer value
 * Precondition: Must have BinaryTreeInterface object
 * Postcondition: A TreeNode is deleted
 * Return Values: Returns true if the Treenode is removed, false if not
 */
bool BinaryTreeInterface::addTreeNode(int n) {
  TreeNode *newTreeNode = new TreeNode(n);

  if (contains(n)) {
    return false;
  }

  if (n < 0) {
    return false;
  }
  TreeNode *parent = nullptr;
  TreeNode *current = rootPtr;

  while (true) {
    parent = current;
    if (n < current->item) {
      current = current->leftChild;
      if (current == nullptr) {
        parent->leftChild = newTreeNode;
        newTreeNode->rightChild = parent;
        newTreeNode->rightThread = true;
        return true;
      }
    } else {
      if (current->rightThread == false) {
        current = current->rightChild;
        if (current == nullptr) {
          parent->rightChild = newTreeNode;
          return true;
        } else {
        }
      } else {
        TreeNode *temp = current->rightChild;
        current->rightChild = newTreeNode;
        newTreeNode->rightChild = temp;
        newTreeNode->rightThread = true;
        return true;
      }
    }
  }
  return false;
};

/* Parameters: None
 * Return Value: Returns the end value of the BinaryTreeInterface
 */
int BinaryTreeInterface::getEndVal() const { return end; };

/* Parameters: None
 * Return Value: Returns the rootPtr
 */
TreeNode *BinaryTreeInterface::getRootPtr() const { return this->rootPtr; };

/* Parameters: TreeNode object
 * Return Value: Returns the item integer value of the TreeNode object
 */
int BinaryTreeInterface::getItemVal(const TreeNode *node) const {
  return node->item;
};

/* Parameters: A TreeNode object
 * Return Value: Returns the right child
 */
TreeNode *BinaryTreeInterface::getRightChild(const TreeNode *node) const {
  return node->rightChild;
};

/* Parameters: A TreeNode object
 * Return Value: Returns the left child
 */
TreeNode *BinaryTreeInterface::getLeftChild(const TreeNode *node) const {
  return node->leftChild;
};

/* Parameters: TreeNode object
 * Return Value: Returns the furthest right TreeNode
 */
TreeNode *BinaryTreeInterface::getFurthestRight(TreeNode *node) {
  while (this->getRightChild(node)) {
    node = node->rightChild;
  }
  return node;
};

/* Parameters: An integer value
 * Precondition: A BinaryTreeInterface object
 * Postcondition: None
 * Return Values: Returns true if the integer is in the BinaryTreeInterface
 object, false if not
 */
bool BinaryTreeInterface::contains(const int n) {
  if (rootPtr == nullptr || n < 0) {
    return false;
  }
  TreeNode *temp = leftMost(rootPtr);

  while (temp != nullptr) {
    if (temp->item == n) {
      return true;
    }
    if (temp->rightThread) {
      temp = temp->rightChild;
    } else {
      temp = leftMost(temp->rightChild);
    }
  }
  return false;
};
