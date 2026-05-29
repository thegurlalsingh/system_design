#include<iostream>
using namespace std;

class CPU {
public:
    void start() {
        cout << "CPU Started\n";
    }
};

class Memory {
public:
    void load() {
        cout << "Memory Loaded\n";
    }
};

class Disk {
public:
    void read() {
        cout << "Disk Read\n";
    }
};

class ComputerFacade {

private:
    CPU cpu;
    Memory mem;
    Disk disk;

public:

    void startComputer() {

        cpu.start();

        mem.load();

        disk.read();

        cout << "Computer Ready\n";
    }
};

int main() {

    ComputerFacade computer;

    computer.startComputer();
}