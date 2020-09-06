#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "graph.hpp"
#include "graph_as_dot.hpp"

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
    //graph.print_nodes_as_dot();
    //graph.delete_node("Descartes");

    Graph<std::string> bfs_graph;
    GraphAsDot<std::string> graph_dot;
    graph.bfs("Plato", [&graph_dot](EdgeTraversal<std::string>& et){
            //std::cout<<et.parent_<<" -> "<<et.weight<<" -> "<<et.current_ << '\n';
            //bfs_graph.add_edge(et.parent_, et.current_, et.weight);
            graph_dot.add_edge(et.parent_, et.current_, et.weight);
            });
    std::cout << graph_dot.str();
    //bfs_graph.print_nodes_as_dot();
}
