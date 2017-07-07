#define LIAM_TEST_

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

#ifdef LIAM_TEST_
#include <fstream>
constexpr const char* casefname = "./cases/1002.2.case.txt";
std::ifstream cin(casefname);
#else
using std::cin;
#endif

constexpr const size_t MAX_POLY_EXPONENT = 10;

void accumulate_poly(const std::string& buffer, std::vector<double>* poly);
std::ostream& print_poly(const std::vector<double>& poly, std::ostream& ostrm);

int main() {
    std::string buffer;
    std::vector<double> poly;
    poly.resize(MAX_POLY_EXPONENT + 1);
    std::fill(poly.begin(), poly.end(), 0.0);

    while (std::getline(cin, buffer)) {
        accumulate_poly(buffer, &poly);
    }
    print_poly(poly, std::cout);
    return 0;
}

inline
void accumulate_poly(const std::string& buffer, std::vector<double>* poly) {
    std::istringstream iss(buffer);

    size_t count;
    iss >> count;

    size_t exponent;
    double coefficient;
    for (size_t loop; loop != count; ++loop) {
        iss >> exponent >> coefficient;
        poly->operator[](exponent) += coefficient;
    }
}

inline
std::ostream& print_poly(const std::vector<double>& poly, std::ostream& ostrm) {
    ostrm << std::fixed;
    ostrm <<
      std::count_if(poly.begin(), poly.end(), [](double coefficient){return (coefficient != 0.0);});
    for (size_t loop = 0; loop != MAX_POLY_EXPONENT + 1; ++loop) {
        size_t exponent = MAX_POLY_EXPONENT - loop;
        double coefficient = poly[exponent];
        if (coefficient != 0.0) {
            ostrm << " " << exponent << " " << std::setprecision(1) << coefficient;
        }
    }
    return ostrm;
}

