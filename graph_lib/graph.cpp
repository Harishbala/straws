#include <vector>
#include <memory>
#include <iostream>

#include "graph.h"

void Graph::insert_node(const int node_id, const std::vector<int>&& neighbours)
{
    auto node_ptr = std::make_unique<GraphNode>();
    node_ptr->label_ = node_id;
    node_ptr->neighbours_ =  std::move(neighbours);
    nodes.push_back(std::move(node_ptr));
}

void Graph::print_nodes() const
{
  for(const auto& node : nodes) {
      std::cout << node->label_ << "---";
      for(const auto& item : node->neighbours_) {
          std::cout << item << ' ';
      }
      std::cout<<'\n';
  }
}
int main()
{
    Graph graph;
    graph.insert_node(1, {2, 3, 4});
    graph.insert_node(2, {3, 4, 1});
    graph.insert_node(3, {4, 3, 2});
    graph.insert_node(4, {1, 3, 2});

    graph.print_nodes();
}
