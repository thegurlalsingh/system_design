#include <iostream>
using namespace std;

class Command {
public:
    virtual void execute() = 0;
};

class TV {
public:
    void turnOn() {
        cout << "TV ON\n";
    }
};

class TurnOnCommand : public Command {

private:
    TV* tv;

public:

    TurnOnCommand(TV* tv) {
        this->tv = tv;
    }

    void execute() override {
        tv->turnOn();
    }
};

class Remote {

private:
    Command* command;

public:

    Remote(Command* command) {
        this->command = command;
    }

    void pressButton() {
        command->execute();
    }
};

int main() {

    TV tv;

    Command* cmd = new TurnOnCommand(&tv);

    Remote remote(cmd);

    remote.pressButton();
}