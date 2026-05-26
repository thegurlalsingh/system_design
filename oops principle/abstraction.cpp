#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual void start() = 0;
};

class Car : public Vehicle {
public:
    void start() override {
        cout << "Car started using push button";
    }
};

int main() {
    Vehicle* v = new Car();

    v->start();
}