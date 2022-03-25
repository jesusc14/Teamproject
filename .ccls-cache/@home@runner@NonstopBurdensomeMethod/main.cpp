//Created by Justin Guilarte,Pavan Sai Ram Korumilli, Jesus Celestino
//On Dec. 12, 2021



#include "ThreadedBinarySearchTree.h"
#include <iostream>
#include <cassert>
using namespace std;

// Method that tests the required specifications.
void ass5Requirments() {
  BinaryTreeInterface tbst(10);
  BinaryTreeInterface tbst2(tbst);
  for (int i = 2; i <= tbst2.getEndVal(); i += 2) {
    tbst2.removeThreadedBinaryTreeNode(i);
  }
  cout << tbst2 <<endl;
  cout << "Requirements for assignment 5 done." << endl;
}

void testPrintThreadBinaryTree() {
  BinaryTreeInterface tbst(40);
  cout << tbst << endl;
  cout << "End of Test two" << endl;
}

void testRemoveAllEvens() {
  BinaryTreeInterface tbst(50);
  BinaryTreeInterface tbst2(tbst);
  int value = 50;
  for (int i = 2; i <= value; i += 2) {
    tbst2.removeThreadedBinaryTreeNode(i);
    cout << tbst2 << endl;
  }
  cout << "End of Test Three" << endl;
}

void testPrintCopyConstructor() {
  BinaryTreeInterface tbst(40);
  BinaryTreeInterface tbst2(tbst);
  cout << tbst2 << endl;
  cout << "End of Test Four" << endl;
}

void testContain() {
  BinaryTreeInterface tbst(20);
  assert(tbst.contains(8));
}
void testRootDelete() {
  BinaryTreeInterface tbst(3);
  BinaryTreeInterface tbst2(tbst);
  tbst2.removeThreadedBinaryTreeNode(2);
  cout << tbst2 << endl;
  cout << "End of Test five" << endl;
}

void testAdd() {
  BinaryTreeInterface tbst(10);
  tbst.addTreeNode(12);
  BinaryTreeInterface tbst2(tbst);
  //tbst2.addTreeNode(12);
  cout << tbst2 << endl;
  cout << "End of Test five" << endl;
}

int main() {

  ass5Requirments();
  cout << endl;
  testRemoveAllEvens();
  cout << endl;
  testRootDelete();
  cout << endl;
  testAdd();
  cout << endl;
}
