#include <iostream>

#include "graph.h"

int main()
{
    Graph<std::string> graph;
    graph.insert_node("Plato", {"Socrates", "Aristotle", "Pythagoras"});
    graph.insert_node("Aristotle", {"Parmenides", "Plato", "Archimedes"});
    graph.insert_node("Descartes", {"Leibniz", "Spinoza", "Hume"});
    graph.insert_node("Kant", {"Hegel", "Descartes", "Schopenhauer"});

    graph.print_nodes();
    graph.delete_node("Descartes");

    std::cout << "After deleting nodes : \n";

    graph.print_nodes();

    graph.bfs("Aristotle", [](){} );
    std::cout << "----\n";
    graph.bfs("Plato", [](){});
}
