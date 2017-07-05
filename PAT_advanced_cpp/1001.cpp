#define LIAM_TEST_

#include <iostream>
#include <iomanip>
#include <locale>
#include <string>
#include <sstream>

#ifdef LIAM_TEST_
#include <fstream>
constexpr const char* casefname = "./cases/1001.case.txt";
std::ifstream cin(casefname);
#else
using std::cin;
#endif

template<class T>
inline
std::string FormatWithCommas(T value) {
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << value;
    return ss.str();
}

int main() {
    int lhs, rhs;
    while (cin >> lhs >> rhs) {
        std::cout << FormatWithCommas(lhs + rhs) << std::endl;
    }
    return 0;
}

