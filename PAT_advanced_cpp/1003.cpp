#define LIAM_TEST_

#include <iostream>
#include <limits>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>

#ifdef LIAM_TEST_
#include <fstream>
constexpr const char* casefname = "./cases/1003.case.txt";
std::ifstream cin(casefname);
#else
using std::cin;
#endif

typedef size_t nodeid_t;
typedef size_t dist_t;

struct Path {
    dist_t total_length_ = 0;
    std::vector<nodeid_t> nodes_;

    inline
    bool operator<(const Path& rhs) const {
        return (this->total_length_ < rhs.total_length_);
    }
};

struct Node {
    nodeid_t id_ = 0;
    size_t team_count_ = 0;
    dist_t max_dist_ = std::numeric_limits<dist_t>::max();

    std::set<std::shared_ptr<Path>> shortest_paths_;

    Node(const nodeid_t& id, const size_t& team_count) : id_{id}, team_count_{team_count} {}
    Node(const nodeid_t& id, const size_t& team_count, const dist_t& max_dist) :
        id_{id}, team_count_{team_count}, max_dist_{max_dist} {}

    inline
    bool operator<(const Node& rhs) const {
        return (this->max_dist_ < rhs.max_dist_);
    }
};

namespace std {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}  // namespace std

int main() {
    // initialize
    nodeid_t node_num;
    cin >> node_num;
    size_t path_num;
    cin >> path_num;
    nodeid_t source, target;
    cin >> source >> target;

    std::set<std::unique_ptr<Node>> processed, unprocessed;

    for (nodeid_t loop = 0; loop != node_num; ++loop) {
        size_t team_count;
        cin >> team_count;
        if (loop == source) {
            processed.insert(std::make_unique<Node>(loop, team_count, 0));
        } else {
            unprocessed.insert(std::make_unique<Node>(loop, team_count));
        }
    }

    std::vector<std::vector<dist_t>> dist_mtx;
    dist_mtx.resize(node_num);
    for (auto& column : dist_mtx) {
        column.resize(node_num);
        std::fill(column.begin(), column.end(), std::numeric_limits<dist_t>::max());
    }
    for (size_t loop = 0; loop != path_num; ++loop) {
        nodeid_t start, end;
        dist_t dist;
        cin >> start >> end >> dist;
        dist_mtx[start][end] = dist_mtx[end][start] = dist;
    }

    return 0;
}

