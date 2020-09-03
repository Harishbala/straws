#include "graph.h"

int main()
{
    Graph graph;
    graph.insert_node(1, {2, 3, 4});
    graph.insert_node(2, {3, 4, 1});
    graph.insert_node(3, {4, 3, 2});
    graph.insert_node(4, {1, 3, 2});

    graph.print_nodes();
}