# include<iostream>
using namespace std;

class Burger {
public:
    virtual void prepare() = 0;

    virtual ~Burger() {}
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger\n";
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Standard Burger\n";
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger\n";
    }
};

class WheatBasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger\n";
    }
};
class WheatStandardBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger\n";
    }
};
class WheatPremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Premium Burger\n";
    }
};

class BurgerFactory {
public:
    virtual Burger* createBurger(string type) = 0;

    virtual ~BurgerFactory() {}
};

class KingBurgerFactory : public BurgerFactory {

public:

    Burger* createBurger(string type) override {

        if(type == "basic")
            return new BasicBurger();

        else if(type == "standard")
            return new StandardBurger();

        else if(type == "premium")
            return new PremiumBurger();

        return nullptr;
    }
};

class SingBurgerFactory : public BurgerFactory {

public:

    Burger* createBurger(string type) override {

        if(type == "basic")
            return new WheatBasicBurger();

        else if(type == "standard")
            return new WheatStandardBurger();

        else if(type == "premium")
            return new WheatPremiumBurger();

        return nullptr;
    }
};

int main() {

    BurgerFactory* factory;

    factory = new KingBurgerFactory();

    Burger* burger = factory->createBurger("premium");

    burger->prepare();
}