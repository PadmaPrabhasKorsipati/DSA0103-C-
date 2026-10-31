#include <iostream>
using namespace std;

int& highestMark(int marks[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[index]) index = i;
    }
    return marks[index];
}

int highestMarkIndex(const int marks[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i) {
        if (marks[i] > marks[index]) index = i;
    }
    return index;
}

int* highestMarkPointer(int marks[], int size) {
    int* highest = &marks[0];
    for (int i = 1; i < size; ++i) {
        if (marks[i] > *highest) highest = &marks[i];
    }
    return highest;
}

int main() {
    int marks[] = {78, 92, 85, 96, 88};
    int size = sizeof(marks) / sizeof(marks[0]);

    cout << "Original marks: ";
    for (int mark : marks) cout << mark << ' ';
    cout << '\n';

    highestMark(marks, size) += 2;
    cout << "After +2 using reference: ";
    for (int mark : marks) cout << mark << ' ';
    cout << '\n';

    int index = highestMarkIndex(marks, size);
    cout << "Highest mark index: " << index << '\n';

    int* highest = highestMarkPointer(marks, size);
    cout << "Highest mark using pointer: " << *highest << '\n';
    cout << "Highest mark using const view: " << marks[index] << '\n';
}
