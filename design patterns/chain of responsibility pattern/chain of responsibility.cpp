#include<iostream>
using namespace std;

class Approver {
public:
    virtual void approve(int days) = 0;
};

class Approver {

protected:
    Approver* next;

public:

    void setNext(Approver* next) {
        this->next = next;
    }

    virtual void approve(int days) = 0;
};

class TeamLead : public Approver {

public:

    void approve(int days) override {

        if(days <= 1) {

            cout << "Approved by Team Lead\n";

        } else if(next) {

            next->approve(days);
        }
    }
};

class Manager : public Approver {

public:

    void approve(int days) override {

        if(days <= 5) {

            cout << "Approved by Manager\n";

        } else if(next) {

            next->approve(days);
        }
    }
};

class Director : public Approver {

public:

    void approve(int days) override {

        cout << "Approved by Director\n";
    }
};

int main() {

    TeamLead tl;
    Manager mgr;
    Director dir;

    tl.setNext(&mgr);
    mgr.setNext(&dir);

    tl.approve(4);
}