#include <vector>

template<class T> using u_ptr = std::unique_ptr<T>;

struct GNode {
    int val_;
    std::vector<int> neighbors_;
    GNode() = delete;
    GNode(int val, std::vector<int> nodes) : 
        val_(val),
        neighbors_(nodes)
    {
    }
};

class Graph {
public:
    void insert(vector<int>& nodes);

private:
    std::vector<u_ptr<GNode>> nodes_;
};

void Graph::insert(vector<int>& nodes) {
    nodes_.push_back(std::make_unique<GNode>(nodes_.size(), nodes));
}
