#include <iostream>
using namespace std;

class Vehicle {
public:
    int speed;

    void stop() {
        cout << "Vehicle stopped\n";
    }
};

class Car : public Vehicle {
public:
    void openSunroof() {
        cout << "Sunroof opened\n";
    }
};

int main() {
    Car c;

    c.speed = 100;

    c.stop();

    c.openSunroof();
}