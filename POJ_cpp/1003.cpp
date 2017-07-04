#include <iostream>

using namespace std;

int main () {
    double target(0.0);
    std::ios::sync_with_stdio(false);
    while (cin >> target and 0.0 != target) {
        double max_len(0.0);
        size_t crd_num(0);
        while (max_len < target) {
            ++crd_num;
            max_len += 1.0 / static_cast<double>(crd_num + 1);
        }
        cout << crd_num << " card(s)" << endl;
    }
    return 0;
}

