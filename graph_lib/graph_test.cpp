#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "graph.hpp"

using nlohmann::json;

int main()
{
    Graph<std::string> graph;
    graph.insert_node("Plato", {"Socrates", "Aristotle", "Pythagoras"});
    graph.insert_node("Aristotle", {"Parmenides", "Plato", "Archimedes"});
    graph.insert_node("Descartes", {"Leibniz", "Spinoza", "Hume"});
    graph.insert_node("Kant", {"Hegel", "Descartes", "Schopenhauer"});

    json j;
    std::ifstream input_file("graph.json");
    input_file >> j;

    auto list = j["dummy"];
    for(const auto & item : list) {
        std::cout << item <<'\n';
    }

    graph.print_nodes_as_dot();
    std::cout << "Before delete ----\n";
    graph.delete_node("Descartes");
    std::cout << "After delete ----\n";
    graph.dfs("Plato", [](){});
    //graph.dfs();
    //graph.bfs("Plato", [](){});
}
