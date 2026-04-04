#ifndef ELECTRONICS_H
#define ELECTRONICS_H
#include "Product.h"

class Electronics : public Product {
private:
    int warranty; 
public:
    Electronics(std::string n, int p, int s, int w);
    
    //Overrides display() to include specific warranty information.
    void display() override;
};
#endif