#define LIAM_TEST_

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <map>

#ifdef LIAM_TEST_
#include <fstream>
constexpr const char* casefname = "./cases/1002.3.case.txt";
std::ifstream cin(casefname);
#else
using std::cin;
#endif

typedef size_t exp_t;
typedef double coeff_t;

constexpr const size_t MAX_POLY_EXPONENT = 10;

void accumulate_poly(const std::string& buffer, std::map<exp_t, coeff_t>* poly);
std::ostream& print_poly(std::ostream& ostrm, const std::map<exp_t, coeff_t>& poly);

int main() {
    std::string buffer;
    std::map<exp_t, coeff_t> poly;

    while (std::getline(cin, buffer)) {
        accumulate_poly(buffer, &poly);
    }

    print_poly(std::cout, poly);

    return 0;
}

inline
void accumulate_poly(const std::string& buffer, std::map<exp_t, coeff_t>* poly) {
    std::istringstream iss(buffer);

    size_t count;
    iss >> count;

    exp_t exponent;
    coeff_t coefficient;
    for (size_t loop = 0; loop != count; ++loop) {
        iss >> exponent >> coefficient;
        poly->operator[](exponent) += coefficient;
    }
}

inline
std::ostream& print_poly(std::ostream& ostrm, const std::map<exp_t, coeff_t>& poly) {
    ostrm << std::fixed;
    ostrm << std::count_if(poly.begin(), poly.end(),
                         [&](const std::pair<exp_t, coeff_t> pair){ return (pair.second != 0.0); });

    for (auto iter = poly.crbegin(); iter != poly.crend(); ++iter) {
        exp_t exponent = iter->first;
        coeff_t coefficient = iter->second;
        if (coefficient != 0.0) {
            ostrm << " " << exponent << " " << std::setprecision(1) << coefficient;
        }
    }

    return ostrm;
}

