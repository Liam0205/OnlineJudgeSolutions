#include <iostream>

using namespace std;
const size_t LINE_COUNT = 12;
int main () {
    double total(0.0);
    double curr(0.0);
    size_t cnt(0);
    std::ios::sync_with_stdio(false);
    while (cin >> curr) {
        total += curr;
        ++cnt;
    }
    if (LINE_COUNT == cnt) {
        cout << "$" << total / LINE_COUNT << endl;
    }
    return 0;
}

