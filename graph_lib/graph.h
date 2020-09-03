#include <vector>
#include <memory>

struct GraphNode
{
    int label_;
    std::vector<int> neighbors_;
};

class Graph
{
public:
    void insert_node(const int node_id, const std::vector<int>&& neighbors);
    void print_nodes() const;
    void delete_node(int node_id);

private:
    std::vector<std::unique_ptr<GraphNode> > nodes;
};
