#include <vector>
#include <memory>
#include <iostream>
#include <queue>

#include "graph.h"

template<typename T>
void Graph<T>::insert_node(const T node_id, const std::vector<T>&& neighbors)
{
    auto node_ptr = std::make_unique<GraphNode<T>>();
    node_ptr->label_ = node_id;
    node_ptr->neighbors_ =  std::move(neighbors);
    nodes.insert(make_pair(node_ptr->label_, std::move(node_ptr)));
}

template<typename T>
void Graph<T>::print_nodes() const
{
  for(const auto& node : nodes) {
      std::cout << node.second->label_ << "---";
      for(const auto& item : node.second->neighbors_) {
          std::cout << item << ' ';
      }
      std::cout<<'\n';
  }
}

template<typename T>
void Graph<T>::print_nodes_as_dot() const
{
  std::cout << "graph great_graph {\n";
  for(const auto& node : nodes) {
      std::cout <<node.second->label_ <<" -- {";
      int i = 0;
      for(const auto& item : node.second->neighbors_) {
          if(i++ != 0)
              std::cout<<",";
          std::cout <<item;
      }
      std::cout<<"}\n";
  }
  std::cout<<'}';
}

template<typename T>
void Graph<T>::delete_node(const T node_id)
{
    auto it = nodes.find(node_id);
    if(it != nodes.end()) { 
        auto& node = it->second;
        for(const auto& node_index : node->neighbors_) {
            auto node_it = nodes.find(node_index);
            if(node_it != nodes.end()) {
                auto& interested_neighbors = node_it->second->neighbors_;
                auto new_end = std::remove_if(begin(interested_neighbors), end(interested_neighbors),
                            [&node_id] (const auto& neighbor_node_id) { return neighbor_node_id == node_id; });
                interested_neighbors.erase(new_end, end(interested_neighbors));
            }
        }
        nodes.erase(it);
        return;
    }
}

template<typename T>
void Graph<T>::reset_visited_state() 
{
  for(const auto& node : nodes) {
      node.second->visited = false;
  }
}

template<typename T>
void Graph<T>::bfs(T node_id, std::function<void()> action)
{
    reset_visited_state();

    std::queue<T> bfs_q;    
    bfs_q.push(node_id);
    while(!bfs_q.empty()) {
        auto id = bfs_q.front();
        auto it = nodes.find(id);
        
        if (it != nodes.end() && !it->second->visited) {
            std::cout << it->second->label_ << '\n';
            it->second->visited = true;
            for(const auto item : it->second->neighbors_) {
                bfs_q.push(item);
            }
        }
        bfs_q.pop();
    }
}

int main1()
{
    Graph<int> graph;
    Graph<std::string> string_graph;
    string_graph.insert_node("Dummy", {});
    string_graph.bfs("Dummy", [](){});
    string_graph.print_nodes();
    string_graph.print_nodes_as_dot();
    string_graph.delete_node("Dummy");
    return 0;
}


