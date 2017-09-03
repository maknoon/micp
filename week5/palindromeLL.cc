/* palindromeLL.cc
 * author: connie
 *
 * LINKED LIST PALINDROME
 * checks if a LL is a palindrome.
 */

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <stack>
#include <cmath>
#include <cassert>

using namespace std;

//== DEFINITIONS
struct node
{
  char data;
  node *next;
  node(char d) : data(d), next(NULL) {}
};

//== DECLARATIONS
void insert(node*& head, int key);
void deleteLL(node*& head);
bool palindromeLL(node *head);

//== FUNCTIONS
/*
 * void insert(node*& head, int key)
 * inputs: head - the LL node to insert the new node in front of
           key - value of the new node to be inserted
 * output: none
 * notes: helper function to insert a new node into the LL, as the new head node
 */
void insert(node*& head, char d)
{
  node *curr = new node(d);
  curr->next = head;

  head = curr;
}

/*
 * void deleteLL(node*& head)
 * inputs: head - the start of the entire LL that we want to delete
 * output: none
 * notes: helper function to prevent memory leaks
 */
void deleteLL(node*& head)
{
  node *del = head;

  while (del) {
    head = head->next;
    delete del;
    del = head;
  }

  head = NULL;
}


/*
 * bool palindromeLL(node *head)
 * inputs: *head - pointer to the starting node of the LL
 * output: T if the LL is a palindrome, F if not
 * notes: main solution function
 */
bool palindromeLL(node *head)
{
  // case: null or only one -> is a palindrome
  if (!head) throw invalid_argument("null pointer detected");
  if (!head->next) return true;

  // find the middle node of the LL by using a faster 'runner' node
  // since runner goes 2x as fast as mid, by the time runner is at the end,
  // the mid node will be in the middle of the LL
  node *mid = head;
  node *runner = head;
  while (runner && runner->next) {
    runner = runner->next->next;
    mid = mid->next;
  }

  // use a stack for the first half of LL
  stack<char> palindrome;
  node *c;
  for (c = head; c != mid; c = c->next) palindrome.push(c->data);
  if (runner) c = c->next; // SKIP the middle element if size of LL is odd

  // check remaining half to verify palindrome
  while (c->next) {
      if (c->data != palindrome.top()) return false;
      palindrome.pop();
      c = c->next;
  }

  // if we reach this point then we only need to verify the first and last elements
  return (c->data == palindrome.top());
}

/*
 * for testing purposes
 */
void tests(void) {
  // TEST 1 - empty case
  // EXPECTED: true
  cout << "TEST 1: null" << endl;
  try {
    palindromeLL(NULL);
  } catch (...) { }; // program will throw an exception for the null
  cout << "test passed" << endl;

  // TEST 2 - simplest pass case (even)
  // EXPECTED: true
  cout << "TEST 2: aa" << endl;
  node *n1 = new node('a');
  insert(n1,'a');
  assert(palindromeLL(n1)==true);
  deleteLL(n1);
  cout << "test passed" << endl;

  // TEST 3 - simplest pass case (odd)
  // EXPECTED: true
  cout << "TEST 3: aBa" << endl;
  node *n2 = new node('a');
  insert(n2,'B');
  insert(n2,'a');
  assert(palindromeLL(n2)==true);
  deleteLL(n2);
  cout << "test passed" << endl;

  // TEST 4 - simplest fail case (even)
  // EXPECTED: false
  cout << "TEST 4: Aa" << endl;
  node *n3 = new node('a');
  insert(n3,'A');
  assert(palindromeLL(n3)==false);
  deleteLL(n3);
  cout << "test passed" << endl;

  // TEST 5 - simplest fail case (odd)
  // EXPECTED: false
  cout << "TEST 5: Aaa" << endl;
  node *n4 = new node('a');
  insert(n4,'a');
  insert(n4,'A');
  assert(palindromeLL(n4)==false);
  deleteLL(n4);
  cout << "test passed" << endl;

  // TEST 6 - space sensitive / larger case
  // EXPECTED: true
  cout << "TEST 5: amor e roma" << endl;
  node *n5 = new node('a');
  insert(n5,'m');
  insert(n5,'o');
  insert(n5,'r');
  insert(n5,' ');
  insert(n5,'e');
  insert(n5,' ');
  insert(n5,'r');
  insert(n5,'o');
  insert(n5,'m');
  insert(n5,'a');
  assert(palindromeLL(n5)==true);
  deleteLL(n5);
  cout << "test passed" << endl;
}

int main(void)
{
  tests();
  return 0;
}
