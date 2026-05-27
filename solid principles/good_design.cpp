#include <iostream>
using namespace std;

class PaymentService {
public:
    virtual void pay() = 0;
};

class CardPayment : public PaymentService {
public:
    void pay() override {
        cout << "Card Payment Processed\n";
    }
};

class UpiPayment : public PaymentService {
public:
    void pay() override {
        cout << "UPI Payment Processed\n";
    }
};

class NotificationService {
public:
    void sendNotification() {
        cout << "Notification Sent\n";
    }
};

class RideManager {
private:
    PaymentService* payment;
    NotificationService notification;

public:

    RideManager(PaymentService* payment) {
        this->payment = payment;
    }

    void completeRide() {

        cout << "Ride Booked Successfully\n";

        payment->pay();

        notification.sendNotification();
    }
};

int main() {

    PaymentService* payment = new UpiPayment();

    RideManager ride(payment);

    ride.completeRide();
}