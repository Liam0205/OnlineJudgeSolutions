#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

size_t getCrossReversePairNum (char[], const size_t&, const size_t&, const size_t&);
size_t getReversePairNum (char[], const size_t&, const size_t&);

struct DNA {
    string seq;
    size_t rev_num;
    bool operator< (const DNA& rhs) const {
        return this->rev_num < rhs.rev_num;
    }
};

int main () {
    size_t len(0), num(0);
    std::ios::sync_with_stdio(false);
    cin >> len >> num;
    char buffer[len + 1];
    DNA  group[num];
    size_t cnt(0);
    while (cin >> buffer and cnt < num) {
        group[cnt].seq     = buffer;
        group[cnt].rev_num = getReversePairNum(buffer, 0, len);
        ++cnt;
    }
    stable_sort(group, group + num);
    for (size_t i = 0; i != num; ++i) {
        cout << group[i].seq
                // << "\t" << group[i].rev_num
                << endl;
    }
    return 0;
}

size_t getCrossReversePairNum (char vec[], const size_t& begin, const size_t& mid, const size_t& end) {
    size_t reverse(0);
    if (begin < mid and mid < end) {
        for (size_t i = mid; i != end; ++i) {
            char high = vec[i];
            for (size_t j = begin; j != mid; ++j) {
                if (high < vec[j]) {
                    ++reverse;
                }
            }
        }
    }
    return reverse;
}

size_t getReversePairNum (char vec[], const size_t& begin, const size_t& end) {
    size_t low(0), high(0), cross(0);
    if (begin + 1 < end) {
        size_t mid = (begin + end) / 2;
        low   = getReversePairNum(vec, begin, mid);
        high  = getReversePairNum(vec, mid, end);
        cross = getCrossReversePairNum(vec, begin, mid, end);
    }
    return low + high + cross;
}

