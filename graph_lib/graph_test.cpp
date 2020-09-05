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
        graph.insert_node(item["label"], item["neighbors"]);
    }

    graph.print_nodes_as_dot();
    std::cout << "Before delete ----\n";
    graph.delete_node("Descartes");
    std::cout << "After delete ----\n";
    graph.dfs("Plato", [](){});
}
