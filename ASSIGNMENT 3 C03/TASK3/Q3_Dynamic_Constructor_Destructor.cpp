#include <iostream>
#include <string>

class Event {
    int rows, seats, booked;
    char** map;

public:
    Event(int r, int s) : rows(r), seats(s), booked(0), map(nullptr) {
        if (rows > 0 && seats > 0) {
            map = new char*[rows];
            for (int i = 0; i < rows; ++i) {
                map[i] = new char[seats];
                for (int j = 0; j < seats; ++j) map[i][j] = 'O';
            }
        }
        std::cout << "Construct Event " << rows << "x" << seats << '\n';
    }

    bool book(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats || map[r][s] == 'X')
            return false;
        map[r][s] = 'X';
        ++booked;
        return true;
    }

    bool cancel(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats || map[r][s] == 'O')
            return false;
        map[r][s] = 'O';
        --booked;
        return true;
    }

    ~Event() {
        for (int i = 0; i < rows; ++i) delete[] map[i];
        delete[] map;
        std::cout << "Destroy Event " << rows << "x" << seats
                  << " | booked seats: " << booked << '\n';
    }
};

int main() {
    std::cout << "Q3 - Dynamic Allocation and RAII\n";
    Event local(2, 3);
    local.book(0, 1);
    local.book(1, 2);
    local.cancel(0, 1);

    {
        Event block(1, 2);
        block.book(0, 0);
    }

    Event* dynamicEvent = new Event(2, 2);
    dynamicEvent->book(1, 1);
    delete dynamicEvent;

    Event zeroRows(0, 5);
    std::cout << "End of main scope\n";
}