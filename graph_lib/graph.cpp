#include <vector>
#include <memory>
#include <iostream>

struct GraphNode
{
    int label_;
    std::vector<GraphNode> neighbours_;
};

class Graph
{
public:
    void insert_node(const int node_id, const std::vector<int>&& neighbours);
    void print_nodes() const;
private:
    std::vector<std::unique_ptr<GraphNode> > nodes;
};

void Graph::insert_node(const int node_id, const std::vector<int>&& neighbours)
{
    auto node_ptr = std::make_unique<GraphNode>();
    node.label_ = node_id;
    node.neighbours_ =  std::move(neighbours);
    nodes.push_back(std::move(node_ptr));
}

int main()
{
    Graph graph;
    graph.insert_node(1, {2, 3, 4});
    graph.insert_node(2, {3, 4, 1});
    graph.insert_node(3, {4, 3, 2});
    graph.insert_node(4, {1, 3, 2});
}
