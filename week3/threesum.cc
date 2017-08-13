/* threesum.cc
 * author: connie
 *
 * THREE SUM
 * Given an input array S of integers, find all unique triplets (i.e. array of 3
 * values from S) for which the values of the triplets add to 0.
 * Ex. S = {0,1,1,-2,-1} returns {{0,1,-1},{1,1,-2}}
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
vector<int> build_arr(vector<int>& v, int i); // helper
vector<vector<int>> getThreeSum(vector<int>& v);
void print_answer(vector<vector<int>> v); // for debugging
void print_arr(vector<int> v); // for debugging

//== DEFINITIONS
//#define DEBUG

//== FUNCTIONS
/*
 * for debugging
 */
void print_arr(vector<int> v) {
  if (v.size() == 0) { cout << "empty array!" << endl; return; }

  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << " " << endl;
}

void print_arr_of_arr(vector<vector<int>> v) {
  if (v.size() == 0) { cout << "empty array!" << endl; return; }

  for (int i = 0; i < v.size(); i++) {
    cout << "triplet " << i << ": ";
    for (int j = 0; j < 3; j++) {
      cout << v[i][j] << " ";
    }
    cout << " " << endl;
  }
  cout << " " << endl;
}

/*
 * vector<int> build_arr(vector<int>& v, int i)
 * inputs: v - array to build a new array from
           i - index to exclude from the new array built from v
 * output: a new array that has every value in v after v[i]
 * notes: could have put this in the main function but wanted to declutter
 */
vector<int> build_arr(vector<int>& v, int i) {
  vector<int> new_v;
  new_v.assign(v.begin()+i,v.end());

  return new_v;
}

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
  map<int,int> threesums;
  vector<vector<int>> threesum_result = {};
  // for twosum operations
  vector<int> twosum_arr;
  int twosum_target;
  vector<vector<int>> twosum_result;

  // next, iterate through the array looking for threesums
  for (int i = 0; i < v.size(); i++) {

    twosum_target = v[i]; // NOTE: we want the additive inverse of this
    twosum_arr = build_arr(v,i); // build twosum_arr w/ every value except v[i]

    // find all twosums on the current value inside twosum_arr
    twosum_result = twosum.getTwoSum(twosum_arr, 0-twosum_target);

    // add obtained triplet to the return array (if it exists)
    if (twosum_result.size() > 0) {
      for (int j = 0; j < twosum_result.size(); j++) {
        // check if it's a duplicate!
        if (threesums.find(v[i]) == threesums.end()) {
          threesum_result.push_back({twosum_target,twosum_result[j][0],
            twosum_result[j][1]});
          // update the map with the triplet
          threesums[twosum_target] = 1;
          threesums[twosum_result[j][0]] = 1;
          threesums[twosum_result[j][1]] = 1;
        }
      }
    }
  }

  return threesum_result;
}

/*
 * for testing purposes
 */
void tests(void) {
  // TEST 1 - empty case
  // EXPECTED: empty array returned
  cout << "TEST 1: {}" << endl;
  vector<int> v1 = {};
  vector<vector<int>> a1 = getThreeSum(v1);
  print_arr_of_arr(a1);

  // TEST 2 - array with duplicates & more than one unique triplet
  // EXPECTED: two unique triplets returned
  cout << endl << "TEST 2: {-1,0,1,2,-1,-4}" << endl;
  vector<int> v2 = {-1,0,1,2,-1,-4};
  vector<vector<int>> a2 = getThreeSum(v2);
  print_arr_of_arr(a2);

  // TEST 3 - array that does not have enough elements to form triplet
  // EXPECTED: empty array returned
  cout << "TEST 3: {1,2}" << endl;
  vector<int> v3 = {1,2};
  vector<vector<int>> a3 = getThreeSum(v3);
  print_arr_of_arr(a3);

  // TEST 4 - array with no unique triplets
  // EXPECTED: empty array returned
  cout << endl << "TEST 4: {1,2,3}" << endl;
  vector<int> v4 = {1,2,3};
  vector<vector<int>> a4 = getThreeSum(v4);
  print_arr_of_arr(a4);

  // TEST 5 - array with one unique triplet
  // EXPECTED: one unique triplet returned
  cout << endl << "TEST 5: {-1,-2,3}" << endl;
  vector<int> v5 = {-1,-2,3};
  vector<vector<int>> a5 = getThreeSum(v5);
  print_arr_of_arr(a5);

  // TEST 6 - array with one unique triplet but possible duplicate triplet
  // EXPECTED: one unique triplet returned
  cout << "TEST 6: {5600,-5600,0,0}" << endl;
  vector<int> v6 = {5600,-5600,0,0};
  vector<vector<int>> a6 = getThreeSum(v6);
  print_arr_of_arr(a6);
}


int main(void)
{
  tests();

  return 0;
}
