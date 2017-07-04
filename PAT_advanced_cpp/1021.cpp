#define LIAM_TEST_

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

#ifdef LIAM_TEST_
#include <fstream>
constexpr const char* casefname = "./cases/1021.1.case.txt";
std::ifstream cin(casefname);
#else
using std::cin;
#endif

struct Graph {
    typedef size_t size_type;
    typedef size_t id_type;
    typedef std::unordered_map<id_type, std::unordered_set<id_type>> adjacent_table;

    size_type graph_size = 0;
    adjacent_table atbl;

    inline
    const size_type init_graph(std::istream* pistrm) {
        auto& istrm = *pistrm;

        istrm >> graph_size;

        id_type start, end;
        for (size_type i = 0; i != graph_size - 1; ++i) {
            istrm >> start >> end;
            atbl[start].insert(end);
            atbl[end].insert(start);
        }

        return graph_size;
    }

    inline
    const void dfs(const id_type& id, const size_type& search_depth, bool visit_record[],
            size_type* max_depth, std::vector<id_type>* farthest_nodes, bool update = false) const {
        if (update and search_depth > *max_depth) {
            farthest_nodes->clear();
            farthest_nodes->push_back(id);
            *max_depth = search_depth;
        } else if (update and search_depth == *max_depth) {
            farthest_nodes->push_back(id);
        } else {}

        visit_record[id] = true;

        for (const auto& aid : this->atbl.at(id)) {
            if (not(visit_record[aid])) {
                dfs(aid, search_depth + 1, visit_record, max_depth, farthest_nodes, update);
            } else {}
        }
    }
};

int main() {
    // init the graph
    Graph graph;
    const auto graph_size = graph.init_graph(&cin);

    // start deep first search, from the first node
    bool visit_record[graph_size + 1];
    std::fill(visit_record, visit_record + graph_size + 1, false);  // clean all records
    Graph::size_type max_depth = 0;
    std::vector<Graph::id_type> farthest_nodes;
    farthest_nodes.resize(graph_size + 1);
    graph.dfs(1, 1, visit_record, &max_depth, &farthest_nodes, true);  // update records
    std::set<Graph::id_type> nodes_in_path(farthest_nodes.begin(), farthest_nodes.end());

    // go through all nodes
    size_t parts = 1;  // at least we have nodes that could link to node 1.
    for (Graph::size_type loop = 0; loop != graph_size; ++loop) {
        const Graph::id_type id = loop + 1;
        if (not(visit_record[id])) {
            ++parts;
            graph.dfs(id, 1, visit_record, &max_depth, &farthest_nodes, false);
        } else {}
    }

    // check parts
    if (parts > 1) {
        std::cout << "Error: " << parts << " components" << std::endl;
    } else {
        const auto root = farthest_nodes[0];
        std::fill(visit_record, visit_record + graph_size + 1, false);  // clean all records
        max_depth = 0;
        farthest_nodes.clear();
        graph.dfs(root, 1, visit_record, &max_depth, &farthest_nodes, true);
        nodes_in_path.insert(farthest_nodes.begin(), farthest_nodes.end());
        for (const auto& id : nodes_in_path) {
            std::cout << id << std::endl;
        }
    }

    return 0;
}

