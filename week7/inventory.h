#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "item.h" // could also use std::pair for this??
#include <vector>

class Inventory {
public:
  Inventory(std::vector<Item> items);
  virtual ~Inventory();

private:
  std::vector<Item> items;
  bool isSoldOut(Item item);
  void addItem(Item item, int quantity);
  void removeItem(Item item, int quantity);
  void reset();
};

#endif /* INVENTORY_H_ */
