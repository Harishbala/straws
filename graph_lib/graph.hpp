#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <map>
#include <memory>
#include <vector>
#include <memory>
#include <iostream>
#include <queue>
#include <algorithm>

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

template <class T>
struct EdgeTraversal
{
    T parent_;
    bool has_parent = false;
    T current_;
    int weight;
};

template<typename T2>
class Graph
{
public:
    void insert_node(const T2 node_id, const std::vector<T2>&& neighbors, const std::vector<int> weights = {});
    void print_nodes() const;
    void delete_node(T2 node_id);
    void bfs(T2 node_id, std::function<void(EdgeTraversal<T2>& )> action);
    void dfs(T2 node_id, std::function<void(EdgeTraversal<T2>& )> action);
    void add_edge(const T2& source, const T2& dest, int weight = 0);
    void print_nodes_as_dot() const;
    void dijikstra_shortest_paths(T2 source);

private:
    void reset_visited_state();
    void bfs_(T2& node_id, std::function<void(EdgeTraversal<T2>& )> action, EdgeTraversal<T2>& et);
    void dfs_(const std::unique_ptr<GraphNode<T2> >& node, std::function<void(EdgeTraversal<T2>& )> action);
    
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
  std::cout << "digraph great_graph {\n";
  for(const auto& node : nodes) {
      int i = 0;
      for(const auto& item : node.second->neighbors_) {
          std::cout <<node.second->get_label() << " -> " << item.label_<< "[label=" <<item.weight_ <<"]\n";
      }
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
void Graph<T>::bfs(T node_id, std::function<void(EdgeTraversal<T>& )> action)
{
    EdgeTraversal<T> et;
    et.has_parent = false;
    bfs_(node_id, action, et);
}
template<typename T>
void Graph<T>::bfs_(T& node_id, std::function<void(EdgeTraversal<T>& )> action, EdgeTraversal<T>& et)
{
    reset_visited_state();

    std::queue<T> bfs_q;
    bfs_q.push(node_id);
    while(!bfs_q.empty()) {
        auto id = bfs_q.front();
        auto it = nodes.find(id);

        if(it == nodes.end())
            return;
        
        et.parent_ = id;
        et.has_parent = true;
        if (it != nodes.end() && !it->second->visited) {
            it->second->visited = true;
            for(const auto item : it->second->neighbors_) {
                et.current_ = item.label_;
                et.weight = item.weight_;
                action(et);
                bfs_q.push(item.label_);
            }
        }
        bfs_q.pop();
    }
}

template<typename T>
void Graph<T>::dfs(T node_id, std::function<void(EdgeTraversal<T>& )> action)
{
    reset_visited_state();

    auto it = nodes.find(node_id);
    if(it != nodes.end())
        dfs_(it->second, action);
}

template<typename T>
void Graph<T>::dfs_(const std::unique_ptr<GraphNode<T> >& node, std::function<void(EdgeTraversal<T>& )> action)
{
    const auto& current = node;
    while(current && !current->visited) {
        current->visited = true;
        for(const auto& item : current->neighbors_) {
            auto n_it =  nodes.find(item.label_);
            if (n_it != nodes.end()) {
                EdgeTraversal<T> et;
                et.parent_ = current->get_label();
                et.current_ = item.label_;
                et.weight = item.weight_;
                action(et);
                dfs_(n_it->second, action);
            }
        }
    }
}

template<typename T>
void Graph<T>::add_edge(const T& source, const T& dest, int weight)
{
    auto it = nodes.find(source);
    if(it == nodes.end()) {
        insert_node(source, {}, {});
        it = nodes.find(source);
    }
    it->second->neighbors_.push_back({dest, weight});
}

template<typename T>
void Graph<T>::dijikstra_shortest_paths(T source)
{
    //Create a distance hash_map, where you can store distance.
    //Set the source dist to 0 and all others to infinite.
    //Insert the source and it's distance to min heap which controlled by distance, need to add comp function.
        //While the heap is not empty, iterate
            //For each item in min heap, caluclate it's neighbors' distance by source distance + weight
            //if the distance is new, i.e. if the old distance is infinite then just push into heap.
            //update if new short distance found for vertex in min heap, probably need to find by key with a special compare function.
            //reform heap
    //return the final distance hash_map
    auto it = nodes.find(source);
    if(it == nodes.end()) return;

    std::unordered_map <T, int> distance_map;
    for(const auto& item : nodes) {
        distance_map.insert(std::make_pair<T, int>(item.second->get_label(), INT_MAX));
    }

    auto& dist = distance_map[source];
    dist = 0;

    
    typedef std::tuple<int, T> distance_values; 
    std::vector<distance_values> min_heap;
    min_heap.push_back({0, source});
    auto heap_comp = [] (const distance_values& first, const distance_values& second) {
            return (std::get<0>(first) < std::get<0>(second));
            };
    std::make_heap(begin(min_heap), end(min_heap), heap_comp);
    while(!min_heap.empty()) {
        std::pop_heap(begin(min_heap), end(min_heap));
        auto [distance, node_id] = *(min_heap.end()-1);
        min_heap.erase(min_heap.end() - 1);

        auto current_it = nodes.find(node_id);

        for(const auto& neighbor : current_it->second->neighbors_) {
            //std::cout << neighbor.label_ <<' '<<std::endl;
            auto new_dist = distance_map[current_it->first] + neighbor.weight_;
            if(new_dist < distance_map[neighbor.label_]) {
                auto item_in_heap = std::find_if(cbegin(min_heap), cend(min_heap), [&neighbor] (const distance_values& item) {
                        return std::get<1>(item) == neighbor.label_;
                        });
                if(item_in_heap != min_heap.end()) {
                    min_heap.erase(item_in_heap);
                    std::make_heap(begin(min_heap), end(min_heap), heap_comp);
                }

                min_heap.push_back({new_dist, neighbor.label_});
                std::push_heap(begin(min_heap), end(min_heap));
                distance_map[neighbor.label_] = new_dist;
            }
        }
    }

    for(const auto& item : distance_map) {
        std::cout << source << " -> " << item.first << " : " << item.second <<'\n';
    }
}
#endif

