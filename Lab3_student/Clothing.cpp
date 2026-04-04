#include <iostream>
#include "Clothing.h"

Clothing::Clothing(std::string n, int p, int s, std::string sz) : Product(n, p, s), size(sz) {}

void Clothing::display() {
    Product::display();
    std::cout << " | Size: " << size << std::endl;
}
