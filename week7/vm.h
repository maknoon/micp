#ifndef VENDINGMACHINE_H_
#define VENDINGMACHINE_H_

#include "inventory.h"

class VendingMachine {
public:
  VendingMachine(double balance, Inventory inventory);
  virtual ~VendingMachine();

  void cancel();
  void recvMoney(int amount);
  int selectItem(int itemID);
  void reset();

private:
  double totalBalance;
  Inventory inventory;

  void issueRefund();
  double getTotalBalance();
};

#endif /* VENDINGMACHINE_H_ */
