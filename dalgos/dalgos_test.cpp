#include <gtest/gtest.h>
#include "tree.hpp"

TEST(BinaryTreeTest, TreeHeight_Balanced) {
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
   ASSERT_EQ(2, height);
}

TEST(BinaryTreeTest, TreeHeight_Unbalanced) {
   BinaryTree t;
   std::cout<<"Inserting elements\n";
   t.insert(1);
   t.insert(2);
   t.insert(3);
   t.print();
   t.print();
   int height = t.find_tree_height();
   std::cout << "Tree height : " << height << '\n';
   ASSERT_EQ(3, height);
}

TEST(BinaryTreeTest, TreeHeight_with_no_nodes) {
   BinaryTree t;
   std::cout<<"Inserting elements\n";
   t.print();
   t.balance();
   std::cout << "After balancing:\n";
   t.print();
   int height = t.find_tree_height();
   std::cout << "Tree height : " << height << '\n';
   ASSERT_EQ(0, height);
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
