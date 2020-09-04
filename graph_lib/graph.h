#include <vector>
#include <map>
#include <memory>

template <class T>
struct GraphNode
{
    T label_;
    bool visited;
    std::vector<T> neighbors_;
};

template<typename T2>
class Graph
{
public:
    void insert_node(const T2 node_id, const std::vector<T2>&& neighbors);
    void print_nodes() const;
    void delete_node(T2 node_id);
    void bfs(T2 node_id, std::function<void()> action);
    
private:
    void reset_visited_state();

    std::map<T2, std::unique_ptr<GraphNode<T2>> > nodes;
};

