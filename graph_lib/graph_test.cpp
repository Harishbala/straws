#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "graph.hpp"

using nlohmann::json;

int main()
{
    Graph<std::string> graph;

    json j;
    std::ifstream input_file("graph.json");
    input_file >> j;

    for(const auto& item : j) {
        graph.insert_node(item["label"], item["neighbors"], item["weights"]);
    }

    graph.add_edge("Aristotle", "Kant", 25);
    graph.print_nodes_as_dot();
    graph.delete_node("Descartes");
    //graph.dfs("Plato", [](){});
}
