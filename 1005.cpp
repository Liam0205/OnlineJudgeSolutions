#include <iostream>
#include <cmath>

using namespace std;

const double DOUBLED_SURFACE_PER_YEAR = 2 * 50.0;
const double PI = 3.14159265358979323846;

int main () {
    size_t max_num(0), cnt(0);
    std::ios::sync_with_stdio(false);
    cin >> max_num;
    double x(0.0), y(0.0);
    while (cnt != max_num and cin >> x >> y) {
        ++cnt;
        double r_square(x * x + y * y);
        double max_r_sq(0.0);
        size_t year(0);
        while (max_r_sq < r_square) {
            ++year;
            max_r_sq = (DOUBLED_SURFACE_PER_YEAR * year) / PI;
        }
        cout << "Property "
                << cnt
                << ": This property will begin eroding in year "
                << year
                << "."
                << endl;
    }
    cout << "END OF OUTPUT." << endl;
    return 0;
}
