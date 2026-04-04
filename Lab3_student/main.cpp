#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Clothing.h"
#include "Electronics.h"
#include "OrderSystem.h"

using namespace std;

int main() {
    OrderSystem system;
    int n;

    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        char type;
        cin >> type;

        if (type == 'E') {
            string name;
            int price;
            int stock, warranty;
            cin >> name >> price >> stock >> warranty;
            system.addProduct(new Electronics(name, price, stock, warranty));
        } 
        else if (type == 'C') { 
            string name;
            int price;
            int stock;
            string size;
            cin >> name >> price >> stock >> size;
            system.addProduct(new Clothing(name, price, stock, size));
        } 
        else if (type == 'P') {
            string name;
            int amount;
            cin >> name >> amount;
            system.processOrder(name, amount);
        }
    }

    system.printSummary();

    return 0;
}