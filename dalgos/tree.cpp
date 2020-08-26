#include <iostream>
#include <memory>

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

class Tree
{
    public:
    Tree() : root(nullptr) {}
    void insert(int value);
    private:
    s_ptr<Node> root;
    void insert(int value, s_ptr<Node> current);
};

void Tree::insert(int value)
{
    return insert(value, root);
}
void Tree::insert(int value, s_ptr<Node> current)
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

int main()
{
   Tree t;
   std::cout<<"Inserting elements\n";
   t.insert(1);
   t.insert(2);
   t.insert(3);
   return 0;
}
