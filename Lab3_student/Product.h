#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product {
protected:
    std::string name;
    int price;
    int stock;

public:
    Product();
    Product(std::string n, int p, int s);
    virtual ~Product();

    /* Checks if stock is sufficient and deducts the amount.
     * return true if successful, false if stock is insufficient.
     */
    bool purchase(int amount);

    // Prints the basic product information (Name, Price, Stock).
    virtual void display();

    // return the name of the product.
    std::string getName();
};
#endif