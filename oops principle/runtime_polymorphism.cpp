#include <iostream>
using namespace std;

class Vehicle {
public:
    virtual void start() {
        cout << "Vehicle starting\n";
    }
};

class Car : public Vehicle {
public:
    void start() override {
        cout << "Car starts with button\n";
    }
};

class Bike : public Vehicle {
public:
    void start() override {
        cout << "Bike starts with kick\n";
    }
};

int main() {
    Vehicle* v1 = new Car();
    Vehicle* v2 = new Bike();

    v1->start();
    v2->start();
}