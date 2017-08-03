#include "twosum.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <unordered_map>

/* DEFINITIONS &C */
TwoSum::TwoSum() {}
TwoSum::~TwoSum() {}

/* FUNCTIONS */
/*
 * vector<int> twoSum(vector<int> nums, int target)
 * inputs: nums - the array to evaluate for two numbers
           target - the number that is the desired sum of two values in nums
 * output: an array with two values from nums that add up to target
 * notes:
 */
std::vector<int> twoSum(std::vector<int> nums, int target) {
  // take care of the null / empty nums cases first
  if (nums.size() == 0) return {};

  // use the O(n) hash map solution discussed in lecture - easy to
  // find what we want as we are iterating thru the array as well
  std::unordered_map<int,int> diffs;
  int diff;
  for (int i = 0; i < nums.size(); i++) {
    // calculate the difference between the sum and the value we are looking at
    diff = target - nums[i];
    // if the difference has already been stored in the map, we are done
    if (diffs[diff] == nums[i]) return {diff, nums[i]};
    // otherwise keep storing the value and differences in the table
    diffs[nums[i]] = diff;
  }

  // if we reach this point then we are unsuccessful, return empty array
  return {};
}
