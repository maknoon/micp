/* threesum.cc
 * author: connie
 *
 * THREE SUM
 *
 */

// TODO: these includes don't seem to be working in new environment rn
//       get rid of all the std:: at some point when I figure this out
#include "twosum.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <unordered_map>

using namespace std;

//== DECLARATIONS
TwoSum twosum;

//== DEFINITIONS
//== FUNCTIONS


/*
 * for testing purposes
 */
void tests(void) {

  // TEST 1
  vector<int> v1 = {1,2,3}; int t1 = 5;
  vector<int> a1 = twosum.getTwoSum(v1,t1);
  assert(a1[0]==2); assert(a1[1]==3);
  cout << "test1 passed" << endl;

  // TEST 2
  vector<int> v2 = {6,2,3}; int t2 = 8;
  vector<int> a2 = twosum.getTwoSum(v2,t2);
  assert(a2[0]==6); assert(a2[1]==2);
  cout << "test2 passed" << endl;
}


int main(void)
{
  tests();

  return 0;
}
