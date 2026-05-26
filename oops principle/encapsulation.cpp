#include <iostream>
using namespace std;

class Car {
private:
    int speed;

public:
    Car() {
        speed = 0;
    }

    void accelerate(int value) {
        if(value > 0) {
            speed += value;
        }
    }

    int getSpeed() {
        return speed;
    }
};

int main() {
    Car c;

    c.accelerate(50);

    cout << c.getSpeed();
}