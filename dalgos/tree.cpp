#include <iostream>
#include <memory>
#include <vector>
#include <map>

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
    private:
    s_ptr<Node> root;
    void insert(int value, s_ptr<Node> current);
};

void BinaryTree::insert(int value)
{
    return insert(value, root);
}
void BinaryTree::insert(int value, s_ptr<Node> current)
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
int main()
{
   BinaryTree t;
   std::cout<<"Inserting elements\n";
   t.insert(1);
   t.insert(2);
   t.insert(3);
   return 0;
}
