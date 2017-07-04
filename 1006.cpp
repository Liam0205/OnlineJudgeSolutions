#include <iostream>

const int P_LOOP = 23;
const int E_LOOP = 28;
const int I_LOOP = 33;
const int BIG_LOOP = P_LOOP * E_LOOP * I_LOOP;
const int PE_LOOP = P_LOOP * E_LOOP;
const int EI_LOOP = E_LOOP * I_LOOP;
const int IP_LOOP = I_LOOP * P_LOOP;

using namespace std;

int main () {
  int p(0), e(0), ii(0), d(0), cnt(0);
  std::ios::sync_with_stdio(false);
  int getNextTriplePeakDay (const int& p, const int& e, const int& ii);
  while (cin >> p >> e >> ii >> d and -1 != p and -1 != e and -1 != ii and -1 != d) {
    ++cnt;
    int gap(getNextTriplePeakDay(p, e, ii) - d);
    gap = gap > 0 ? gap : BIG_LOOP + gap;
    cout << "Case " << cnt << ": the next triple peak occurs in " << gap << " days." << endl;
  }
  return 0;
}

int getNextTriplePeakDay (const int& p, const int& e, const int& ii) {
  int peak_map[BIG_LOOP];
  for (int i = 0; i != BIG_LOOP; ++i) peak_map[i] = 0;
  for (int i = 0; i != EI_LOOP; ++i) {
    int curr = (p + i * P_LOOP) % BIG_LOOP;
    ++peak_map[curr];
  }
  for (int i = 0; i != IP_LOOP; ++i) {
    int curr = (e + i * E_LOOP) % BIG_LOOP;
    ++peak_map[curr];
  }
  for (int i = 0; i != PE_LOOP; ++i) {
    int curr = (ii + i * I_LOOP) % BIG_LOOP;
    ++peak_map[curr];
    if (3 == peak_map[curr]) {
      return curr;
    }
  }
  return -1;
}

