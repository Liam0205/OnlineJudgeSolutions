#include <iostream>
#include <string>

using std::string;
using std::size_t;
using std::cin;
using std::cout;
using std::endl;
using std::min;

int main () {
  string str("");
  int exp(0);

  bool prepareBaseOFString(string &str);
  string stringPow(const string &str, int exp);

  while (cin >> str >> exp) {
    prepareBaseOFString(str);
    cout << stringPow(str, exp) << endl;
  }

  return 0;
}

// if str contains a integer, return true; else return false.
bool prepareBaseOFString(string &str) {
  // remove leading 0
  str.erase(0, min(str.find_first_not_of('0'), str.size() - 1));
  if (str.empty()) { str = "0"; }
  size_t found = str.find(".");
  bool is_int = !(str.find(".") != std::string::npos);
  if (is_int) { return true; }
  // remove traling 0
  found = str.find_last_not_of('0');
  if (found != std::string::npos and found != str.size() - 1) {
    str.erase(found + 1, std::string::npos);
  }
  // remove traling .
  found = str.find_last_not_of('.');
  if (found != std::string::npos and found != str.size() - 1) {
    str.erase(found + 1, std::string::npos);
  }
  if (str.empty()) { str = "0"; }
  return false;
}

// how many digits after the decimal point
size_t makeRealInteger(string &str) {
  if (prepareBaseOFString(str)) { return 0; }
  size_t found(str.find_last_of('.'));
  if (found != str.size()) {
    // erase the decimal point
    str.erase(found, 1);
    size_t res = str.size() - found;
    return res;
  } else { 
    return 0;
  }
}

string multipleOFTwoString(string lhs, string rhs) {
  // trivial test
  if (lhs.empty() or rhs.empty() or "0" == lhs or "0" == rhs) { return "0"; }
  size_t f_lhs(makeRealInteger(lhs)), f_rhs(makeRealInteger(rhs));
  size_t sz_lhs(lhs.size()), sz_rhs(rhs.size());
  string result(sz_lhs + sz_rhs, '0');
  for (size_t i = 0; i != sz_lhs; ++i) {
    size_t wk_i = sz_lhs - i - 1;
    int carry(0);
    int l(lhs[wk_i] - '0');
    for (size_t j = 0; j != sz_rhs; ++j) {
      size_t wk_j = sz_rhs - j - 1;
      int r(rhs[wk_j] - '0');
      int sum = l * r + carry + (result[wk_i + wk_j + 1] - '0');
      carry = static_cast<int>(sum / 10);
      result[wk_i + wk_j + 1] = (sum % 10 + '0');
    }
    result[sz_lhs - i - 1] += carry;
  }
  if (f_lhs + f_rhs > 0) { result.insert(result.end() - f_lhs - f_rhs, '.'); }
  prepareBaseOFString(result);
  return result;
}

string stringPow(const string &str, int exp) {
  // trivial test
  if (str.empty() or "0" == str) { return "0"; }
  if (0 == exp) return "1";
  if (1 == exp) return str;
  string result(stringPow(str, static_cast<int>(exp / 2)));
  result = multipleOFTwoString(result, result);
  if (exp & 0x1) { result = multipleOFTwoString(result, str); }
  return result;
}

