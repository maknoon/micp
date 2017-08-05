/* threesum.cc
 * author: connie
 *
 * THREE SUM
 *
 */
#include "twosum.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

//== DECLARATIONS
TwoSum twosum;
vector<vector<int>> getThreeSum(vector<int>& v);
void print_answer(vector<vector<int>> v); // for debugging

//== DEFINITIONS
//== FUNCTIONS
/*
 * vector<vector<int>> getThreeSum(vector<int>& v)
 * input: v - the array to find triplet threesum arrays from
 * output: an array of triplets (i.e. arrays w/ 3 values) with the desired
           threesum from the input array
 * notes: the main solution function
 */
vector<vector<int>> getThreeSum(vector<int>& v)
{
  // if v doesn't fulfill basic threesum requirements, return an empty arr
  if (v.size() < 3) return {};

  // create a map to hold existing threesums
  map<int,vector<int>> threesums;
  vector<vector<int>> threesum_result = {};
  vector<int> twosum_result; int twosum_target;

  // next, iterate through the array looking for threesums
  for (int i = 0; i < v.size(); i++) {
    
    // first check if it's a duplicate using map
    if (threesums.find(v[i]) == threesums.end()) {
      twosum_target = v[i];
      v.erase(v.begin()+i); // remove the value from v before giving it to twosum
      twosum_result = twosum.getTwoSum(v, 0 - twosum_target); // we want the additive inverse

      // add this obtained triplet to the return array if it exists
      if (twosum_result.size() > 0) {
        threesum_result.push_back({twosum_target,twosum_result[0],twosum_result[1]});
      }

      v.push_back(twosum_target); // readd the value to the original array
      threesums[twosum_target] = twosum_result; // update the map
    }
  }

  return threesum_result;
}

/*
 * for debugging purposes
 */
void print_answer(vector<vector<int>> v) {
  for (int i = 0; i < v.size(); i++) {
    cout << "triplet " << i << ": ";
    for (int j = 0; j < v[i].size(); j++) {
      cout << v[i][j] << " ";
    }
    cout << " " << endl;
  }
  cout << " " << endl;
}

/*
 * for testing purposes
 */
void tests(void) {
  // TEST 1
  vector<int> v1 = {-1,0,1,2,-1,-4};
  vector<vector<int>> a1 = getThreeSum(v1);
  print_answer(a1);

  // TEST 2
  vector<int> v2 = {};
  vector<vector<int>> a2 = getThreeSum(v2);
  print_answer(a2);
}


int main(void)
{
  tests();

  return 0;
}
