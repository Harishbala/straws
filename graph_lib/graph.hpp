#include <vector>
#include <map>
#include <memory>
#include <vector>
#include <memory>
#include <iostream>
#include <queue>

template <class T>
struct Edge
{
    T label_;
    int weight_;
    Edge(T label, int weight)
        : label_(label),
        weight_(weight) {
        }
};

template <class T>
struct GraphNode
{
    T label_;
    bool visited;
    std::vector<Edge<T>> neighbors_;

    virtual ~GraphNode() {}
    
    virtual T get_label()
    {
        return label_;
    }
};

template<typename T2>
class Graph
{
public:
    void insert_node(const T2 node_id, const std::vector<T2>&& neighbors, const std::vector<int> weights = {});
    void print_nodes() const;
    void delete_node(T2 node_id);
    void bfs(T2 node_id, std::function<void()> action);
    void dfs(T2 node_id, std::function<void()> action);
    void print_nodes_as_dot() const;
    
private:
    void reset_visited_state();
    void dfs_(const std::unique_ptr<GraphNode<T2> >& node, std::function<void()> action);

    
    std::map<T2, std::unique_ptr<GraphNode<T2> > > nodes;
};

template<typename T>
void Graph<T>::insert_node(const T node_id, const std::vector<T>&& neighbors, const std::vector<int> weights)
{
    auto it = nodes.find(node_id);
    if(it ==  nodes.end()) {
        auto node_ptr = std::make_unique<GraphNode<T>>();
        node_ptr->label_ = node_id;
        auto [new_it, result] = nodes.insert(make_pair(node_ptr->label_, std::move(node_ptr)));
        it = new_it;
    }
    if(neighbors.size() == weights.size() || weights.size() == 0) {
        auto index = 0;
        for (const auto& item : neighbors) {
            auto d_it =  nodes.find(item);
            if(d_it == nodes.end()) {
                insert_node(item, {});
            }
            auto weight = 0;
            if(weights.size() != 0) {
                weight = weights[index];
            }
            it->second->neighbors_.push_back(Edge{item, weight});
            ++index;
        }
    }
}

template<typename T>
void Graph<T>::print_nodes() const
{
  for(const auto& node : nodes) {
      std::cout << node.second->label_ << "---";
      for(const auto& item : node.second->neighbors_) {
          std::cout << item.label_ << "|" << item.weight_ << ' ';
      }
      std::cout<<'\n';
  }
}

template<typename T>
void Graph<T>::print_nodes_as_dot() const
{
  std::cout << "graph great_graph {\n";
  for(const auto& node : nodes) {
      std::cout <<node.second->get_label()<<" -- {";
      int i = 0;
      for(const auto& item : node.second->neighbors_) {
          if(i++ != 0)
              std::cout<<",";
          std::cout <<item.label_;
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
            auto node_it = nodes.find(node_index.label_);
            if(node_it != nodes.end()) {
                auto& interested_neighbors = node_it->second->neighbors_;
                auto new_end = std::remove_if(begin(interested_neighbors), end(interested_neighbors),
                            [&node_id] (const auto& neighbor_node_id) { return neighbor_node_id.label_ == node_id; });
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
                bfs_q.push(item.label_);
            }
        }
        bfs_q.pop();
    }
}

template<typename T>
void Graph<T>::dfs(T node_id, std::function<void()> action)
{
    reset_visited_state();

    auto it = nodes.find(node_id);
    if(it != nodes.end())
        dfs_(it->second, action);
}

template<typename T>
void Graph<T>::dfs_(const std::unique_ptr<GraphNode<T> >& node, std::function<void()> action)
{
    const auto& current = node;
    while(current && !current->visited) {
        current->visited = true;
        std::cout << current->get_label() << '\n';
        for(const auto& item : current->neighbors_) {
            auto n_it =  nodes.find(item.label_);
            if (n_it != nodes.end()) {
                dfs_(n_it->second, action);
            }
        }
    }
}
