#include <iostream>

#include "graph.h"

int main()
{
    Graph<std::string> graph;
    graph.insert_node("Plato", {"Socrates", "Aristotle", "Pythagoras"});
    graph.insert_node("Aristotle", {"Parmenides", "Plato", "Archimedes"});
    graph.insert_node("Descartes", {"Leibniz", "Spinoza", "Hume"});
    graph.insert_node("Kant", {"Hegel", "Descartes", "Schopenhauer"});

    graph.print_nodes_as_dot();
    graph.delete_node("Descartes");

    //graph.bfs("Aristotle", [](){} );
    //std::cout << "----\n";
    //graph.bfs("Plato", [](){});
}
