#include <iostream>
#include <vector>

using namespace std;

class Coffee {
public:
    virtual int cost() = 0;
};

class SimpleCoffee : public Coffee {
public:
    int cost() override {
        return 100;
    }
};

class CoffeeDecorator : public Coffee {

protected:
    Coffee* coffee;

public:

    CoffeeDecorator(Coffee* coffee) {
        this->coffee = coffee;
    }
};

class MilkDecorator : public CoffeeDecorator {

public:

    MilkDecorator(Coffee* coffee)
        : CoffeeDecorator(coffee) {}

    int cost() override {
        return coffee->cost() + 20;
    }
};

class SugarDecorator : public CoffeeDecorator {

public:

    SugarDecorator(Coffee* coffee)
        : CoffeeDecorator(coffee) {}

    int cost() override {
        return coffee->cost() + 10;
    }
};

int main() {

    Coffee* coffee = new SimpleCoffee();

    coffee = new MilkDecorator(coffee);

    coffee = new SugarDecorator(coffee);

    cout << coffee->cost();
}