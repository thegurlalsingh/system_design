#include <iostream>
using namespace std;


class Payment {

public:

    void makePayment() {

        validate();

        processPayment();

        sendReceipt();
    }

    virtual void processPayment() = 0;

    void validate() {
        cout << "Validating User\n";
    }

    void sendReceipt() {
        cout << "Sending Receipt\n";
    }
};

class UpiPayment : public Payment {

public:

    void processPayment() override {
        cout << "UPI Payment\n";
    }
};

class CardPayment : public Payment {

public:

    void processPayment() override {
        cout << "Card Payment\n";
    }
};

int main() {

    Payment* p = new UpiPayment();

    p->makePayment();
}

