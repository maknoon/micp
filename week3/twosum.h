#ifndef TWOSUM_H_
#define TWOSUM_H_

#include <vector>

class TwoSum {
public:
  TwoSum();
  virtual ~TwoSum();

  std::vector<std::vector<int>> getTwoSum(std::vector<int>& nums, int target);
};

#endif /* TWOSUM_H_ */
