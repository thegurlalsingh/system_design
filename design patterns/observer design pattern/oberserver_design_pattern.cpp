#include <iostream>
#include <vector>

using namespace std;

class Subscriber {
public:
    virtual void update(string videoTitle) = 0;
};

class User : public Subscriber {

private:
    string name;

public:

    User(string name) {
        this->name = name;
    }

    void update(string videoTitle) override {

        cout << name
             << " got notification for "
             << videoTitle << "\n";
    }
};

class YouTubeChannel {

private:

    vector<Subscriber*> subscribers;

public:

    void subscribe(Subscriber* s) {
        subscribers.push_back(s);
    }

    void notifySubscribers(string videoTitle) {

        for(auto s : subscribers) {
            s->update(videoTitle);
        }
    }

    void uploadVideo(string title) {

        cout << "New Video Uploaded: "
             << title << "\n";

        notifySubscribers(title);
    }
};

int main() {

    YouTubeChannel channel;

    User u1("Gurlal");
    User u2("Aman");

    channel.subscribe(&u1);
    channel.subscribe(&u2);

    channel.uploadVideo("Observer Pattern");
}