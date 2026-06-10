#include<iostream>
using namespace std;

class FileSystemNode {
public:
    virtual void show() = 0;
};

class File : public FileSystemNode {

private:
    string name;

public:

    File(string name) {
        this->name = name;
    }

    void show() override {
        cout << name << "\n";
    }
};

class Folder : public FileSystemNode {

private:

    string name;

    vector<FileSystemNode*> children;

public:

    Folder(string name) {
        this->name = name;
    }

    void add(FileSystemNode* node) {
        children.push_back(node);
    }

    void show() override {

        cout << "Folder: "
             << name << "\n";

        for(auto child : children) {
            child->show();
        }
    }
};

int main() {

    File* f1 = new File("Resume.pdf");

    File* f2 = new File("Notes.pdf");

    Folder* docs = new Folder("Documents");

    docs->add(f1);

    docs->add(f2);

    docs->show();
}