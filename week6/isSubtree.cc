/* isSubtree.cc
 * author: connie
 *
 * IS SUBTREE
 * Checks if a binary tree T is a subtree of binary tree S.
 * A subtree is defined as have the same structure as another tree's root
 * or child nodes -
 * i.e., T does not necessarily have to be a node actually in tree S.
 *
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <queue>

using namespace std;

//== DEFINITIONS
struct tNode // tNode = binary treeNode
{
  int data;
  tNode *left;
  tNode *right;
  tNode(int d) : data(d), left(NULL), right(NULL) {}
};

//== DECLARATIONS
tNode* findParent(tNode*& root, int node);
tNode* buildTree(string nodeData);
void deleteTree(tNode*& root);
bool isSameTree(tNode *t1, tNode *t2);
bool isSubtree(tNode *s, tNode *t);

//== FUNCTIONS
/*
 * tNode* findParent(tNode* root, int node)
 * inputs: root - pointer to the root node of the tree
           node - integer indicating position of the parent in the tree
 * output: pointer to the node we are looking for
 * notes: iterative BFS helper that traverses tree from root to find a node

tNode* findParent(tNode*& root, int node)
{
  if (node == 0) return root;

  // vars used for traversal
  queue<tNode*> tree;
  int count = 0;
  tNode* found = root;

  // BFS until we reach the index of the node
  tree.push(root);
  while(!tree.empty()) {
    found = tree.back();
    tree.pop();
    count++; // this is the index of the treenode we are at
    if (count == node) break;
    else {
      if (found->left) tree.push(found->left);
      if (found->right) tree.push(found->right);
    }
  }

  return found;
}
*/

/*
 * tNode* buildTree(string nodeData)
 * inputs: nodeData - vector of chars corresponding to data in the intended tree
 * output: pointer to the root node of the tree constructed from nodeData
 * notes: takes a vector of chars and builds a binary tree from it.
          ** assume nodeData(0) is never null **

tNode* buildTree(string nodeData)
{
  // if array is empty, we don't have a tree
  if (nodeData.size() == 0) return NULL;

  int parent = 0;
  int i = 0;
  int delimiter = nodeData.find(",");

  // assume root is always not null
  string num = nodeData.substr(0,delimiter);
  tNode* root = new tNode(stoi(num));

  // reset the string
  nodeData.erase(0, delimiter+1); // +1 to erase the comma as well
  num.resize(0);

  // otherwise iterate and build our binary tree
  while (delimiter != string::npos) {
    num = nodeData.substr(0,delimiter);

    // 'x' indicates that it is an empty node
    if (num != "x") {
      tNode* newNode = new tNode(stoi(num)); // construct new node w/ data

      // Find newNode's parent and attach:
      // because every node (regardless null or not) is described by nodeData,
      // we can just increment the parent every 2 nodes instead of doing math
      parent = (i % 2 == 1) ? parent : parent + 1;
      tNode* parentNode = findParent(root, parent);
      if (i % 2 == 1) parentNode->left = newNode;
      else parentNode->right = newNode;
     }

     nodeData.erase(0,delimiter+1);
     num.resize(0);
     i++;
  }

  return root;
}
*/

/*
 * void deleteTree(tNode*& root)
 * inputs: root - root node of the tree that we want to delete
 * output: none
 * notes: post-order traversal helper. don't need those memory leaks :P
 */
void deleteTree(tNode*& root)
{
  if (root) {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = NULL;
  }
}

/*
 * bool isSameTree(tNode *t1, tNode *t2)
 * inputs: *t - pointer to the root of first tree
           *s - pointer to the root of second tree
 * output: true if t1 and t2 are structurally the same, false otherwise
 * notes: helper function to validate tree structure
 */
bool isSameTree(tNode *t1, tNode *t2)
{
  // base case: both null
  if (!t1 && !t2) return true;

  else {
    // if either node is null, then t1 and t2 are structurally different
    if (!t1 || !t2) return false;
    // next validate that the contents of the node are the same
    if (t1->data == t2->data) {
      // only recurse if we get this far
      return isSameTree(t1->left, t2->left) && isSameTree(t1->right, t2->right);
    }
  }

  // shouldn't ever get this far, but in case we do, return false to be safe
  return false;
}

