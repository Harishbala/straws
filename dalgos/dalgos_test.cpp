#include <gtest/gtest.h>
#include "tree.hpp"
#include "strings.hpp"

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
TEST(BinaryTreeTest, TreeHeight_Balanced_Bigtree) {
   BinaryTree t;

   //input tree taken from : http://faculty.washington.edu/jstraub/dsa/btree/test_balance.html
   t.insert(1024);
   t.insert(512);
   t.insert(1536);
   t.insert(256);
   t.insert(768);
   t.insert(1280);
   t.insert(1792);
   t.insert(128);
   t.insert(384);
   t.insert(640);
   t.insert(896);
   t.insert(1152);
   t.insert(1408);
   t.insert(1664);
   t.insert(1920);
   t.insert(64);
   t.insert(192);
   t.insert(320);
   t.insert(448);
   t.insert(576);
   t.insert(704);
   t.insert(832);
   t.insert(960);
   t.insert(1088);
   t.insert(1216);
   t.insert(1344);
   t.insert(1472);
   t.insert(1600);
   t.insert(1728);
   t.insert(1856);
   t.insert(1984);
   
   t.print();
   t.balance();
   std::cout << "After balancing:\n";
   t.print();

   t.bfs();
   int height = t.find_tree_height();
   std::cout << "Tree height : " << height << '\n';
   ASSERT_EQ(5, height);
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

TEST(StringsTest, String_Binary_Search)
{
    std::string str{"Helloworld"};

    sort(begin(str), end(str));
    
    std::cout <<str<<'\n';
    std::cout <<binary_search(str, 'o') <<'\n';

    std::rotate(begin(str), begin(str) + 3, end(str));
    
    std::cout << str << '\n';
    std::cout <<search_rotated(str, 'o') <<'\n';

    filter_duplicated_from_sorted(str);
    std::cout << str << '\n';
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
