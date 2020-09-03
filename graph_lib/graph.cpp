#include <vector>
#include <memory>
#include <iostream>

#include "graph.h"

void Graph::insert_node(const int node_id, const std::vector<int>&& neighbors)
{
    auto node_ptr = std::make_unique<GraphNode>();
    node_ptr->label_ = node_id;
    node_ptr->neighbors_ =  std::move(neighbors);
    nodes.push_back(std::move(node_ptr));
}

void Graph::print_nodes() const
{
  for(const auto& node : nodes) {
      std::cout << node->label_ << "---";
      for(const auto& item : node->neighbors_) {
          std::cout << item << ' ';
      }
      std::cout<<'\n';
  }
}

void Graph::delete_node(int node_id)
{
    for(auto& node : nodes) {
        std::cout << " iterating through nodes\n";
        if (node->label_ == node_id) {
            std::cout << "Matched node id \n";
            for(const auto& node_index : node->neighbors_) {
                std::cout << "matching node index\n";
                auto& interested_neighbors = nodes[node_index-1]->neighbors_;
                auto new_end = std::remove_if(begin(interested_neighbors), end(interested_neighbors),
                            [node_id] (int neighbor_node_id) { return neighbor_node_id == node_id; });
                interested_neighbors.erase(new_end, end(interested_neighbors));
            }
        }
    }
}
