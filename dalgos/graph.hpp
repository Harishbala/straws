
template<class T> using u_ptr = std::unique_ptr<T>;
struct GNode {
    int val_;
    std::vector<u_ptr<GNode>> neighbors_;
    GNode() = delete;
    GNode(int val) : val_(val) {
    }
};

class Graph {
private:
    std::vector<GNode> nodes_;
};




