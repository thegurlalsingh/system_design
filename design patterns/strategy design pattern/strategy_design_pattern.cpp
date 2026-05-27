# include<iostream>
using namespace std;

class Talkable {
public:
    virtual void talk() = 0;

    virtual ~Talkable() {}
};

class Walkable {
public:
    virtual void walk() = 0;

    virtual ~Walkable() {}
};

class Flyable {
public:
    virtual void fly() = 0;

    virtual ~Flyable() {}
};

class NormalTalk : public Talkable {
public:
    void talk() override {
        cout << "Robot is talking\n";
    }
};

class NoTalk : public Talkable {
public:
    void talk() override {
        cout << "Cannot talk\n";
    }
};

class NormalWalk : public Walkable {
public:
    void walk() override {
        cout << "Robot is walking\n";
    }
};

class NoWalk : public Walkable {
public:
    void walk() override {
        cout << "Cannot walk\n";
    }
};

class NormalFly : public Flyable {
public:
    void fly() override {
        cout << "Robot is flying\n";
    }
};

class NoFly : public Flyable {
public:
    void fly() override {
        cout << "Cannot fly\n";
    }
};

class Robot {

protected:

    Talkable* talkBehavior;
    Walkable* walkBehavior;
    Flyable* flyBehavior;

public:

    Robot(
        Talkable* t,
        Walkable* w,
        Flyable* f
    ) {
        talkBehavior = t;
        walkBehavior = w;
        flyBehavior = f;
    }

    void performTalk() {
        talkBehavior->talk();
    }

    void performWalk() {
        walkBehavior->walk();
    }

    void performFly() {
        flyBehavior->fly();
    }

    virtual ~Robot() {}
};

class CompanionRobot : public Robot {

public:

    CompanionRobot() : Robot(new NormalTalk(), new NormalWalk(), new NoFly()) { }
};