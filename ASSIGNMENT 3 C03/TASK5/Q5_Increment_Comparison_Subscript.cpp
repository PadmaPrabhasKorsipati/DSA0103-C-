#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int seconds;

public:
    explicit Time(int s = 0) : seconds(s) {}
    Time& operator++() { ++seconds; return *this; }
    Time operator++(int) { Time old(*this); ++seconds; return old; }
    bool operator==(const Time& other) const { return seconds == other.seconds; }
    bool operator<(const Time& other) const { return seconds < other.seconds; }
    int value() const { return seconds; }
};

class Playlist {
    std::vector<std::string> tracks;

public:
    Playlist(std::initializer_list<std::string> items) : tracks(items) {}
    std::string& operator[](int i) {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw std::out_of_range("Playlist index out of range");
        return tracks[i];
    }
    const std::string& operator[](int i) const {
        if (i < 0 || i >= static_cast<int>(tracks.size()))
            throw std::out_of_range("Playlist index out of range");
        return tracks[i];
    }
};

int main() {
    std::cout << "Q5 - Increment and Subscript Operators\n";
    Time t(5);
    Time a = t++;
    Time b = ++t;
    std::cout << "a=" << a.value() << " b=" << b.value()
              << " t=" << t.value() << '\n';

    Playlist playlist{"Track One", "Track Two", "Track Three"};
    std::cout << "Now playing: " << playlist[1] << '\n';
    playlist[1] = "Updated Track";
    std::cout << "Updated: " << playlist[1] << '\n';

    try {
        std::cout << playlist[-1] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Range test: " << e.what() << '\n';
    }

    Time roll(3599);
    ++roll;
    std::cout << "Seconds after increment: " << roll.value()
              << " (3600 = 1 hour)\n";
}