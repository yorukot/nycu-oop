#include <iostream>
#include "OrderSystem.h"


OrderSystem::OrderSystem() : totalSales(0) {}

void OrderSystem::addProduct(Product* p) {
    inventory.push_back(p);
}

void OrderSystem::processOrder(std::string prodName, int amount) {
    /* 
    * TODO: Search for the product by name in the inventory.
    * 1. Iterate through the inventory vector.
    * 2. If the name matches and stock is sufficient, call purchase() and add the amount to totalSales.
    * 3. If stock is insufficient, print: "[Item Name] Sold out!!!"
    * HINT:Call Function: Use 'inventory[i]->getName()' to check the product name.
    * HINT:Call Function: Use 'inventory[i]->purchase(amount)' to attempt the sale.
    */
    for (auto p : inventory) {
        if (p->getName() == prodName) {
            if (p->purchase(amount)) {
                totalSales += amount;
            } else {
                std::cout << prodName << " Sold out!!!" << std::endl;
            }
            return;
        }
    }
}

void OrderSystem::printSummary() {
    std::cout << "--- Inventory Summary ---" << std::endl;
    for (auto p : inventory) {
        // HINT: Because display() is virtual, the correct version (Electronics or Clothing) 
        p->display();
    }
    std::cout << "Total items sold: " << totalSales << std::endl;
}

// Cleanup memory to prevent leaks
OrderSystem::~OrderSystem() {
    for (auto p : inventory) delete p;
}
