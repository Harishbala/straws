#include <vector>
#include <memory>

struct GraphNode
{
    int label_;
    std::vector<int> neighbours_;
};

class Graph
{
public:
    void insert_node(const int node_id, const std::vector<int>&& neighbours);
    void print_nodes() const;
private:
    std::vector<std::unique_ptr<GraphNode> > nodes;
};
