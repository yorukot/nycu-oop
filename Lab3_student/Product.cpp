#include <string>
#include <iostream>
#include "Product.h"


Product::Product() : name("Unknown"), price(0), stock(0) {}

Product::Product(std::string n, int p, int s) : name(n), price(p), stock(s) {}

Product::~Product() {}

bool Product::purchase(int amount) {
    if (stock >= amount) {
        stock -= amount;
        return true;
    }
    return false;
}
/*
    * HINT: The 'virtual' keyword is essential for Polymorphism. 
    * It allows the program to decide which display() function to call at runtime 
    * based on the actual object type, even when using a Product pointer.
    * Derived classes MUST override this function to provide specific details.
    */
void Product::display() {
    std::cout << "[Product] " << name << " | Price: " << price << " | Stock: " << stock;
}

std::string Product::getName() { return name; }
