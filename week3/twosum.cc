/* twosum.cc
 * author: connie
 *
 * TWO SUM
 * week3 in-lecture problem. given an input array and a target number,
 * return an array with two values from the input array that sum to the target.
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
TwoSum::TwoSum() {}
TwoSum::~TwoSum() {}

//== DEFINITIONS

//== FUNCTIONS
/*
 * vector<vector<int>> getTwoSum(vector<int> nums, int target)
 * inputs: nums - the array to evaluate for two numbers
           target - the number that is the desired sum of two values in nums
 * output: an array of pairs from nums that add up to target
 * notes:
 */
vector<vector<int>> TwoSum::getTwoSum(vector<int>& nums, int target) {
  // take care of the null / empty nums cases first
  if (nums.size() == 0) return {};

  // use the O(n) hash map solution discussed in lecture - easy to
  // find what we want as we are iterating thru the array as well
  map<int,int> diffs;
  int diff;
  vector<vector<int>> twosums = {};

  for (int i = 0; i < nums.size(); i++) {
    // calculate the difference between the sum and the value we are looking at
    diff = target - nums[i];
    // if the difference has already been stored in the map, add it to the twosums
    if (diffs.find(diff) != diffs.end()) twosums.push_back({diff, nums[i]});
    // otherwise keep storing the value and differences in the table
    diffs[nums[i]] = diff;
  }

  return twosums;
}
