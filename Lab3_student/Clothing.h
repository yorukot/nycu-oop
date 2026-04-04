#ifndef CLOTHING_H
#define CLOTHING_H
#include "Product.h"

class Clothing : public Product {
private:
    std::string size;
public:
    Clothing(std::string n, int p, int s, std::string sz);

    //Overrides display() to include specific size information.
    void display() override;
};
#endif