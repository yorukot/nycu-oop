#include <iostream>
#include "Electronics.h"

/*
  * HINT: Constructor Chaining.
  * We call the Base Class constructor first to initialize inherited members (name, price, stock),
  * then initialize the specific member of this class (warranty).
  */
Electronics::Electronics(std::string n, int p, int s, int w) : Product(n, p, s), warranty(w) {}

/*
  * HINT: Function Overriding.
  * Use 'Product::display()' to reuse the base class logic, 
  * then add the specific warranty information.
  */
void Electronics::display() {
    Product::display();
    std::cout << " | Warranty: " << warranty << " months" << std::endl;
}
