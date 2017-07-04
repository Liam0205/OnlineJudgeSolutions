#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const size_t MAX_REC_NUM = 1000;

struct node {
  size_t value;
  size_t pos;
  node () : value(0), pos(0) {}
  node (size_t v, size_t p) : value(v), pos(p) {}
  node (const node& orig) : value(orig.value), pos(orig.pos) {}
  bool operator< (const node& rhs) const {
    return this->pos < rhs.pos;
  }
};

size_t calcMaxGapINAdjacent (const size_t& location, const size_t& width, const size_t& px_nums, const size_t& rec_nums, const size_t rec[][2]);
int getValue (const size_t& location, const size_t& rec_nums, const size_t rec[][2]);

int main () {
  freopen("1009.test.txt", "r", stdin);
  size_t width(0);
  while (scanf("%lu", &width) != EOF and width) {
    printf("%lu\n", width);
    size_t px_val(0), repeat_times(0);
    size_t px_nums(0), rec_nums(0);
    size_t rec[MAX_REC_NUM][2];
    while (scanf("%lu%lu", &px_val, &repeat_times) != EOF) {
      px_nums += repeat_times;
      rec[rec_nums][0] = px_val;
      rec[rec_nums][1] = px_nums;
      if (0 == repeat_times) {
        break;
      }
      ++rec_nums;
    }
    // printf("px_nums[%lu], rec_nums[%lu]\n", px_nums, rec_nums);
    vector<node> nodes;
    for (size_t i = 0; i != rec_nums; ++i) {
      size_t row(rec[i][1] / width);
      size_t col(rec[i][1] % width);
      for (int j(row - 1); j != row + 2; ++j) {
        for (int k(col - 1); k != col + 2 and j >= 0; ++k) {
          if (k < 0) {
            continue;
          }
          size_t location = j * width + k;
          if (location > px_nums) {
            continue;
          }
          // printf("before calling calcMaxGapINAdjacent\n");
          nodes.push_back(node(calcMaxGapINAdjacent(location, width, px_nums, rec_nums, rec), location));
        }
      }
    }
    stable_sort(nodes.begin(), nodes.end());
    // for (size_t i = 0; i != nodes.size(); ++i) {
    //   printf("%lu, %lu\n", nodes[i].value, nodes[i].pos);
    // }
    node curr(nodes[0]);
    size_t nodes_num = nodes.size();
    for (size_t i(0); i != nodes_num; ++i) {
      if (curr.value == nodes[i].value) {
        continue;
      }
      printf("%lu %lu\n", curr.value, nodes[i].pos - curr.pos);
      curr = nodes[i];
    }
    printf("%lu %lu\n", curr.value, px_nums - curr.pos);
    printf("0 0\n");
  }
  printf("0\n");
  return 0;
}

size_t calcMaxGapINAdjacent (const size_t& location, const size_t& width, const size_t& px_nums, const size_t& rec_nums, const size_t rec[][2]) {
  size_t row(location / width);
  size_t col(location % width);
  size_t res(0);
  // printf("before calling getValue\n");
  int curr_value(getValue(location, rec_nums, rec));
  for (int i = row - 1; i != row + 2; ++i) {
    for (int j = col - 1; j != col + 2 and i >= 0; ++j) {
      if (j < 0 or j >= width) {
        continue;
      }
      size_t pos(i * width + j);
      if (pos == location or pos >= px_nums) {
        continue;
      }
      size_t tmp(abs(getValue(pos, rec_nums, rec) - curr_value));
      res = tmp > res ? tmp : res;
    }
  }
  return res;
}

int getValue (const size_t& location, const size_t& rec_nums, const size_t rec[][2]) {
  // binary search
  size_t low(0), high(rec_nums);
  while (low < high and low != high - 1) {
    // printf("low[%lu], high[%lu]\n", low, high);
    size_t mid = (low + high) / 2;
    // printf("low[%lu] mid[%lu] high[%lu] rec[mid][1]:%lu location[%lu]\n", low, mid, high, rec[mid][1], location);
    if (rec[mid][1] <= location) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  // printf("return low[%lu] rec[low][0]:%lu\n", low, rec[low][0]);
  return rec[low][0];
}

