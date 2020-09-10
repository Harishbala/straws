#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <gtest/gtest.h>

#include "graph.hpp"
#include "graph_as_dot.hpp"

using nlohmann::json;

TEST(GraphTest, Graph_Collective_Test)
{
    Graph<std::string> graph;

    json j;
    std::ifstream input_file("graph.json");
    input_file >> j;

    for(const auto& item : j) {
        graph.insert_node(item["label"], item["neighbors"], item["weights"]);
    }

    graph.add_edge("Aristotle", "Kant", 25);

    int count  = 1;
    GraphAsDot<std::string> graph_dot;
    graph.bfs("Plato", [&graph_dot, &count](EdgeTraversal<std::string>& et){
            graph_dot.add_edge(et.parent_, et.current_, count++);
            });
    std::cout << graph_dot.str();
    graph.dijikstra_shortest_paths("Plato");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
