#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <queue>

using namespace std;

template<class T> using s_ptr = std::shared_ptr<T>;
template<class T> using u_ptr = std::unique_ptr<T>;

struct Node {
    Node(int val) : val(val),
    left(nullptr),
    right(nullptr)
    {}
    int val;
    s_ptr<Node> left;
    s_ptr<Node> right;
};

struct Node_E {
    Node_E(int val) : val(val)
    {}
    int val;
    vector<s_ptr<Node_E> > children;
    std::map<std::string, int> flags;
};

class BinaryTree
{
    public:
    BinaryTree() : root(nullptr) {}
    void insert(int value);
    void print();
    void balance();
    int find_tree_height();

    private:
    s_ptr<Node> root;
    void insert(int value, s_ptr<Node>& current);
    void print_(const s_ptr<Node>& node, int level, vector<vector<int>>& values);
    void get_sorted(s_ptr<Node>& node, vector<int>& sorted);
    void balance_(s_ptr<Node>& node, vector<int>& sorted, int start, int end);
    void find_tree_height_(s_ptr<Node>& node,int level, int& height); 
};

void BinaryTree::insert(int value)
{
    return insert(value, root);
}
void BinaryTree::insert(int value, s_ptr<Node>& current)
{
    if(current)
    {
        s_ptr<Node> child;
        if(current->val <= value)
        {
            if(current->right)
                insert(value, current->right);
            else
                current->right = make_shared<Node>(value);
        }
        else
        {
            if(current->left)
                insert(value, current->left);
            else
                current->left = make_shared<Node>(value);
        }
    }
    else
    {
        current = make_shared<Node>(value);
    }
}

void BinaryTree::print() {
    vector<vector<int>> values;
    print_(root, 0, values);

    for(const auto& item : values) {
        for(const auto& v : item) {
            std::cout << v << ' ';
        }
        std::cout <<'\n';
    }
}

void BinaryTree::print_(const s_ptr<Node>& node, int level, vector<vector<int>>& values)
{
    if(node)
    {
        if(level+1 > values.size()) {
            values.push_back({});
        }
        values[level].push_back(node->val);

        print_(node->left, level+1, values);
        print_(node->right, level+1, values);
    }
}

void BinaryTree::balance() {
    vector<int> sorted;
    get_sorted(root, sorted);

    balance_(root, sorted, 0, sorted.size()-1);
}

void BinaryTree::get_sorted(s_ptr<Node>& node, vector<int>& sorted) {
    if(node) {
        get_sorted(node->left, sorted);
        sorted.push_back(node->val);
        get_sorted(node->right, sorted);
    }
}

void BinaryTree::balance_(s_ptr<Node>& node, vector<int>& sorted, int start, int end) {
    
    if(start > end)
        return;

    int mid = (start + end) / 2;
    
    node = std::make_shared<Node>(sorted[mid]); 
    balance_(node->left, sorted, start, mid-1);
    balance_(node->right, sorted, mid+1, end);
    
}
class Tree
{
    s_ptr<Node_E> find_center_of_tree();
private:
    s_ptr<Node_E> find_center_of_tree_(const s_ptr<Node_E> current);
    s_ptr<Node_E> root;
};

s_ptr<Node_E> Tree::find_center_of_tree()
{
    return find_center_of_tree_(root);
}

s_ptr<Node_E> Tree::find_center_of_tree_(s_ptr<Node_E> current)
{
    if(current)
    {
        for(const auto item : current->children)
        {
           return  find_center_of_tree_(item);
        }
    }
    return nullptr;
}

int BinaryTree::find_tree_height() {
    int level = 0;
    int height = 0;
    find_tree_height_(root, 1, height);
    return height;
}

void BinaryTree::find_tree_height_(s_ptr<Node>& node,int level, int& height) {
    if (node) {
        height = max(height, level);
        find_tree_height_(node->left, level+1, height);
        find_tree_height_(node->right, level+1, height);
    }
}

int main_disabled()
{
   BinaryTree t;
   std::cout<<"Inserting elements\n";
   t.insert(1);
   t.insert(2);
   t.insert(3);
   t.print();
   t.balance();
   std::cout << "After balancing:\n";
   t.print();
   int height = t.find_tree_height();
   std::cout << "Tree height : " << height << '\n';
   return 0;
}