/*
 * bool isSubtree(tNode *s, tNode *t)
 * inputs: *t - pointer to the root of the subtree we are validating
           *s - pointer to the root of the tree we are using as reference
 * output: true if t is a subtree of s, false otherwise
 * notes: main solution function
 */
bool isSubtree(tNode *t, tNode *s)
{
  // base cases
  if (!t) return true; // T is null -> it is always a subtree
  if (!s) return false; // S is null (& T is not) -> T can never be a subtree

  else {
    // only check isSameTree if the node data is the same
    if ((s->data == t->data) && isSameTree(s,t)) return true;

    // otherwise:
    // recurse on L and R children of s to find another suitable node
    // as long as either side comes up with a matching subtree, we are done
    else return (isSubtree(t, s->left) || isSubtree(t, s->right));
  }
}

/*
 * for testing purposes
 */
void tests(void) {
  // TODO write a helper function to construct complex trees from an array lol

  // TEST 1 - empty case
  cout << "TEST 1: t=NULL, s=NULL" << endl;
  assert(isSubtree(NULL,NULL)==true);
  cout << "test passed" << endl;

  // TEST 2 - simplest pass (equal trees)
  cout << "TEST 2: t={1}, s={1}" << endl;
  tNode *t1 = new tNode(1);
  tNode *s1 = new tNode(1);
  assert(isSubtree(s1,t1)==true);
  deleteTree(t1);
  deleteTree(s1);
  cout << "test passed" << endl;

  // TEST 3 - simplest fail (one null tree)
  cout << "TEST 3: t={1}, s=NULL" << endl;
  tNode *t2 = new tNode(1);
  assert(isSubtree(t2,NULL)==false);
  deleteTree(t2);
  cout << "test passed" << endl;

  // TEST 4 - complex pass w/ no duplicate numbers
  cout << "TEST 4: t={1,null,2,10,3}, s={2,10,3}" << endl;
  tNode *t3 = new tNode(1);
  t3->right = new tNode(2);
  t3->right->left = new tNode(10);
  t3->right->right = new tNode(3);
  tNode *s3 = new tNode(2);
  s3->left = new tNode(10);
  s3->right = new tNode(3);
  assert(isSubtree(s3,t3)==true);
  deleteTree(t3);
  deleteTree(s3);
  cout << "test passed" << endl;

  // TEST 5 - complex fail w/ no duplicate numbers
  cout << "TEST 5: t={1,null,2,10,3}, s={2,null,3}" << endl;
  tNode *t4 = new tNode(1);
  t4->right = new tNode(2);
  t4->right->left = new tNode(10);
  t4->right->right = new tNode(3);
  tNode *s4 = new tNode(2);
  s4->right = new tNode(3);
  assert(isSubtree(s4,t4)==false);
  deleteTree(t4);
  deleteTree(s4);
  cout << "test passed" << endl;

  // TEST 6 - complex pass w/ duplicate numbers
  cout << "TEST 6: t={2,null,2,10,3}, s={2,10,3}" << endl;
  tNode *t5 = new tNode(2);
  t5->right = new tNode(2);
  t5->right->left = new tNode(10);
  t5->right->right = new tNode(3);
  tNode *s5 = new tNode(2);
  s5->left = new tNode(10);
  s5->right = new tNode(3);
  assert(isSubtree(s5,t5)==true);
  deleteTree(t5);
  deleteTree(s5);
  cout << "test passed" << endl;


  // TEST 7 - complex fail w/ duplicate numbers
  cout << "TEST 7: t={2,null,2,10,3}, s={2,null,3}" << endl;
  tNode *t6 = new tNode(2);
  t6->right = new tNode(2);
  t6->right->left = new tNode(10);
  t6->right->right = new tNode(3);
  tNode *s6 = new tNode(2);
  s6->right = new tNode(3);
  assert(isSubtree(s6,t6)==false);
  deleteTree(t6);
  deleteTree(s6);
  cout << "test passed" << endl;
}

int main(void)
{
  tests();
  return 0;
}
