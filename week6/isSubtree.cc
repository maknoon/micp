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
#include <cmath>
#include <cassert>

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
void deleteTree(tNode*& root);
bool isSameTree(tNode *t1, tNode *t2);
bool isSubtree(tNode *s, tNode *t);

//== FUNCTIONS
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
  // base case + null cases
  if (!s && !t) return true;
  else if (!s || !t) return false;

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
  cout << "TEST 1: t={1}, s={1}" << endl;
  tNode *t1 = new tNode(1);
  tNode *s1 = new tNode(1);
  assert(isSubtree(s1,t1)==true);
  deleteTree(t1);
  deleteTree(s1);
  cout << "test passed" << endl;

  // TEST 3 - simplest fail (one null tree)
  cout << "TEST 1: t={1}, s=NULL" << endl;
  tNode *t2 = new tNode(1);
  assert(isSubtree(NULL,t2)==false);
  deleteTree(t2);
  cout << "test passed" << endl;

  // TEST 4 - complex pass w/ no duplicate numbers
  cout << "TEST 1: t={1,null,2,10,3}, s={2,10,3}" << endl;
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
  cout << "TEST 1: t={1,null,2,10,3}, s={2,null,3}" << endl;
  // TODO

  // TEST 6 - complex pass w/ duplicate numbers
  cout << "TEST 1: t={2,null,2,10,3}, s={2,10,3}" << endl;
  // TODO


  // TEST 7 - complex fail w/ duplicate numbers
  cout << "TEST 1: t={2,null,2,10,3}, s={2,null,3}" << endl;
  // TODO
}

int main(void)
{
  tests();
  return 0;
}
