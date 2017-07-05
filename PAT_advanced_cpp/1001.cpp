#define LIAM_TEST_

#include <iostream>
#include <iomanip>
#include <locale>
#include <cstdint>
#include <string>

#ifdef LIAM_TEST_
#include <fstream>
constexpr const char* casefname = "./cases/1001.case.txt";
std::ifstream cin(casefname);
#else
using std::cin;
#endif

template<typename T>
class ThousandsSeparator : public std::numpunct<T> {
 public:
    ThousandsSeparator(T separator) : separator_(separator) {}

 protected:
    inline
    T do_thousands_sep() const override {
        return separator_;
    }

    inline
    std::string do_grouping() const override {
        return "\03";
    }

 private:
    T separator_;
};

template<typename T>
inline
std::ostream& FormatWithCommas(T value, std::ostream& ostrm, std::numpunct<char>* const separator) {
    ostrm.imbue(std::locale(ostrm.getloc(), separator));
    ostrm << std::fixed << value << std::endl;
    return ostrm;
}

int main() {
    int32_t lhs, rhs;
    ThousandsSeparator<char> separator(',');
    while (cin >> lhs >> rhs and FormatWithCommas((lhs + rhs), std::cout, &separator)) {}
    return 0;
}

