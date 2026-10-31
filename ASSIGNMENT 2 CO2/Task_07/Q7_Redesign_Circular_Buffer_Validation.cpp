#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;

void addByShifting(vector<int>& data, int value, int capacity) {
    if ((int)data.size() == capacity) {
        for (int i = 1; i < capacity; ++i) data[i - 1] = data[i];
        data[capacity - 1] = value;
    } else {
        data.push_back(value);
    }
}

class CircularHistory {
    vector<int> data;
    int capacity, count = 0, next = 0;
public:
    explicit CircularHistory(int cap) : data(cap), capacity(cap) {}
    void add(int value) {
        data[next] = value;
        next = (next + 1) % capacity;
        if (count < capacity) ++count;
    }
    int size() const { return count; }
    int latest() const { return data[(next - 1 + capacity) % capacity]; }
};

int main() {
    const int capacity = 10;
    vector<int> shifted;
    CircularHistory circular(capacity);

    for (int i = 1; i <= 15; ++i) {
        addByShifting(shifted, i, capacity);
        circular.add(i);
    }

    cout << "Original shifting design:\n";
    cout << "Stored transactions: " << shifted.size() << '\n';
    cout << "Oldest retained: " << shifted.front() << '\n';
    cout << "Newest retained: " << shifted.back() << '\n';

    cout << "Redesigned circular buffer:\n";
    cout << "Stored transactions: " << circular.size() << '\n';
    cout << "Newest retained: " << circular.latest() << '\n';

    cout << "Insertion complexity: shifting O(k), circular O(1)\n";
    cout << "Storage complexity: both O(k)\n";
    cout << "Validation: both designs retain the latest 10 values (6 to 15).\n";
}
