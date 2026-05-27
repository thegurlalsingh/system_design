#include <iostream>
using namespace std;

class RideService {
public:
    void bookRide(string paymentType) {

        cout << "Ride booked\n";

        if(paymentType == "card") {
            cout << "Card payment processed\n";
        }
        else if(paymentType == "upi") {
            cout << "UPI payment processed\n";
        }

        cout << "Notification sent\n";
    }
};

int main() {

    RideService r;

    r.bookRide("upi");
}