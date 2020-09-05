#include <iostream>

#include "graph.hpp"

int main()
{
    Graph<std::string> graph;
    graph.insert_node("Plato", {"Socrates", "Aristotle", "Pythagoras"});
    graph.insert_node("Aristotle", {"Parmenides", "Plato", "Archimedes"});
    graph.insert_node("Descartes", {"Leibniz", "Spinoza", "Hume"});
    graph.insert_node("Kant", {"Hegel", "Descartes", "Schopenhauer"});

    graph.print_nodes_as_dot();
    graph.delete_node("Descartes");
    //graph.dfs("Plato", [](){});
    //graph.dfs();
    //graph.bfs("Plato", [](){});
}
