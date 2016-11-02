#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>

#include <iostream>
#include <string>

const size_t NUM_LEN  = 7;
const size_t HIGH_LEN = 3;
const size_t LOW_LEN  = 4;
const int MASK        = 10000;     // last four digits
const size_t MAX_NUM  = 10000000;
const int MAP[]       = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};

using namespace std;

int main () {
    bool getIntFromString (const string& in, int& out);
    bool getStdStringFromInt (const int& in, string& out);

    size_t total(0);
    std::ios::sync_with_stdio(false);
    cin >> total;

    int* hash_map = reinterpret_cast<int*>(malloc(MAX_NUM * sizeof(int)));
    memset(hash_map, 0, MAX_NUM * sizeof(int));

    size_t cnt(0);
    string in;
    while (cnt != total and cin >> in) {
        ++cnt;
        int out(0);
        if (getIntFromString(in, out)) {
            ++(hash_map[out]);
        }
    }

    bool flag(false);
    for (size_t i = 0; i != MAX_NUM; ++i) {
        if (hash_map[i] > 1) {
            flag = true;
            string out;
            getStdStringFromInt(i, out);
            cout << out << ' ' << hash_map[i] << endl;
        }
    }
    if (!flag) {
        cout << "No duplicates." << endl;
    }

    return 0;
}

inline bool isTelNumValid (const string& str) {
    size_t len = str.size();
    size_t cnt(0);
    for (size_t i = 0; i != len; ++i) {
        const char curr = str[i];
        if (isdigit(curr) or (isupper(curr) and 'Q' != curr and 'Z' != curr)) {
            ++cnt;
        } else if ('-' != curr) {
            return false;
        }
    }
    if (NUM_LEN != cnt) {
        return false;
    }
    return true;
}

inline bool padLeft (string& str, size_t tgt_len, const char& pad_char = '0') {
    size_t len_str = str.size();
    if (!(len_str < tgt_len)) { return false; }
    str = string(tgt_len - len_str, pad_char) + str;
    return true;
}

bool getStdStringFromInt (const int& in, string& out) {
    out.clear();
    char high[HIGH_LEN + 1];
    char low[LOW_LEN + 1];
    snprintf(high, HIGH_LEN + 1, "%03d", in / MASK);
    snprintf(low,  LOW_LEN  + 1, "%04d", in % MASK);
    out = string(high) + "-" + low;
    return true;
}

bool getIntFromString (const string& in, int& out) {
    out = 0;
    if (!isTelNumValid(in)) { return false; }
    size_t len = in.size();
    for (size_t i = 0; i != len; ++i) {
        const char curr = in[i];
        if (isdigit(curr)) {
            out = out * 10 + (curr - '0');
        } else if (isupper(curr)) {
            out = out * 10 + MAP[curr - 'A'];
        }
    }
    return true;
}
