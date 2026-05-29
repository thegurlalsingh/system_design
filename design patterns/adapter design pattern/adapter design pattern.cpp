#include <iostream>
using namespace std;

class Notification {
public:
    virtual void send() = 0;
};

class WhatsAppAPI {
public:
    void sendMessage() {
        cout << "WhatsApp Message\n";
    }
};

class WhatsAppAdapter : public Notification {

private:
    WhatsAppAPI* api;

public:

    WhatsAppAdapter(WhatsAppAPI* api) {
        this->api = api;
    }

    void send() override {
        api->sendMessage();
    }
};

WhatsAppAPI api;

Notification* n =
    new WhatsAppAdapter(&api);

n->send();