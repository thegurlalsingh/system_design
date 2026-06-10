#include <iostream>
#include <vector>

using namespace std;

class DatabaseInterface {
public:
    virtual void access() = 0;
};

class RealDatabase : public DatabaseInterface {
public:

    void access() override {
        cout << "Database Accessed\n";
    }
};

class DatabaseProxy : public DatabaseInterface {

private:

    RealDatabase db;

public:

    void access() override {

        cout << "Checking Permission...\n";

        db.access();
    }
};

int main() {

    DatabaseInterface* db =
        new DatabaseProxy();

    db->access();
}