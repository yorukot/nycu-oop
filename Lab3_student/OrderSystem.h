#ifndef ORDERSYSTEM_H
#define ORDERSYSTEM_H
#include <vector>
#include <string>
#include "Product.h"

class OrderSystem {
private:
    std::vector<Product*> inventory; 
    int totalSales;
public:
    OrderSystem();

    // Adds a product pointer to the inventory. 
    void addProduct(Product* p);

    /*Searches for a product by name and processes the sale.
     * Prints "[product_name] Sold out!!!" immediately if stock is zero.
     */
    void processOrder(std::string prodName, int amount);

    // Prints a summary of all items in inventory and total units sold. 
    void printSummary();
    
    ~OrderSystem();
};
#endif