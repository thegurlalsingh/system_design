# include<iostream>
using namespace std;

class Burger {
public:
    virtual void prepare() = 0;

    virtual ~Burger() {}
};

class GarlicBread {
    public:
    virtual void prepare() = 0;

    virtual ~GarlicBread() {}
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Basic Burger\n";
    }
};

class WheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing Wheat Burger\n";
    }
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Basic Garlic Bread\n";
    }
};

class WheatGarlicBread : public GarlicBread {
public:
    void prepare() override {
        cout << "Preparing Wheat Garlic Bread\n";
    }
};

class MealFactory {

public:

    virtual Burger* createBurger() = 0;

    virtual GarlicBread* createGarlicBread() = 0;

    virtual ~MealFactory() {}
};

class KingFactory : public MealFactory {

public:

    Burger* createBurger() override {
        return new BasicBurger();
    }

    GarlicBread* createGarlicBread() override {
        return new BasicGarlicBread();
    }
};

class SinghFactory : public MealFactory {

    public:

    Burger* createBurger() override {
        return new WheatBurger();
    }

    GarlicBread* createGarlicBread() override {
        return new WheatGarlicBread();
    }
};

int main() {

    MealFactory* factory;

    factory = new SinghFactory();

    Burger* burger = factory->createBurger();

    GarlicBread* bread = factory->createGarlicBread();

    burger->prepare();

    bread->prepare();
}
